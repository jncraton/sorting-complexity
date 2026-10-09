#include <chrono>
#include <cstddef>
#include <fstream>
#include <print>

#include "list.hh"

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

template <typename Setup, typename Operation, typename Cleanup>
void benchmark(
  std::ofstream& output,
  const char* name,
  std::size_t size,
  std::size_t iterations,
  list<TrackedInt>& values,
  Setup setup,
  Operation operation,
  Cleanup cleanup)
{
  std::chrono::duration<double, std::nano> elapsed{};

  for (std::size_t i = 0; i < iterations; ++i)
  {
    setup(values, i);

    auto start = std::chrono::steady_clock::now();
    operation(values, i);
    auto end = std::chrono::steady_clock::now();

    elapsed += end - start;
    cleanup(values, i);
  }

  std::println(output, "{},{},{},{}",
             name, size, iterations, elapsed.count() / iterations);
}

int main()
{
  std::ofstream output("bench.csv");
  std::println(output, "operation,size,iterations,ns_per_operation");

  const std::size_t sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
  const auto noop = [](auto&, std::size_t) {};

  for (std::size_t size : sizes)
  {
    const std::size_t iterations = 100;
    list<TrackedInt> values{};

    for (std::size_t i = 0; i < size; ++i)
    {
      values.push_back(static_cast<int>(i));
    }

    benchmark(output, "at", size, iterations, values, noop,
      [size](auto& l, std::size_t i) { (void)l.at(i % size); }, noop);

    benchmark(output, "operator[]", size, iterations, values, noop,
      [size](auto& l, std::size_t i) { (void)l[i % size]; }, noop);

    benchmark(output, "front", size, iterations, values, noop,
      [](auto& l, std::size_t) { (void)l.front(); }, noop);

    benchmark(output, "back", size, iterations, values, noop,
      [](auto& l, std::size_t) { (void)l.back(); }, noop);

    benchmark(output, "size", size, iterations, values, noop,
      [](auto& l, std::size_t) { (void)l.size(); }, noop);

    benchmark(output, "push_back", size, iterations, values, noop,
      [](auto& l, std::size_t i) { l.push_back(static_cast<int>(i)); },
      [](auto& l, std::size_t) { l.pop_back(); });

    benchmark(output, "pop_back", size, iterations, values,
      [](auto& l, std::size_t i) { l.push_back(static_cast<int>(i)); },
      [](auto& l, std::size_t) { l.pop_back(); }, noop);

    benchmark(output, "push_front", size, iterations, values, noop,
      [](auto& l, std::size_t i) { l.push_front(static_cast<int>(i)); },
      [](auto& l, std::size_t) { l.pop_front(); });

    benchmark(output, "pop_front", size, iterations, values,
      [](auto& l, std::size_t i) { l.push_front(static_cast<int>(i)); },
      [](auto& l, std::size_t) { l.pop_front(); }, noop);

    benchmark(output, "insert", size, iterations, values, noop,
      [size](auto& l, std::size_t i) {
        l.insert(size / 2, static_cast<int>(i));
      },
      [](auto& l, std::size_t) { l.pop_back(); });

    values.clear();

    benchmark(output, "clear", size, iterations, values,
      [size](auto& l, std::size_t) {
        for (std::size_t i = 0; i < size; ++i)
        {
          l.push_back(static_cast<int>(i));
        }
      },
      [](auto& l, std::size_t) { l.clear(); },
      noop);
  }

  std::println("Benchmark results written to bench.csv");
}
