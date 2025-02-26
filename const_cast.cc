#include <iostream>
int main(int argc, char *argv[]) {
  int a = 100;
  static_cast<int>(a) = 999;
  std::cout << a << "\n";
  return 0;
}
