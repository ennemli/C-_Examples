#include <coroutine>
#include <iostream>

struct RObj {
  struct promise_type {
    RObj get_return_object() { return {}; }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
  };
};
struct Awaiter {
  std::coroutine_handle<> *hp_;
  constexpr bool await_ready() const noexcept { return false; }
  void await_suspend(std::coroutine_handle<> h) noexcept {
    if (hp_) {
      *hp_ = h;
      hp_ = nullptr;
    }
  };
  constexpr void await_resume() const noexcept {}
};

RObj coroutine(std::coroutine_handle<> *continuation_out) {
  Awaiter a{continuation_out};
  for (int i = 0;; ++i) {
    co_await a;
    std::cout << "Coroutine resumed " << i << " times\n";
  }
}

int main(int argc, char *argv[]) {
  std::coroutine_handle<> h;
  coroutine(&h);
  for (int i = 0; i < 3; ++i) {
    std::cout << "Main loop " << i << " times\n";
    h();
  }
  h.destroy();
  return 0;
}
