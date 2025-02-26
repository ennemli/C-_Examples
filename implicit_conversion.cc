#include <iostream>
int main(int argc, char *argv[]) {
  int &&x = 55;
  const int &ptr = std::move(x);
  ptr = 44;
  std::cout << "Ptr: " << ptr << "\n";
  std::cout << "X: " << x << "\n";
  return 0;
}
