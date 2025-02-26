#include <iostream>

struct st {
  int value;
};
st *fun(int v) {
  st *s = new st;
  s->value = v;
  return s;
}

int main(int argc, char *argv[]) {
  int n1 = 1, n2 = 2, n3 = 3;
  std::cout << &fun << "\n";
  return 0;
}
