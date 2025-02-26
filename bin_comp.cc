#include <cstdint>
#include <iostream>
#include <sys/types.h>
using namespace std;

int main(int argc, char *argv[]) {
  uint16_t x = 0xFFFF;
  x += static_cast<uint16_t>(0x0001);

  return 0;
}
