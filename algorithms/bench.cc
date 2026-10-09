#include <chrono>
#include <cstddef>
#include <fstream>
#include <initializer_list>
#include <memory>
#include <print>
#include <vector>

#include "forward_list.hh"
#include "list.hh"
#include "vector.hh"

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

template <typename Container, typename Operation>
void benchmark(std::ofstream &output, const char *container_name,
               const char *name, std::size_t size, std::size_t initial_size,
               std::size_t iterations, Operation operation) {
  std::vector<std::unique_ptr<Container>> containers;
  containers.reserve(iterations);

  for (std::size_t i = 0; i < iterations; ++i) {
    containers.emplace_back(
        std::make_unique<Container>(std::initializer_list<TrackedInt>{}));

    for (std::size_t j = 0; j < initial_size; ++j) {
      containers.back()->push_back(static_cast<int>(j));
    }
  }

  std::chrono::duration<double, std::nano> elapsed{};

  for (std::size_t i = 0; i < iterations; ++i) {
    auto start = std::chrono::steady_clock::now();
    operation(*containers[i], i);
    auto end = std::chrono::steady_clock::now();

    elapsed += end - start;
  }

  std::println(output, "{},{},{},{},{}", container_name, name, size, iterations,
               elapsed.count() / iterations);
}

template <typename Container>
void run_benchmarks_for_container(std::ofstream &output,
                                  const char *container_name) {
  const std::size_t sizes[] = {10, 100, 1000, 10000};
  const std::size_t iterations = 10;

  for (std::size_t size : sizes) {
    benchmark<Container>(
        output, container_name, "at", size, size, iterations,
        [size](auto &l, std::size_t) { (void)l.at(size / 2); });

    benchmark<Container>(output, container_name, "operator[]", size, size,
                         iterations,
                         [size](auto &l, std::size_t) { (void)l[size / 2]; });

    benchmark<Container>(output, container_name, "front", size, size,
                         iterations,
                         [](auto &l, std::size_t) { (void)l.front(); });

    benchmark<Container>(output, container_name, "back", size, size, iterations,
                         [](auto &l, std::size_t) { (void)l.back(); });

    benchmark<Container>(output, container_name, "size", size, size, iterations,
                         [](auto &l, std::size_t) { (void)l.size(); });

    benchmark<Container>(
        output, container_name, "push_back", size, size, iterations,
        [](auto &l, std::size_t i) { l.push_back(static_cast<int>(i)); });

    benchmark<Container>(output, container_name, "pop_back", size, size + 1,
                         iterations,
                         [](auto &l, std::size_t) { l.pop_back(); });

    benchmark<Container>(
        output, container_name, "push_front", size, size, iterations,
        [](auto &l, std::size_t i) { l.push_front(static_cast<int>(i)); });

    benchmark<Container>(output, container_name, "pop_front", size, size + 1,
                         iterations,
                         [](auto &l, std::size_t) { l.pop_front(); });

    benchmark<Container>(output, container_name, "insert", size, size,
                         iterations, [size](auto &l, std::size_t i) {
                           l.insert(size / 2, static_cast<int>(i));
                         });

    benchmark<Container>(output, container_name, "clear", size, size,
                         iterations, [](auto &l, std::size_t) { l.clear(); });

    benchmark<Container>(output, container_name, "sort_bubble", size, size,
                         iterations / 10,
                         [](auto &l, std::size_t) { l.sort_bubble(); });

    benchmark<Container>(output, container_name, "sort_insertion", size, size,
                         iterations / 10,
                         [](auto &l, std::size_t) { l.sort_insertion(); });

    benchmark<Container>(output, container_name, "sort_selection", size, size,
                         iterations / 10,
                         [](auto &l, std::size_t) { l.sort_selection(); });

    benchmark<Container>(output, container_name, "sort_merge", size, size,
                         iterations / 10,
                         [](auto &l, std::size_t) { l.sort_merge(); });

    benchmark<Container>(output, container_name, "sort_quick", size, size,
                         iterations / 10,
                         [](auto &l, std::size_t) { l.sort_quick(); });

    benchmark<Container>(output, container_name, "sort_heap", size, size,
                         iterations / 10,
                         [](auto &l, std::size_t) { l.sort_heap(); });

    benchmark<Container>(output, container_name, "sort_shell", size, size,
                         iterations / 10,
                         [](auto &l, std::size_t) { l.sort_shell(); });

    benchmark<Container>(output, container_name, "sort_tim", size, size,
                         iterations / 10,
                         [](auto &l, std::size_t) { l.sort_tim(); });
  }
}

int main() {
  std::ofstream output("bench.csv");
  std::println(output, "container,operation,size,iterations,ns_per_operation");

  run_benchmarks_for_container<list<TrackedInt>>(output, "list");
  run_benchmarks_for_container<forward_list<TrackedInt>>(output,
                                                         "forward_list");
  run_benchmarks_for_container<vector<TrackedInt>>(output, "vector");

  std::println("Benchmark results written to bench.csv");
}
