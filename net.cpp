#include "arpa/inet.h"
#include <iostream>
int main(int argc, char *argv[]) {
  std::cout << ntohs(4090) << "\n";

  return 0;
}
