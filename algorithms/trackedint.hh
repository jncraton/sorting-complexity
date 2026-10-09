#pragma once

#include <compare>

class TrackedInt {
  int val;
  static inline long long comparisons = 0;

public:
  TrackedInt(int v = 0) : val(v) {}

  static long long get_comparisons() { return comparisons; }
  static void reset_comparisons() { comparisons = 0; }

  int get_val() const { return val; }

  auto operator<=>(const TrackedInt &other) const {
    comparisons++;
    return val <=> other.val;
  }

  bool operator==(const TrackedInt &other) const {
    comparisons++;
    return val == other.val;
  }
};
