#include "list.hh"

#include <stdexcept>

#include "trackedint.hh"

template <typename T>
list<T>::node::node(const T &value, node *previous, node *next)
    : value(value), previous(previous), next(next) {}

template <typename T>
list<T>::list() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
list<T>::list(std::initializer_list<T> values)
    : head(nullptr), tail(nullptr), count(0) {
  for (const T &value : values) {
    push_back(value);
  }
}

template <typename T> list<T>::~list() { clear(); }

template <typename T> void list<T>::push_back(const T &value) {
  node *added = new node(value, tail, nullptr);

  if (tail) {
    tail->next = added;
  } else {
    head = added;
  }

  tail = added;
  ++count;
}

template <typename T> void list<T>::push_front(const T &value) {
  node *added = new node(value, nullptr, head);

  if (head) {
    head->previous = added;
  } else {
    tail = added;
  }

  head = added;
  ++count;
}

template <typename T> void list<T>::pop_back() {
  if (!tail) {
    throw std::out_of_range("pop_back on empty list");
  }

  node *removed = tail;
  tail = tail->previous;

  if (tail) {
    tail->next = nullptr;
  } else {
    head = nullptr;
  }

  delete removed;
  --count;
}

template <typename T> void list<T>::pop_front() {
  if (!head) {
    throw std::out_of_range("pop_front on empty list");
  }

  node *removed = head;
  head = head->next;

  if (head) {
    head->previous = nullptr;
  } else {
    tail = nullptr;
  }

  delete removed;
  --count;
}

template <typename T> void list<T>::insert(std::size_t index, const T &value) {
  if (index > count) {
    throw std::out_of_range("insert index out of range");
  }

  if (index == 0) {
    push_front(value);
    return;
  }

  if (index == count) {
    push_back(value);
    return;
  }

  node *current = head;
  for (std::size_t i = 0; i < index; ++i) {
    current = current->next;
  }

  node *added = new node(value, current->previous, current);
  current->previous->next = added;
  current->previous = added;
  ++count;
}

template <typename T> void list<T>::clear() {
  while (head) {
    node *removed = head;
    head = head->next;
    delete removed;
  }

  tail = nullptr;
  count = 0;
}

template <typename T> T &list<T>::at(std::size_t index) {
  if (index >= count) {
    throw std::out_of_range("list index out of range");
  }

  node *current = head;
  for (std::size_t i = 0; i < index; ++i) {
    current = current->next;
  }

  return current->value;
}

template <typename T> const T &list<T>::at(std::size_t index) const {
  if (index >= count) {
    throw std::out_of_range("list index out of range");
  }

  node *current = head;
  for (std::size_t i = 0; i < index; ++i) {
    current = current->next;
  }

  return current->value;
}

template <typename T> T &list<T>::operator[](std::size_t index) {
  return at(index);
}

template <typename T> const T &list<T>::operator[](std::size_t index) const {
  return at(index);
}

template <typename T> T &list<T>::front() {
  if (!head) {
    throw std::out_of_range("front on empty list");
  }

  return head->value;
}

template <typename T> const T &list<T>::front() const {
  if (!head) {
    throw std::out_of_range("front on empty list");
  }

  return head->value;
}

template <typename T> T &list<T>::back() {
  if (!tail) {
    throw std::out_of_range("back on empty list");
  }

  return tail->value;
}

template <typename T> const T &list<T>::back() const {
  if (!tail) {
    throw std::out_of_range("back on empty list");
  }

  return tail->value;
}

template <typename T> std::size_t list<T>::size() const { return count; }

template <typename T> void list<T>::sort_bubble() {}

template <typename T> void list<T>::sort_insertion() {}

template <typename T> void list<T>::sort_selection() {}

template <typename T> void list<T>::sort_merge() {}

template <typename T> void list<T>::sort_quick() {}

template <typename T> void list<T>::sort_heap() {}

template <typename T> void list<T>::sort_shell() {}

template <typename T> void list<T>::sort_tim() {}

template class list<TrackedInt>;
template class list<int>;
