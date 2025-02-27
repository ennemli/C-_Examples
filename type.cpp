#include <cxxabi.h>
#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T> void printType() {
  int status;
  char *realname = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
  char *decayedname =
      abi::__cxa_demangle(typeid(std::decay_t<T>).name(), 0, 0, &status);

  std::cout << "Before Decay: " << (realname ? realname : typeid(T).name());

  if (std::is_lvalue_reference<T>::value) {
    std::cout << " (L-value reference)";
  } else if (std::is_rvalue_reference<T>::value) {
    std::cout << " (R-value reference)";
  }

  if (std::is_const<std::remove_reference_t<T>>::value) {
    std::cout << " (const)";
  }

  std::cout << "\nAfter Decay: "
            << (decayedname ? decayedname : typeid(std::decay_t<T>).name())
            << "\n";
  std::cout << "----------------------------\n";

  free(realname);
  free(decayedname);
}

// Overloaded function to test type deduction
template <typename T> void printType(T &&t) {
  std::cout << "Using printType(T&&) with argument type:\n";
  printType<T>();
}

int main() {
  using T = int;

  std::cout << "Explicitly Specified Types:\n";
  printType<T>();          // int
  printType<T &>();        // int (L-value reference)
  printType<T &&>();       // int (R-value reference)
  printType<const T>();    // int (const)
  printType<const T &>();  // int (L-value reference, const)
  printType<const T &&>(); // int (R-value reference, const)

  std::cout << "\nType Deduction with Function Overload:\n";
  int x = 42;
  const int cx = 100;

  printType(x);             // L-value
  printType(std::move(x));  // R-value
  printType(cx);            // Const L-value
  printType(std::move(cx)); // Const R-value

  return 0;
}

