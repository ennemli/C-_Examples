#include <coroutine>
#include <iostream>

template <typename PromiseType> struct GetPromise {
  PromiseType *p_;
  bool await_ready() const noexcept { return false; }
  bool await_suspend(std::coroutine_handle<PromiseType> h) {
    p_ = &h.promise();
    return false;
  }
  PromiseType *await_resume() { return p_; }
};
template <typename T> struct RObj {
  struct promise_type {
    T value_;
    RObj<T> get_return_object() {
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

RObj<int> coroutine() {
  auto pp = co_await GetPromise<RObj<int>::promise_type>{};
  for (int i = 0;; ++i) {
    pp->value_ = i;
    co_await std::suspend_always{};
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
