#include <future>
#include <iostream>
#include <thread>

int computeResult() {
  std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate some work
  return 42; // Return a computed result
}

int main() {
  // Launch an asynchronous operation
  std::future<int> fut = std::async(std::launch::async, computeResult);
  std::cout << fut.get() << "\n";
  std::cout << "async completed." << '\n';

  return 0;
}

