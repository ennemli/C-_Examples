#include <iostream>
#include <numeric>
#include <vector>
int main(int argc, char *argv[]) {
  std::vector<int> values(15);
  std::iota(values.begin(), values.end(), 0);

  int acc_value = std::accumulate(values.begin(), values.end(), 0,
                                  [](int a, int b) { return a + b; });
  std::cout << acc_value << "\n";
  return 0;
}
