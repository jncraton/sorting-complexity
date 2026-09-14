#include <print>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> arr;
    int val;
    while (std::cin >> val) {
        arr.push_back(val);
    }

    long long comparisons = 0;
    auto start_time = std::chrono::high_resolution_clock::now();

    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
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
