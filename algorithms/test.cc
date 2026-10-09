#include <chrono>
#include <cstddef>
#include <fstream>
#include <initializer_list>
#include <iostream>

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

template <typename Operation>
void benchmark(
  std::ofstream& output,
  const char* name,
  std::size_t size,
  std::size_t iterations,
  list<TrackedInt>& values,
  Operation operation)
{
  auto start = std::chrono::steady_clock::now();

  for (std::size_t i = 0; i < iterations; ++i)
  {
    operation(values, i);
  }

  auto end = std::chrono::steady_clock::now();
  auto elapsed =
    std::chrono::duration<double, std::nano>(end - start).count();

  output << name << ',' << size << ',' << iterations << ','
         << elapsed / iterations << '\n';
}

int main()
{
  std::ofstream output("bench.csv");
  if (!output)
  {
    std::cerr << "Could not open bench.csv for writing\n";
    return 1;
  }

  output << "operation,size,iterations,ns_per_operation\n";

  const std::size_t sizes[] = {10, 100, 1000, 10000};

  for (std::size_t size : sizes)
  {
    const std::size_t iterations = 10000;
    list<TrackedInt> values{};

    for (std::size_t i = 0; i < size; ++i)
    {
      values.push_back(static_cast<int>(i));
    }

    benchmark(output, "at", size, iterations, values,
      [size](auto& l, std::size_t i) { (void)l.at(i % size); });

    benchmark(output, "operator[]", size, iterations, values,
      [size](auto& l, std::size_t i) { (void)l[i % size]; });

    benchmark(output, "front", size, iterations, values,
      [](auto& l, std::size_t) { (void)l.front(); });

    benchmark(output, "back", size, iterations, values,
      [](auto& l, std::size_t) { (void)l.back(); });

    benchmark(output, "size", size, iterations, values,
      [](auto& l, std::size_t) { (void)l.size(); });

    benchmark(output, "push_back", size, iterations, values,
      [](auto& l, std::size_t i) {
        l.push_back(static_cast<int>(i));
        l.pop_back();
      });

    benchmark(output, "pop_back", size, iterations, values,
      [](auto& l, std::size_t i) {
        l.pop_back();
        l.push_back(static_cast<int>(i));
      });

    benchmark(output, "push_front", size, iterations, values,
      [](auto& l, std::size_t i) {
        l.push_front(static_cast<int>(i));
        l.pop_front();
      });

    benchmark(output, "pop_front", size, iterations, values,
      [](auto& l, std::size_t i) {
        l.pop_front();
        l.push_front(static_cast<int>(i));
      });

    benchmark(output, "insert", size, iterations, values,
      [size](auto& l, std::size_t i) {
        l.insert(size / 2, static_cast<int>(i));
        l.pop_back();
      });

    benchmark(output, "clear_and_refill", size, iterations, values,
      [size](auto& l, std::size_t) {
        l.clear();
        for (std::size_t i = 0; i < size; ++i)
        {
          l.push_back(static_cast<int>(i));
        }
      });
  }

  std::cout << "Benchmark results written to bench.csv\n";
}
