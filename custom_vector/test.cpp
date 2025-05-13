#include <algorithm>
#include <iostream>
#include <string>

#include "custom_vector.hpp"

// Helper function to print a vector's contents
template <typename T>
void print_vector(const CustomVector<T>& vec, const std::string& name) {
  std::cout << name << " (size=" << vec.size() << ", capacity=" << vec.capacity() << "): ";
  for (const auto& item : vec) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

// Test utility to report success/failure
void test_result(bool condition, const std::string& test_name) {
  std::cout << "TEST " << test_name << ": " << (condition ? "PASSED" : "FAILED") << std::endl;
}

int main() {
  std::cout << "=== CustomVector Testing ===" << std::endl;

  // Test constructors
  std::cout << "\n--- Basic Construction ---" << std::endl;
  CustomVector<int> vec1;
  test_result(vec1.size() == 0 && vec1.capacity() >= 1, "Default constructor");

  CustomVector<int> vec2(10);
  test_result(vec2.size() == 0 && vec2.capacity() == 10, "Capacity constructor");

  // Test push_back and basic operations
  std::cout << "\n--- Push Back Operations ---" << std::endl;
  for (int i = 0; i < 5; ++i) {
    vec1.push_back(i * 10);
  }
  print_vector(vec1, "vec1 after push_back");
  test_result(vec1.size() == 5, "push_back size");

  // Test access operations
  std::cout << "\n--- Access Operations ---" << std::endl;
  test_result(vec1[2] == 20, "operator[]");
  test_result(vec1.at(3) == 30, "at()");
  test_result(vec1.front() == 0, "front()");
  test_result(vec1.back() == 40, "back()");

  try {
    vec1.at(10);  // This should throw
    test_result(false, "at() bounds check");
  } catch (const std::out_of_range&) {
    test_result(true, "at() bounds check");
  }

  // Test copy operations
  std::cout << "\n--- Copy Operations ---" << std::endl;
  CustomVector<int> vec3 = vec1;  // Copy constructor
  print_vector(vec3, "vec3 after copy construction");
  test_result(vec3.size() == vec1.size(), "Copy constructor size");
  test_result(vec3[2] == vec1[2], "Copy constructor content");

  CustomVector<int> vec4;
  vec4 = vec1;  // Copy assignment
  print_vector(vec4, "vec4 after copy assignment");
  test_result(vec4.size() == vec1.size(), "Copy assignment size");

  // Test pop_back
  std::cout << "\n--- Pop Back Operations ---" << std::endl;
  vec1.pop_back();
  vec1.pop_back();
  print_vector(vec1, "vec1 after pop_back");
  test_result(vec1.size() == 3, "pop_back size");
  test_result(vec1.back() == 20, "pop_back content");

  // Test iterators
  std::cout << "\n--- Iterator Operations ---" << std::endl;
  CustomVector<int> vec5;
  for (int i = 1; i <= 5; ++i) {
    vec5.push_back(i);
  }

  // Using iterator to modify values
  for (auto it = vec5.begin(); it != vec5.end(); ++it) {
    *it *= 2;
  }
  print_vector(vec5, "vec5 after doubling");
  test_result(vec5[2] == 6, "Iterator modification");

  // Using STL algorithms with our iterators
  int sum = 0;
  std::for_each(vec5.begin(), vec5.end(), [&sum](int val) { sum += val; });
  std::cout << "Sum of vec5 elements: " << sum << std::endl;
  test_result(sum == 30, "STL algorithm compatibility");

  // Test move semantics
  std::cout << "\n--- Move Semantics ---" << std::endl;
  CustomVector<int> vec6 = std::move(vec5);  // Move constructor
  print_vector(vec6, "vec6 after move construction");
  test_result(vec5.size() == 0, "Move constructor source emptied");
  test_result(vec6.size() == 5, "Move constructor destination filled");

  CustomVector<int> vec7;
  vec7 = std::move(vec6);  // Move assignment
  print_vector(vec7, "vec7 after move assignment");
  test_result(vec6.size() == 0, "Move assignment source emptied");
  test_result(vec7.size() == 5, "Move assignment destination filled");

  // Edge cases
  std::cout << "\n--- Edge Cases ---" << std::endl;
  CustomVector<int> empty_vec;
  test_result(empty_vec.empty(), "empty() on empty vector");

  try {
    empty_vec.front();  // Should throw
    test_result(false, "front() on empty vector");
  } catch (const std::out_of_range&) {
    test_result(true, "front() on empty vector");
  }

  try {
    empty_vec.back();  // Should throw
    test_result(false, "back() on empty vector");
  } catch (const std::out_of_range&) {
    test_result(true, "back() on empty vector");
  }

  // Test with different type
  std::cout << "\n--- Different Type Testing ---" << std::endl;
  CustomVector<std::string> str_vec;
  str_vec.push_back("Hello");
  str_vec.push_back("Custom");
  str_vec.push_back("Vector");
  print_vector(str_vec, "str_vec");
  test_result(str_vec.size() == 3, "string vector size");
  test_result(str_vec[1] == "Custom", "string vector content");

  std::cout << "\n=== Testing Complete ===" << std::endl;

  return 0;
}
