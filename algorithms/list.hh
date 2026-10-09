#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template <typename T> class list {
private:
  struct node {
    T value;
    node *previous;
    node *next;

    node(const T &value) : value(value), previous(nullptr), next(nullptr) {}
  };

  node *first = nullptr;
  node *last = nullptr;
  std::size_t count = 0;

public:
  list(std::initializer_list<T> values) {
    for (const T &value : values) {
      push_back(value);
    }
  }

  list(const list &) = delete;
  list &operator=(const list &) = delete;

  ~list() { clear(); }

  T &at(std::size_t index) {
    if (index >= count) {
      throw std::out_of_range("list index out of range");
    }

    node *current = first;
    for (std::size_t i = 0; i < index; ++i) {
      current = current->next;
    }

    return current->value;
  }

  T &operator[](std::size_t index) { return at(index); }

  T &front() {
    if (first == nullptr) {
      throw std::out_of_range("front of empty list");
    }

    return first->value;
  }

  T &back() {
    if (last == nullptr) {
      throw std::out_of_range("back of empty list");
    }

    return last->value;
  }

  std::size_t size() { return count; }

  void clear() {
    node *current = first;

    while (current != nullptr) {
      node *next = current->next;
      delete current;
      current = next;
    }

    first = nullptr;
    last = nullptr;
    count = 0;
  }

  void insert(std::size_t index, const T &value) {
    if (index > count) {
      throw std::out_of_range("list index out of range");
    }

    if (index == count) {
      push_back(value);
      return;
    }

    node *current = first;
    for (std::size_t i = 0; i < index; ++i) {
      current = current->next;
    }

    node *added = new node(value);
    added->next = current;
    added->previous = current->previous;

    if (current->previous != nullptr) {
      current->previous->next = added;
    } else {
      first = added;
    }

    current->previous = added;
    ++count;
  }

  void push_back(const T &value) {
    node *added = new node(value);

    if (last == nullptr) {
      first = added;
      last = added;
    } else {
      added->previous = last;
      last->next = added;
      last = added;
    }

    ++count;
  }

  void pop_back() {
    if (last == nullptr) {
      throw std::out_of_range("pop_back on empty list");
    }

    node *removed = last;
    last = last->previous;

    if (last == nullptr) {
      first = nullptr;
    } else {
      last->next = nullptr;
    }

    delete removed;
    --count;
  }

  void push_front(const T &value) {
    node *added = new node(value);

    if (first == nullptr) {
      first = added;
      last = added;
    } else {
      added->next = first;
      first->previous = added;
      first = added;
    }

    ++count;
  }

  void pop_front() {
    if (first == nullptr) {
      throw std::out_of_range("pop_front on empty list");
    }

    node *removed = first;
    first = first->next;

    if (first == nullptr) {
      last = nullptr;
    } else {
      first->previous = nullptr;
    }

    delete removed;
    --count;
  }
};
