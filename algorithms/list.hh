#pragma once

#include <cstddef>
#include <initializer_list>

template <typename T>
class list {
  struct node {
    T value;
    node *previous;
    node *next;

    node(const T &value, node *previous = nullptr, node *next = nullptr);
  };

  node *head;
  node *tail;
  std::size_t count;

public:
  list(std::initializer_list<T> values);
  ~list();

  list(const list &) = delete;
  list &operator=(const list &) = delete;
  list(list &&) = delete;
  list &operator=(list &&) = delete;

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
};
