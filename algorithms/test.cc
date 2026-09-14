#include <algorithm>
#include <chrono>
#include <iostream>
#include <print>
#include <vector>

class TrackedInt {
  int val;
  static inline long long comparisons = 0;

public:
  TrackedInt(int v = 0) : val(v) {}

  static long long get_comparisons() { return comparisons; }
  static void reset_comparisons() { comparisons = 0; }

  int get_val() const { return val; }

  auto operator<=>(const TrackedInt& other) const {
    comparisons++;
    return val <=> other.val;
  }

  bool operator==(const TrackedInt& other) const {
    comparisons++;
    return val == other.val;
  }
};

template <typename T>
extern void sort(std::vector<T>&);

int main() {
  std::vector<TrackedInt> arr;
  int val;
  while (std::cin >> val) {
    arr.push_back(TrackedInt(val));
  }

  TrackedInt::reset_comparisons();
  auto start_time = std::chrono::high_resolution_clock::now();

  sort(arr);

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;

  for (int i = 0; i < arr.size(); ++i) {
    std::println("{}", arr[i].get_val());
  }
  std::println("");
  std::println("Comparisons: {}", TrackedInt::get_comparisons());
  std::println("Time: {} seconds", elapsed.count());

  return 0;
}
