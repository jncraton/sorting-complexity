#include "vector.hh"

#include <algorithm>
#include <stdexcept>

#include "trackedint.hh"

template <typename T> void vector<T>::reallocate(std::size_t new_cap) {
  if (new_cap < count)
    new_cap = count;
  if (new_cap == 0)
    new_cap = 1;
  T *new_data = new T[new_cap];
  for (std::size_t i = 0; i < count; ++i) {
    new_data[i] = std::move(data_ptr[i]);
  }
  delete[] data_ptr;
  data_ptr = new_data;
  cap = new_cap;
}

template <typename T>
vector<T>::vector() : data_ptr(nullptr), count(0), cap(0) {}

template <typename T>
vector<T>::vector(std::initializer_list<T> values)
    : data_ptr(nullptr), count(0), cap(0) {
  reallocate(values.size());
  for (const T &value : values) {
    data_ptr[count++] = value;
  }
}

template <typename T> vector<T>::~vector() { delete[] data_ptr; }

template <typename T> void vector<T>::push_back(const T &value) {
  if (count >= cap) {
    reallocate(cap == 0 ? 1 : cap * 2);
  }
  data_ptr[count++] = value;
}

template <typename T> void vector<T>::push_front(const T &value) {
  insert(0, value);
}

template <typename T> void vector<T>::pop_back() {
  if (count == 0) {
    throw std::out_of_range("pop_back on empty vector");
  }
  --count;
}

template <typename T> void vector<T>::pop_front() {
  if (count == 0) {
    throw std::out_of_range("pop_front on empty vector");
  }
  for (std::size_t i = 0; i < count - 1; ++i) {
    data_ptr[i] = std::move(data_ptr[i + 1]);
  }
  --count;
}

template <typename T>
void vector<T>::insert(std::size_t index, const T &value) {
  if (index > count) {
    throw std::out_of_range("insert index out of range");
  }
  if (count >= cap) {
    reallocate(cap == 0 ? 1 : cap * 2);
  }
  for (std::size_t i = count; i > index; --i) {
    data_ptr[i] = std::move(data_ptr[i - 1]);
  }
  data_ptr[index] = value;
  ++count;
}

template <typename T> void vector<T>::clear() { count = 0; }

template <typename T> T &vector<T>::at(std::size_t index) {
  if (index >= count) {
    throw std::out_of_range("vector index out of range");
  }
  return data_ptr[index];
}

template <typename T> const T &vector<T>::at(std::size_t index) const {
  if (index >= count) {
    throw std::out_of_range("vector index out of range");
  }
  return data_ptr[index];
}

template <typename T> T &vector<T>::operator[](std::size_t index) {
  return data_ptr[index];
}

template <typename T> const T &vector<T>::operator[](std::size_t index) const {
  return data_ptr[index];
}

template <typename T> T &vector<T>::front() {
  if (count == 0) {
    throw std::out_of_range("front on empty vector");
  }
  return data_ptr[0];
}

template <typename T> const T &vector<T>::front() const {
  if (count == 0) {
    throw std::out_of_range("front on empty vector");
  }
  return data_ptr[0];
}

template <typename T> T &vector<T>::back() {
  if (count == 0) {
    throw std::out_of_range("back on empty vector");
  }
  return data_ptr[count - 1];
}

template <typename T> const T &vector<T>::back() const {
  if (count == 0) {
    throw std::out_of_range("back on empty vector");
  }
  return data_ptr[count - 1];
}

template <typename T> std::size_t vector<T>::size() const { return count; }

template <typename T> void vector<T>::sort_bubble() {
  if (count < 2)
    return;
  for (std::size_t i = 0; i < count - 1; ++i) {
    for (std::size_t j = 0; j < count - i - 1; ++j) {
      if (data_ptr[j + 1] < data_ptr[j]) {
        T temp = std::move(data_ptr[j]);
        data_ptr[j] = std::move(data_ptr[j + 1]);
        data_ptr[j + 1] = std::move(temp);
      }
    }
  }
}

template <typename T> void vector<T>::sort_insertion() {
  if (count < 2)
    return;
  for (std::size_t i = 1; i < count; ++i) {
    T key = std::move(data_ptr[i]);
    long long j = static_cast<long long>(i) - 1;
    while (j >= 0 && key < data_ptr[j]) {
      data_ptr[j + 1] = std::move(data_ptr[j]);
      j--;
    }
    data_ptr[j + 1] = std::move(key);
  }
}

template <typename T> void vector<T>::sort_selection() {
  if (count < 2)
    return;
  for (std::size_t i = 0; i < count - 1; ++i) {
    std::size_t min_idx = i;
    for (std::size_t j = i + 1; j < count; ++j) {
      if (data_ptr[j] < data_ptr[min_idx]) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      T temp = std::move(data_ptr[i]);
      data_ptr[i] = std::move(data_ptr[min_idx]);
      data_ptr[min_idx] = std::move(temp);
    }
  }
}

template <typename T> void vector<T>::sort_merge() {}
template <typename T> void vector<T>::sort_quick() {}
template <typename T> void vector<T>::sort_heap() {}
template <typename T> void vector<T>::sort_shell() {}
template <typename T> void vector<T>::sort_tim() {}

template class vector<TrackedInt>;
template class vector<int>;
