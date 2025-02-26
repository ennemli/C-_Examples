#include <atomic>
#include <iostream>
#include <thread>

int counter = 0;

void inc() {
  for (int i = 0; i < 1000; ++i) {
    counter++;
  }
}

int main(int argc, char *argv[]) {
  std::thread t1(inc);
  std::thread t2(inc);
  std::thread t3(inc);

  t1.join();
  t2.join();
  t3.join();

  std::cout << counter << "\n";
  return 0;
}
