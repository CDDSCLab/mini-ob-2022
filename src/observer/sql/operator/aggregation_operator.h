//
// Created by Moon on 2022/10/25.
//

#pragma once

#include "sql/operator/operator.h"

#include <unordered_map>

#include "sql/parser/parse_defs.h"
#include "sql/expr/tuple_cell_factory.h"
#include "util/MurmurHash2.h"

struct AggregateKey {
  std::vector<TupleCell> group_bys_;

  bool operator==(const AggregateKey &other) const
  {
    for (uint32_t i = 0; i < other.group_bys_.size(); i++) {
      if (group_bys_[i].compare(other.group_bys_[i]) != 0) {
        return false;
      }
    }
    return true;
  }
};

struct AggregateValue {
  int count;
  std::vector<int> null_counts;
  std::vector<TupleCell> aggregates_;
};

namespace std {

template <>
struct hash<AggregateKey> {
  std::size_t operator()(const AggregateKey &aggr_key) const
  {
    int len = 0;
    for (const auto &group_by : aggr_key.group_bys_) {
      len += group_by.length();
    }
    auto key = static_cast<char *>(malloc(len));
    int offset = 0;
    for (const auto &group_by : aggr_key.group_bys_) {
      memcpy(key + offset, group_by.data(), group_by.length());
      offset += group_by.length();
    }
    return MurmurHash64A(key, len, 0x1F0D3804);
  }
};

}  // namespace std

class AggregationHashTable {
public:
  AggregationHashTable(const std::vector<Field> &aggr_field) : aggr_field(aggr_field)
  {}

  AggregateValue generate_initial_aggregate_value()
  {
    std::vector<int> null_counts;
    std::vector<TupleCell> values;
    for (const auto &field : aggr_field) {
      null_counts.emplace_back(0);

      auto attr_type = field.attr_type();
      switch (field.aggr_type()) {
        case AGGR_NONE:
          break;
        case AGGR_MAX:
          values.emplace_back(TupleCellFactory::GetMinTupleCellByType(attr_type));
          break;
        case AGGR_MIN:
          values.emplace_back(TupleCellFactory::GetMaxTupleCellByType(attr_type, field.meta()->len()));
          break;
        case AGGR_COUNT:
          values.emplace_back(TupleCellFactory::GetIntegerTupleCell(0));
          break;
        case AGGR_AVG:
          values.emplace_back(TupleCellFactory::GetFloatTupleCell(0));
          break;
        case AGGR_SUM:
          if (attr_type == INTS) {
            values.emplace_back(TupleCellFactory::GetIntegerTupleCell(0));
          } else if (attr_type == FLOATS || attr_type == CHARS) {
            values.emplace_back(TupleCellFactory::GetFloatTupleCell(0));
          } else {
            assert(false);
          }
          break;
      }
    }
    return {0, null_counts, values};
  }

  void combine_aggregate_values(AggregateValue *result, const AggregateValue &input)
  {
    result->count += input.count;
    for (int i = 0; i < aggr_field.size(); i++) {
      if (input.aggregates_[i].attr_type() == AttrType::NULLS) {
        result->null_counts[i]++;
        continue;
      }

      switch (aggr_field[i].aggr_type()) {
        case AGGR_NONE:
          break;
        case AGGR_MAX:
          if (input.aggregates_[i].compare(result->aggregates_[i]) > 0) {
            result->aggregates_[i] = input.aggregates_[i];
          }
          break;
        case AGGR_MIN:
          if (input.aggregates_[i].compare(result->aggregates_[i]) < 0) {
            result->aggregates_[i] = input.aggregates_[i];
          }
          break;
        case AGGR_COUNT:
          result->aggregates_[i].plus(TupleCellFactory::GetIntegerTupleCell(1));
          break;
        case AGGR_AVG:
        case AGGR_SUM:
          result->aggregates_[i].plus(input.aggregates_[i]);
          break;
      }
    }
  }

  void insert_combine(const AggregateKey &aggr_key, const AggregateValue &aggr_value)
  {
    if (hash_table_.count(aggr_key) == 0) {
      hash_table_.insert({aggr_key, generate_initial_aggregate_value()});
    }
    combine_aggregate_values(&hash_table_[aggr_key], aggr_value);
  }

  class Iterator {
  public:
    explicit Iterator()
    {}
    explicit Iterator(std::unordered_map<AggregateKey, AggregateValue>::const_iterator iter) : iter_{iter}
    {}

    const AggregateKey &Key()
    {
      return iter_->first;
    }
    const AggregateValue &Value()
    {
      return iter_->second;
    }

    Iterator &operator++()
    {
      ++iter_;
      return *this;
    }
    bool operator==(const Iterator &other)
    {
      return this->iter_ == other.iter_;
    }
    bool operator!=(const Iterator &other)
    {
      return this->iter_ != other.iter_;
    }

  private:
    std::unordered_map<AggregateKey, AggregateValue>::const_iterator iter_;
  };

  Iterator Begin()
  {
    return Iterator{hash_table_.cbegin()};
  }
  Iterator End()
  {
    return Iterator{hash_table_.cend()};
  }

private:
  std::unordered_map<AggregateKey, AggregateValue> hash_table_{};
  const std::vector<Field> &aggr_field;
};

class AggregationOperator : public Operator {
public:
  AggregationOperator(const std::vector<Field> &aggregate_field, const std::vector<Field> &group_by_field)
      : aggregate_field_(aggregate_field),
        group_by_field_(group_by_field),
        hash_table_(aggregate_field),
        hash_table_iter_(),
        tuple_(aggregate_field, group_by_field)
  {}

  virtual ~AggregationOperator() = default;

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  AggregateKey make_aggregate_key(const Tuple *tuple)
  {
    std::vector<TupleCell> keys;
    TupleCell cell;
    for (const auto &field : group_by_field_) {
      tuple->find_cell(field, cell);
      keys.emplace_back(cell);
    }
    return {keys};
  }

  AggregateValue make_aggregate_value(const Tuple *tuple)
  {
    std::vector<int> null_counts;
    std::vector<TupleCell> values;
    TupleCell cell;
    for (const auto &field : aggregate_field_) {
      null_counts.emplace_back(0);

      tuple->find_cell(field, cell);
      values.emplace_back(cell);
    }
    return {1, null_counts, values};
  }

  const std::vector<Field> &aggregate_field_;
  const std::vector<Field> &group_by_field_;
  AggregationHashTable hash_table_;
  AggregationHashTable::Iterator hash_table_iter_;
  AggregateTuple tuple_;
  bool init_ = false;
};
