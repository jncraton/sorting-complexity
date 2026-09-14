#include "test.cc"

template <typename T>
void sort(std::vector<T>& arr) {
  for (int i = 0; i < arr.size() - 1; ++i) {
    int min_idx = i;
    for (int j = i + 1; j < arr.size(); ++j) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      std::swap(arr[i], arr[min_idx]);
    }
  }
}
