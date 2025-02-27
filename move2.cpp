#include <functional>
#include <iostream>
#include <vector>

void execute(std::function<void()> func) {
  func(); // Call the lambda
}

int main() {
  std::vector<int> data(10000, 5);

  auto lambda = [data = std::move(data)]() {
    std::cout << "Inside lambda, vector size: " << data.size() << '\n';
  };

  execute(lambda); // Move lambda

  std::cout << "After move, original vector size: " << data.size()
            << '\n'; // Undefined behavior?

  return 0;
}
