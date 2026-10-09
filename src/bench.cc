#include <chrono>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <initializer_list>
#include <memory>
#include <print>
#include <utility>
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

enum class InputOrder { presorted, reverse_sorted, randomized };

const char *input_order_name(InputOrder order) {
  switch (order) {
  case InputOrder::presorted:
    return "presorted";
  case InputOrder::reverse_sorted:
    return "reverse_sorted";
  case InputOrder::randomized:
    return "randomized";
  }

  return "unknown";
}

std::vector<int> make_input_values(std::size_t size, InputOrder order,
                                   std::size_t iteration) {
  std::vector<int> values(size);

  for (std::size_t i = 0; i < size; ++i) {
    if (order == InputOrder::reverse_sorted) {
      values[i] = static_cast<int>(size - 1 - i);
    } else {
      values[i] = static_cast<int>(i);
    }
  }

  if (order == InputOrder::randomized) {
    std::uint64_t state =
        0x9e3779b97f4a7c15ULL ^ static_cast<std::uint64_t>(iteration + 1);

    for (std::size_t i = size; i > 1; --i) {
      state ^= state >> 12;
      state ^= state << 25;
      state ^= state >> 27;

      const std::size_t j =
          static_cast<std::size_t>((state * 0x2545f4914f6cdd1dULL) % i);
      std::swap(values[i - 1], values[j]);
    }
  }

  return values;
}

template <typename Container, typename Operation>
void benchmark(std::ofstream &output, const char *container_name,
               const char *name, std::size_t size, std::size_t initial_size,
               std::size_t iterations, Operation operation,
               InputOrder input_order = InputOrder::presorted) {
  std::vector<std::unique_ptr<Container>> containers;
  containers.reserve(iterations);

  for (std::size_t i = 0; i < iterations; ++i) {
    containers.emplace_back(
        std::make_unique<Container>(std::initializer_list<TrackedInt>{}));

    const auto values = make_input_values(initial_size, input_order, i);
    for (int value : values) {
      containers.back()->push_back(value);
    }
  }

  std::chrono::duration<double, std::nano> elapsed{};
  long long total_comparisons = 0;

  for (std::size_t i = 0; i < iterations; ++i) {
    TrackedInt::reset_comparisons();

    auto start = std::chrono::steady_clock::now();
    operation(*containers[i], i);
    auto end = std::chrono::steady_clock::now();

    elapsed += end - start;
    total_comparisons += TrackedInt::get_comparisons();
  }

  const double ns_per_operation = elapsed.count() / iterations;
  const double comparisons_per_operation =
      static_cast<double>(total_comparisons) / iterations;

  std::println(output, "{},{},{},{},{},{},{}", container_name, name,
               input_order_name(input_order), size, iterations,
               ns_per_operation, comparisons_per_operation);
}

template <typename Container>
void run_sort_benchmarks(std::ofstream &output, const char *container_name,
                         std::size_t size, std::size_t iterations,
                         InputOrder input_order) {
  const std::size_t sort_iterations = iterations / 10;

  benchmark<Container>(
      output, container_name, "sort_bubble", size, size, sort_iterations,
      [](auto &l, std::size_t) { l.sort_bubble(); }, input_order);

  benchmark<Container>(
      output, container_name, "sort_insertion", size, size, sort_iterations,
      [](auto &l, std::size_t) { l.sort_insertion(); }, input_order);

  benchmark<Container>(
      output, container_name, "sort_selection", size, size, sort_iterations,
      [](auto &l, std::size_t) { l.sort_selection(); }, input_order);

  benchmark<Container>(
      output, container_name, "sort_merge", size, size, sort_iterations,
      [](auto &l, std::size_t) { l.sort_merge(); }, input_order);

  benchmark<Container>(
      output, container_name, "sort_quick", size, size, sort_iterations,
      [](auto &l, std::size_t) { l.sort_quick(); }, input_order);

  benchmark<Container>(
      output, container_name, "sort_heap", size, size, sort_iterations,
      [](auto &l, std::size_t) { l.sort_heap(); }, input_order);

  benchmark<Container>(
      output, container_name, "sort_shell", size, size, sort_iterations,
      [](auto &l, std::size_t) { l.sort_shell(); }, input_order);

  benchmark<Container>(
      output, container_name, "sort_tim", size, size, sort_iterations,
      [](auto &l, std::size_t) { l.sort_tim(); }, input_order);
}

template <typename Container>
void run_benchmarks_for_container(std::ofstream &output,
                                  const char *container_name) {
  const std::size_t sizes[] = {10, 100, 1000, 10000};
  const std::size_t iterations = 10;
  const InputOrder sort_orders[] = {
      InputOrder::presorted,
      InputOrder::reverse_sorted,
      InputOrder::randomized,
  };

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

    for (InputOrder order : sort_orders) {
      run_sort_benchmarks<Container>(output, container_name, size, iterations,
                                     order);
    }
  }
}

int main() {
  std::ofstream output("bench.csv");
  std::println(output, "container,operation,input_order,size,iterations,"
                       "ns_per_operation,comparisons_per_operation");

  run_benchmarks_for_container<list<TrackedInt>>(output, "list");
  run_benchmarks_for_container<forward_list<TrackedInt>>(output,
                                                         "forward_list");
  run_benchmarks_for_container<vector<TrackedInt>>(output, "vector");

  std::println("Benchmark results written to bench.csv");
}
