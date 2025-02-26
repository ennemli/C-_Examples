#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
std::mutex m;
int counter;

void inc(int s) {
  std::lock_guard<std::mutex> lock(m);
  std::this_thread::sleep_for(std::chrono::seconds(s));
  ++counter;
}

int main(int argc, char *argv[]) {
  std::vector<std::thread> threads_list;
  for (int i = 0; i < 10; ++i) {
    threads_list.push_back(std::thread(inc, i));
  }
  for (auto &t : threads_list) {
    t.join();
  }
  std::cout << "Counter: " << counter << "\n";
  return 0;
}
