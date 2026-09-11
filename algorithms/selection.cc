#include <print>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> arr;
    int val;
    while (cin >> val) {
        arr.push_back(val);
    }

    long long comparisons = 0;
    auto start_time = chrono::high_resolution_clock::now();

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
            swap(arr[i], arr[min_idx]);
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;

    for (int i = 0; i < n; ++i) {
        std::print("{}{}", arr[i], (i == n - 1 ? "" : " "));
    }
    std::println("");
    std::println("Comparisons: {}", comparisons);
    std::println("Time: {} seconds", elapsed.count());

    return 0;
}
