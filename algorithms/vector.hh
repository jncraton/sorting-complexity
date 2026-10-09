#pragma once

#include <cstddef>
#include <initializer_list>

template <typename T> class vector {
  T *data_ptr;
  std::size_t count;
  std::size_t cap;

  void reallocate(std::size_t new_cap);

public:
  vector();
  vector(std::initializer_list<T> values);
  ~vector();

  vector(const vector &) = delete;
  vector &operator=(const vector &) = delete;
  vector(vector &&) = delete;
  vector &operator=(vector &&) = delete;

  void push_back(const T &value);
  void push_front(const T &value);
  void pop_back();
  void pop_front();
  void insert(std::size_t index, const T &value);
  void clear();

  T &at(std::size_t index);
  const T &at(std::size_t index) const;
  T &operator[](std::size_t index);
  const T &operator[](std::size_t index) const;
  T &front();
  const T &front() const;
  T &back();
  const T &back() const;
  std::size_t size() const;

  void sort_bubble();
  void sort_insertion();
  void sort_selection();
  void sort_merge();
  void sort_quick();
  void sort_heap();
  void sort_shell();
  void sort_tim();
};
