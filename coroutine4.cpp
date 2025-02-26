#include <coroutine>
#include <iostream>

template <typename T> struct RObj {
  struct promise_type {
    T value_;
    RObj<T> get_return_object() {
      return {.h_ = std::coroutine_handle<promise_type>::from_promise(*this)};
    };
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
    std::suspend_always yield_value(T value) {
      value_ = value;
      return {};
    }
  };
  std::coroutine_handle<promise_type> h_;
  operator std::coroutine_handle<promise_type>() { return h_; }
  operator std::coroutine_handle<>() const { return h_; }
};

RObj<int> coroutine() {
  for (int i = 0;; ++i) {
    co_yield i;
  }
}

int main(int argc, char *argv[]) {
  std::coroutine_handle<RObj<int>::promise_type> h = coroutine();
  RObj<int>::promise_type &pp = h.promise();
  for (int i = 0; i < 3; ++i) {
    std::cout << "Main loop " << pp.value_ << " times\n";
    h();
  }

  h.destroy();
  return 0;
}
