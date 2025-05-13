#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T>
class CustomVector {
 private:
  T *data_arr;
  size_t current_capacity;
  size_t current_size;

  // memory allocation strategy
  auto resize() -> void;

 public:
  // const
  const double GROWTH_FACTOR = 1.5;

  // Iterators
  using iterator = T *;
  using const_iterator = const T *;

  // Constructors & Destructors
  CustomVector();
  ~CustomVector();
  CustomVector(size_t capacity);
  CustomVector(const CustomVector &other_instance);
  CustomVector(CustomVector &&other) noexcept;

  // Assignment operator
  CustomVector &operator=(const CustomVector &other);
  CustomVector &operator=(CustomVector &&other) noexcept;

  // Core Functionality
  auto push_back(const T &element) -> void;
  auto pop_back() -> void;
  auto capacity() const -> size_t;
  auto size() const -> size_t;
  auto empty() -> bool;

  // Access Operations
  auto operator[](size_t index) -> T &;
  auto operator[](size_t index) const -> const T &;
  auto at(size_t index) -> T &;
  auto at(size_t index) const -> const T &;
  auto front() -> T &;
  auto front() const -> const T &;
  auto back() -> T &;
  auto back() const -> const T &;

  // Iterator methods
  iterator begin() { return data_arr; }
  iterator end() { return data_arr + current_size; }
  const_iterator begin() const { return data_arr; }
  const_iterator end() const { return data_arr + current_size; }
  const_iterator cbegin() const { return data_arr; }
  const_iterator cend() const { return data_arr + current_size; }
};

template <typename T>
// constructor: initializing an empty vector
CustomVector<T>::CustomVector() : current_capacity(1), current_size(0) {
  data_arr = new T[current_capacity];
}

// cleans up the memory
template <typename T>
CustomVector<T>::~CustomVector() {
  delete[] data_arr;
}

// initialize container with specified capacity
template <typename T>
CustomVector<T>::CustomVector(size_t capacity) : current_capacity(capacity), current_size(0) {
  data_arr = new T[current_capacity];
}

// handling copying user's instance
template <typename T>
CustomVector<T>::CustomVector(const CustomVector &other_instance)
    : current_capacity(other_instance.current_capacity), current_size(other_instance.current_size) {
  data_arr = new T[current_capacity];
  for (size_t i = 0; i < current_size; ++i) data_arr[i] = other_instance[i];
}

// handle self assignment: release existing memory and perform deep copy
template <typename T>
CustomVector<T> &CustomVector<T>::operator=(const CustomVector &other_instance) {
  if (this == &other_instance) return *this;

  delete[] data_arr;

  current_capacity = other_instance.current_capacity;
  current_size = other_instance.current_size;
  data_arr = new T[current_capacity];
  for (size_t i = 0; i < current_size; ++i) data_arr[i] = other_instance[i];

  return *this;
}

// Move constructor
template <typename T>
CustomVector<T>::CustomVector(CustomVector &&other) noexcept
    : data_arr(other.data_arr),
      current_capacity(other.current_capacity),
      current_size(other.current_size) {
  other.data_arr = nullptr;
  other.current_capacity = 0;
  other.current_size = 0;
}

// Move assignment operator
template <typename T>
CustomVector<T> &CustomVector<T>::operator=(CustomVector &&other) noexcept {
  if (this != &other) {
    delete[] data_arr;
    data_arr = other.data_arr;
    current_capacity = other.current_capacity;
    current_size = other.current_size;
    other.data_arr = nullptr;
    other.current_capacity = 0;
    other.current_size = 0;
  }
  return *this;
}

// resizing the Custom_Vector
template <typename T>
auto CustomVector<T>::resize() -> void {
  current_capacity *= GROWTH_FACTOR;
  T *new_data_arr = new T[current_capacity];
  for (size_t i = 0; i < current_size; ++i) new_data_arr[i] = data_arr[i];
  delete[] data_arr;
  data_arr = new_data_arr;
}

// Core Functionality

template <typename T>
auto CustomVector<T>::push_back(const T &element) -> void {
  if (current_size == current_capacity) resize();
  data_arr[current_size] = element;
  ++current_size;
}

template <typename T>
auto CustomVector<T>::pop_back() -> void {
  if (current_size > 0) --current_size;
}

template <typename T>
auto CustomVector<T>::capacity() const -> size_t {
  return current_capacity;
}

template <typename T>
auto CustomVector<T>::size() const -> size_t {
  return current_size;
}

template <typename T>
auto CustomVector<T>::empty() -> bool {
  return current_size == 0;
}

// Access Operations

template <typename T>
auto CustomVector<T>::operator[](size_t index) -> T & {
  if (index >= current_size) throw std::out_of_range("Index out of range");

  return data_arr[index];
}

template <typename T>
auto CustomVector<T>::operator[](size_t index) const -> const T & {
  if (index >= current_size) throw std::out_of_range("Index out of range");

  return data_arr[index];
}

template <typename T>
auto CustomVector<T>::at(size_t index) -> T & {
  if (index >= current_size) throw std::out_of_range("Index out of range");

  return data_arr[index];
}

template <typename T>
auto CustomVector<T>::at(size_t index) const -> const T & {
  if (index >= current_size) throw std::out_of_range("Index out of range");
  return data_arr[index];
}

template <typename T>
auto CustomVector<T>::front() -> T & {
  if (current_size == 0) throw std::out_of_range("Vector is empty");
  return data_arr[0];
}

template <typename T>
auto CustomVector<T>::front() const -> const T & {
  if (current_size == 0) throw std::out_of_range("Vector is empty");
  return data_arr[0];
}

template <typename T>
auto CustomVector<T>::back() -> T & {
  if (current_size == 0) throw std::out_of_range("Vector is empty");
  return data_arr[current_size - 1];
}

template <typename T>
auto CustomVector<T>::back() const -> const T & {
  if (current_size == 0) throw std::out_of_range("Vector is empty");
  return data_arr[current_size - 1];
}
