#include <iostream>

template <int N> struct Fact {
  const static int V = Fact<N - 1>::V * N;
};
template <> struct Fact<0> {
  const static int V = 1;
};

int main(int argc, char *argv[]) {
  std::cout << Fact<5>::V << "\n";
  return 0;
}
