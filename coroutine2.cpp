#include <coroutine>
#include <iostream>

struct RObj {
  struct promise_type {
    RObj get_return_object() {
      return {.h_ = std::coroutine_handle<promise_type>::from_promise(*this)};
    };
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
  };
  std::coroutine_handle<promise_type> h_;
  operator std::coroutine_handle<promise_type>() { return h_; }
  operator std::coroutine_handle<>() const { return h_; }
};

RObj coroutine() {
  for (int i = 0;; ++i) {
    co_await std::suspend_always{};
    std::cout << "Coroutine resumed " << i << " times\n";
  }
}

int main(int argc, char *argv[]) {
  std::coroutine_handle<> h = coroutine();
  for (int i = 0; i < 3; ++i) {
    std::cout << "Main loop " << i << " times\n";
    h();
  }
  h.destroy();
  return 0;
}
