#include <iostream>
template <typename T> void printSize(T value) {
  // sizeof(value) will be the size of a pointer, not the array!
  std::cout << sizeof(value) << std::endl;
}

int main(int argc, char *argv[]) {
  int numbers[50];    // 200 bytes (assuming 4-byte ints)
  printSize(numbers); // Prints 4 or 8 (pointer size), not 200!

  return 0;
}
