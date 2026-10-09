#include "list.hh"
#include "trackedint.hh"
#include <cassert>
#include <iostream>
#include <stdexcept>

void test_initializer_list_and_size() {
  std::cout << "Running test_initializer_list_and_size..." << std::endl;
  list<int> l = {10, 20, 30};
  assert(l.size() == 3);
  assert(l.front() == 10);
  assert(l.back() == 30);
  std::cout << "Passed test_initializer_list_and_size." << std::endl;
}

void test_push_back() {
  std::cout << "Running test_push_back..." << std::endl;
  list<int> l{};
  assert(l.size() == 0);
  l.push_back(1);
  assert(l.size() == 1);
  assert(l.front() == 1);
  assert(l.back() == 1);
  l.push_back(2);
  l.push_back(3);
  assert(l.size() == 3);
  assert(l.front() == 1);
  assert(l.back() == 3);
  assert(l[0] == 1);
  assert(l[1] == 2);
  assert(l[2] == 3);
  std::cout << "Passed test_push_back." << std::endl;
}

void test_push_front() {
  std::cout << "Running test_push_front..." << std::endl;
  list<int> l{};
  l.push_front(1);
  assert(l.size() == 1);
  assert(l.front() == 1);
  assert(l.back() == 1);
  l.push_front(2);
  l.push_front(3);
  assert(l.size() == 3);
  assert(l.front() == 3);
  assert(l.back() == 1);
  assert(l[0] == 3);
  assert(l[1] == 2);
  assert(l[2] == 1);
  std::cout << "Passed test_push_front." << std::endl;
}

void test_pop_back() {
  std::cout << "Running test_pop_back..." << std::endl;
  list<int> l = {10, 20, 30};
  l.pop_back();
  assert(l.size() == 2);
  assert(l.back() == 20);
  l.pop_back();
  assert(l.size() == 1);
  assert(l.back() == 10);
  l.pop_back();
  assert(l.size() == 0);

  bool exception_thrown = false;
  try {
    l.pop_back();
  } catch (const std::out_of_range &e) {
    exception_thrown = true;
  }
  assert(exception_thrown);
  std::cout << "Passed test_pop_back." << std::endl;
}

void test_pop_front() {
  std::cout << "Running test_pop_front..." << std::endl;
  list<int> l = {10, 20, 30};
  l.pop_front();
  assert(l.size() == 2);
  assert(l.front() == 20);
  l.pop_front();
  assert(l.size() == 1);
  assert(l.front() == 30);
  l.pop_front();
  assert(l.size() == 0);

  bool exception_thrown = false;
  try {
    l.pop_front();
  } catch (const std::out_of_range &e) {
    exception_thrown = true;
  }
  assert(exception_thrown);
  std::cout << "Passed test_pop_front." << std::endl;
}

void test_insert() {
  std::cout << "Running test_insert..." << std::endl;
  list<int> l = {10, 30};
  l.insert(1, 20); // {10, 20, 30}
  assert(l.size() == 3);
  assert(l[0] == 10);
  assert(l[1] == 20);
  assert(l[2] == 30);

  l.insert(0, 5); // {5, 10, 20, 30}
  assert(l.size() == 4);
  assert(l[0] == 5);
  assert(l.front() == 5);

  l.insert(4, 40); // {5, 10, 20, 30, 40}
  assert(l.size() == 5);
  assert(l[4] == 40);
  assert(l.back() == 40);

  bool exception_thrown = false;
  try {
    l.insert(10, 99);
  } catch (const std::out_of_range &e) {
    exception_thrown = true;
  }
  assert(exception_thrown);
  std::cout << "Passed test_insert." << std::endl;
}

void test_clear() {
  std::cout << "Running test_clear..." << std::endl;
  list<int> l = {1, 2, 3};
  assert(l.size() == 3);
  l.clear();
  assert(l.size() == 0);
  l.clear(); // clearing empty list
  assert(l.size() == 0);
  std::cout << "Passed test_clear." << std::endl;
}

void test_accessors_at_and_operator_brackets() {
  std::cout << "Running test_accessors_at_and_operator_brackets..."
            << std::endl;
  list<int> l = {100, 200, 300};
  assert(l.at(0) == 100);
  assert(l.at(1) == 200);
  assert(l.at(2) == 300);

  assert(l[0] == 100);
  assert(l[1] == 200);
  assert(l[2] == 300);

  l.at(1) = 250;
  assert(l.at(1) == 250);

  l[2] = 350;
  assert(l[2] == 350);

  const auto &cl = l;
  assert(cl.at(0) == 100);
  assert(cl[1] == 250);

  bool exception_thrown = false;
  try {
    l.at(3);
  } catch (const std::out_of_range &e) {
    exception_thrown = true;
  }
  assert(exception_thrown);

  exception_thrown = false;
  try {
    cl.at(3);
  } catch (const std::out_of_range &e) {
    exception_thrown = true;
  }
  assert(exception_thrown);

  std::cout << "Passed test_accessors_at_and_operator_brackets." << std::endl;
}

void test_front_and_back_accessors() {
  std::cout << "Running test_front_and_back_accessors..." << std::endl;
  list<int> l = {10, 20, 30};
  assert(l.front() == 10);
  assert(l.back() == 30);

  l.front() = 15;
  l.back() = 35;
  assert(l.front() == 15);
  assert(l.back() == 35);

  const auto &cl = l;
  assert(cl.front() == 15);
  assert(cl.back() == 35);

  list<int> empty_l;
  bool exception_thrown = false;
  try {
    empty_l.front();
  } catch (const std::out_of_range &e) {
    exception_thrown = true;
  }
  assert(exception_thrown);

  exception_thrown = false;
  try {
    empty_l.back();
  } catch (const std::out_of_range &e) {
    exception_thrown = true;
  }
  assert(exception_thrown);

  const auto &empty_cl = empty_l;
  exception_thrown = false;
  try {
    empty_cl.front();
  } catch (const std::out_of_range &e) {
    exception_thrown = true;
  }
  assert(exception_thrown);

  exception_thrown = false;
  try {
    empty_cl.back();
  } catch (const std::out_of_range &e) {
    exception_thrown = true;
  }
  assert(exception_thrown);

  std::cout << "Passed test_front_and_back_accessors." << std::endl;
}

int main() {
  std::cout << "=== Starting List Test Harness ===" << std::endl;
  test_initializer_list_and_size();
  test_push_back();
  test_push_front();
  test_pop_back();
  test_pop_front();
  test_insert();
  test_clear();
  test_accessors_at_and_operator_brackets();
  test_front_and_back_accessors();
  std::cout << "=== All Tests Passed Successfully! ===" << std::endl;
  return 0;
}
