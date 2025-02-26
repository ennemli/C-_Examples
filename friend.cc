#include "a.h"
#include <iostream>

void print(const A &a) { std::cout << "here's A's value :" << a.m_a << "\n"; }
int main(int argc, char *argv[]) {
  A a(5);
  print(a);
  return 0;
}
