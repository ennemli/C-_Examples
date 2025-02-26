#pragma once

#include <iostream>
class A {
private:
  int m_a;

public:
  A(int a) : m_a(a) {}
  friend void print(const A &a);
};
