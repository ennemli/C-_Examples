#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
  std::vector<int> source(17);
  std::iota(source.begin(), source.end(), -8);

  std::vector<int> dest;
  auto pow = [](int x) { return x * x; };
  std::transform(source.begin(), source.end(), std::back_inserter(dest), pow);
  std::for_each(dest.begin(), dest.end(),
                [](int x) { std::cout << x << "\n"; });
  int accumulated_value =
      std::accumulate(dest.begin(), dest.end(), 0, std::plus<int>{});
  std::cout << "Accumulated dest's values: " << accumulated_value << "\n";
  return 0;
}
