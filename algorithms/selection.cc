#include <algorithm>
#include <chrono>
#include <iostream>
#include <print>
#include <vector>

int main() {
  std::vector<int> arr;
  int val;
  while (std::cin >> val) {
    arr.push_back(val);
  }

  long long comparisons = 0;
  auto start_time = std::chrono::high_resolution_clock::now();

  int n = arr.size();
  for (int i = 0; i < n - 1; ++i) {
    int min_idx = i;
    for (int j = i + 1; j < n; ++j) {
      comparisons++;
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      std::swap(arr[i], arr[min_idx]);
    }
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;

  for (int i = 0; i < n; ++i) {
    std::println("{}", arr[i]);
  }
  std::println("");
  std::println("Comparisons: {}", comparisons);
  std::println("Time: {} seconds", elapsed.count());

  return 0;
}
