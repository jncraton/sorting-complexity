#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class forward_list {
  struct node {
    T value;
    node *next;

    node(const T &value, node *next = nullptr) : value(value), next(next) {}
  };

  node *head;
  std::size_t count;

public:
  forward_list() : head(nullptr), count(0) {}

  forward_list(std::initializer_list<T> values) : head(nullptr), count(0) {
    for (const T &value : values) {
      push_back(value);
    }
  }

  ~forward_list() { clear(); }

  forward_list(const forward_list &) = delete;
  forward_list &operator=(const forward_list &) = delete;
  forward_list(forward_list &&) = delete;
  forward_list &operator=(forward_list &&) = delete;

  void push_back(const T &value) {
    node *added = new node(value, nullptr);
    if (!head) {
      head = added;
    } else {
      node *current = head;
      while (current->next) {
        current = current->next;
      }
      current->next = added;
    }
    ++count;
  }

  void push_front(const T &value) {
    node *added = new node(value, head);
    head = added;
    ++count;
  }

  void pop_back() {
    if (!head) {
      throw std::out_of_range("pop_back on empty forward_list");
    }
    if (!head->next) {
      delete head;
      head = nullptr;
    } else {
      node *current = head;
      while (current->next->next) {
        current = current->next;
      }
      delete current->next;
      current->next = nullptr;
    }
    --count;
  }

  void pop_front() {
    if (!head) {
      throw std::out_of_range("pop_front on empty forward_list");
    }
    node *removed = head;
    head = head->next;
    delete removed;
    --count;
  }

  void insert(std::size_t index, const T &value) {
    if (index > count) {
      throw std::out_of_range("insert index out of range");
    }
    if (index == 0) {
      push_front(value);
      return;
    }
    node *current = head;
    for (std::size_t i = 0; i < index - 1; ++i) {
      current = current->next;
    }
    node *added = new node(value, current->next);
    current->next = added;
    ++count;
  }

  void clear() {
    while (head) {
      node *removed = head;
      head = head->next;
      delete removed;
    }
    count = 0;
  }

  T &at(std::size_t index) {
    if (index >= count) {
      throw std::out_of_range("forward_list index out of range");
    }
    node *current = head;
    for (std::size_t i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->value;
  }

  const T &at(std::size_t index) const {
    if (index >= count) {
      throw std::out_of_range("forward_list index out of range");
    }
    node *current = head;
    for (std::size_t i = 0; i < index; ++i) {
      current = current->next;
    }
    return current->value;
  }

  T &operator[](std::size_t index) { return at(index); }
  const T &operator[](std::size_t index) const { return at(index); }

  T &front() {
    if (!head) {
      throw std::out_of_range("front on empty forward_list");
    }
    return head->value;
  }

  const T &front() const {
    if (!head) {
      throw std::out_of_range("front on empty forward_list");
    }
    return head->value;
  }

  T &back() {
    if (!head) {
      throw std::out_of_range("back on empty forward_list");
    }
    node *current = head;
    while (current->next) {
      current = current->next;
    }
    return current->value;
  }

  const T &back() const {
    if (!head) {
      throw std::out_of_range("back on empty forward_list");
    }
    node *current = head;
    while (current->next) {
      current = current->next;
    }
    return current->value;
  }

  std::size_t size() const { return count; }

  void sort_bubble() {
    if (count < 2) return;
    bool swapped;
    do {
      swapped = false;
      node *current = head;
      while (current && current->next) {
        if (current->next->value < current->value) {
          T temp = current->value;
          current->value = current->next->value;
          current->next->value = temp;
          swapped = true;
        }
        current = current->next;
      }
    } while (swapped);
  }

  void sort_insertion() {
    if (count < 2) return;
    node *sorted = nullptr;
    node *current = head;
    while (current) {
      node *next = current->next;
      if (!sorted || sorted->value >= current->value) {
        current->next = sorted;
        sorted = current;
      } else {
        node *curr = sorted;
        while (curr->next && curr->next->value < current->value) {
          curr = curr->next;
        }
        current->next = curr->next;
        curr->next = current;
      }
      current = next;
    }
    head = sorted;
  }

  void sort_selection() {
    if (count < 2) return;
    for (node *i = head; i && i->next; i = i->next) {
      node *min_node = i;
      for (node *j = i->next; j; j = j->next) {
        if (j->value < min_node->value) {
          min_node = j;
        }
      }
      if (min_node != i) {
        T temp = i->value;
        i->value = min_node->value;
        min_node->value = temp;
      }
    }
  }

  void sort_merge() {}
  void sort_quick() {}
  void sort_heap() {}
  void sort_shell() {}
  void sort_tim() {}
};
