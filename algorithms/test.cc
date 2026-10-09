#include <algorithm>
#include <chrono>
#include <iostream>
#include <print>
#include <vector>

#include "list.hh"

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

int main() {
  list<TrackedInt> l{10, 20, 30};

  TrackedInt::reset_comparisons();
  auto start_time = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < 1000000; i++) {
    l.push_front(i);
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;

  std::println("");
  std::println("Comparisons: {}", TrackedInt::get_comparisons());
  std::println("Time: {} seconds", elapsed.count());

  return 0;
}
