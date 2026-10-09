#include "forward_list.hh"
#include "list.hh"
#include "vector.hh"
#include "trackedint.hh"
#include <cassert>
#include <iostream>
#include <stdexcept>

template <typename Container>
void run_tests_for(const std::string &container_name) {
  std::cout << "=== Starting tests for " << container_name << " ===" << std::endl;

  // initializer_list & size
  {
    Container l = {10, 20, 30};
    assert(l.size() == 3);
    assert(l.front() == 10);
    assert(l.back() == 30);
  }

  // push_back
  {
    Container l{};
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
  }

  // push_front
  {
    Container l{};
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
  }

  // pop_back
  {
    Container l = {10, 20, 30};
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
  }

  // pop_front
  {
    Container l = {10, 20, 30};
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
  }

  // insert
  {
    Container l = {10, 30};
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
  }

  // clear
  {
    Container l = {1, 2, 3};
    assert(l.size() == 3);
    l.clear();
    assert(l.size() == 0);
    l.clear(); // clearing empty container
    assert(l.size() == 0);
  }

  // accessors at and operator[]
  {
    Container l = {100, 200, 300};
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
  }

  // front and back accessors
  {
    Container l = {10, 20, 30};
    assert(l.front() == 10);
    assert(l.back() == 30);

    l.front() = 15;
    l.back() = 35;
    assert(l.front() == 15);
    assert(l.back() == 35);

    const auto &cl = l;
    assert(cl.front() == 15);
    assert(cl.back() == 35);

    Container empty_l;
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
  }

  std::cout << "=== All tests passed for " << container_name << " ===" << std::endl;
}

int main() {
  std::cout << "=== Starting Comprehensive Test Harness ===" << std::endl;
  run_tests_for<list<int>>("list");
  run_tests_for<forward_list<int>>("forward_list");
  run_tests_for<vector<int>>("vector");
  std::cout << "=== All Tests Passed Successfully Across All Containers! ===" << std::endl;
  return 0;
}
