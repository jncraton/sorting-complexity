#include "test.cc"

template <typename T> void sort(std::vector<T> &arr) {
  bool swapped;
  for (int i = 0; i < arr.size() - 1; ++i) {
    swapped = false;
    for (int j = 0; j < arr.size() - i - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}
