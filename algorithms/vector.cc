#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

template <typename T>
class vector {
  T *data_ptr;
  std::size_t count;
  std::size_t cap;

  void reallocate(std::size_t new_cap) {
    if (new_cap < count) new_cap = count;
    if (new_cap == 0) new_cap = 1;
    T *new_data = new T[new_cap];
    for (std::size_t i = 0; i < count; ++i) {
      new_data[i] = std::move(data_ptr[i]);
    }
    delete[] data_ptr;
    data_ptr = new_data;
    cap = new_cap;
  }

public:
  vector() : data_ptr(nullptr), count(0), cap(0) {}

  vector(std::initializer_list<T> values) : data_ptr(nullptr), count(0), cap(0) {
    reallocate(values.size());
    for (const T &value : values) {
      data_ptr[count++] = value;
    }
  }

  ~vector() { delete[] data_ptr; }

  vector(const vector &) = delete;
  vector &operator=(const vector &) = delete;
  vector(vector &&) = delete;
  vector &operator=(vector &&) = delete;

  void push_back(const T &value) {
    if (count >= cap) {
      reallocate(cap == 0 ? 1 : cap * 2);
    }
    data_ptr[count++] = value;
  }

  void push_front(const T &value) {
    insert(0, value);
  }

  void pop_back() {
    if (count == 0) {
      throw std::out_of_range("pop_back on empty vector");
    }
    --count;
  }

  void pop_front() {
    if (count == 0) {
      throw std::out_of_range("pop_front on empty vector");
    }
    for (std::size_t i = 0; i < count - 1; ++i) {
      data_ptr[i] = std::move(data_ptr[i + 1]);
    }
    --count;
  }

  void insert(std::size_t index, const T &value) {
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

  void clear() {
    count = 0;
  }

  T &at(std::size_t index) {
    if (index >= count) {
      throw std::out_of_range("vector index out of range");
    }
    return data_ptr[index];
  }

  const T &at(std::size_t index) const {
    if (index >= count) {
      throw std::out_of_range("vector index out of range");
    }
    return data_ptr[index];
  }

  T &operator[](std::size_t index) { return data_ptr[index]; }
  const T &operator[](std::size_t index) const { return data_ptr[index]; }

  T &front() {
    if (count == 0) {
      throw std::out_of_range("front on empty vector");
    }
    return data_ptr[0];
  }

  const T &front() const {
    if (count == 0) {
      throw std::out_of_range("front on empty vector");
    }
    return data_ptr[0];
  }

  T &back() {
    if (count == 0) {
      throw std::out_of_range("back on empty vector");
    }
    return data_ptr[count - 1];
  }

  const T &back() const {
    if (count == 0) {
      throw std::out_of_range("back on empty vector");
    }
    return data_ptr[count - 1];
  }

  std::size_t size() const { return count; }

  void sort_bubble() {
    if (count < 2) return;
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

  void sort_insertion() {
    if (count < 2) return;
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

  void sort_selection() {
    if (count < 2) return;
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

  void sort_merge() {}
  void sort_quick() {}
  void sort_heap() {}
  void sort_shell() {}
  void sort_tim() {}
};
