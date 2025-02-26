#include <bitset>
#include <iostream>
#include <string>
int main(int argc, char *argv[]) {
  short n = static_cast<short>(std::stoi(argv[1]));
  std::bitset<16> bit(n);
  std::cout << "bit " << n << " : " << bit << " Size: " << sizeof(n) << "\n";
  if (n & 0xFFFF0000) {
    std::cout << "overflow occured\n";
  } else {
    std::cout << "overflow not occured\n";
  }
  return 0;
}
