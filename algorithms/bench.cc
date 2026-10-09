#include <chrono>
#include <cstddef>
#include <fstream>
#include <initializer_list>
#include <memory>
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

template <typename Operation>
void benchmark(std::ofstream &output, const char *name, std::size_t size,
               std::size_t initial_size, std::size_t iterations,
               Operation operation) {
  std::vector<std::unique_ptr<list<TrackedInt>>> lists;
  lists.reserve(iterations);

  for (std::size_t i = 0; i < iterations; ++i) {
    lists.emplace_back(
        std::make_unique<list<TrackedInt>>(std::initializer_list<TrackedInt>{}));

    for (std::size_t j = 0; j < initial_size; ++j) {
      lists.back()->push_back(static_cast<int>(j));
    }
  }

  std::chrono::duration<double, std::nano> elapsed{};

  for (std::size_t i = 0; i < iterations; ++i) {
    auto start = std::chrono::steady_clock::now();
    operation(*lists[i], i);
    auto end = std::chrono::steady_clock::now();

    elapsed += end - start;
  }

  std::println(output, "{},{},{},{}", name, size, iterations,
               elapsed.count() / iterations);
}

int main() {
  std::ofstream output("bench.csv");
  std::println(output, "operation,size,iterations,ns_per_operation");

  const std::size_t sizes[] = {10, 100, 1000, 10000};
  const std::size_t iterations = 10000;

  for (std::size_t size : sizes) {
    benchmark(output, "at", size, size, iterations,
              [size](auto &l, std::size_t) { (void)l.at(size / 2); });

    benchmark(output, "operator[]", size, size, iterations,
              [size](auto &l, std::size_t) { (void)l[size / 2]; });

    benchmark(output, "front", size, size, iterations,
              [](auto &l, std::size_t) { (void)l.front(); });

    benchmark(output, "back", size, size, iterations,
              [](auto &l, std::size_t) { (void)l.back(); });

    benchmark(output, "size", size, size, iterations,
              [](auto &l, std::size_t) { (void)l.size(); });

    benchmark(output, "push_back", size, size, iterations,
              [](auto &l, std::size_t i) {
                l.push_back(static_cast<int>(i));
              });

    benchmark(output, "pop_back", size, size + 1, iterations,
              [](auto &l, std::size_t) { l.pop_back(); });

    benchmark(output, "push_front", size, size, iterations,
              [](auto &l, std::size_t i) {
                l.push_front(static_cast<int>(i));
              });

    benchmark(output, "pop_front", size, size + 1, iterations,
              [](auto &l, std::size_t) { l.pop_front(); });

    benchmark(output, "insert", size, size, iterations,
              [size](auto &l, std::size_t i) {
                l.insert(size / 2, static_cast<int>(i));
              });

    benchmark(output, "clear", size, size, iterations,
              [](auto &l, std::size_t) { l.clear(); });

    benchmark(output, "sort_bubble", size, size, iterations,
              [](auto &l, std::size_t) { l.sort_bubble(); });

    benchmark(output, "sort_insertion", size, size, iterations,
              [](auto &l, std::size_t) { l.sort_insertion(); });

    benchmark(output, "sort_selection", size, size, iterations,
              [](auto &l, std::size_t) { l.sort_selection(); });

    benchmark(output, "sort_merge", size, size, iterations,
              [](auto &l, std::size_t) { l.sort_merge(); });

    benchmark(output, "sort_quick", size, size, iterations,
              [](auto &l, std::size_t) { l.sort_quick(); });

    benchmark(output, "sort_heap", size, size, iterations,
              [](auto &l, std::size_t) { l.sort_heap(); });

    benchmark(output, "sort_shell", size, size, iterations,
              [](auto &l, std::size_t) { l.sort_shell(); });

    benchmark(output, "sort_tim", size, size, iterations,
              [](auto &l, std::size_t) { l.sort_tim(); });
  }

  std::println("Benchmark results written to bench.csv");
}
