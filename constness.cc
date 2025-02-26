#include <iostream>
int main(int argc, char *argv[]) {
  const int *ptr1 = new int(42); // pointer to const int
  int *ptr2 = const_cast<int *>(
      ptr1); // Casting away constness (dangerous, don't do this!)
  *ptr2 = 999;
  std::cout << *ptr1 << "-" << *ptr2 << "\n";
  return 0;
}
