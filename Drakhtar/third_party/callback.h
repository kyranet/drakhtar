// Copyright 2014 the sasq64/tween authors. All rights reserved. MIT license.
// (https://github.com/sasq64/tween)

#include <functional>
#include <memory>
#include <utility>
#include <vector>

namespace utils {

template <typename T, typename R>
using require_fn0 =
    typename std::conditional<false, decltype(std::declval<T>()()), R>::type;
template <typename T, typename R>
using require_fn1 =
    typename std::conditional<false, decltype(std::declval<T>()(0)), R>::type;
template <typename T, typename R>
using require_fn2 =
    typename std::conditional<false, decltype(std::declval<T>()(0, 0)),
                              R>::type;
template <typename T, typename R>
using require_fn3 =
    typename std::conditional<false, decltype(std::declval<T>()(0, 0, 0)),
                              R>::type;
template <typename T, typename R>
using require_fn4 =
    typename std::conditional<false, decltype(std::declval<T>()(0, 0, 0, 0)),
                              R>::type;

template <typename... A>
struct FCallerBase {
  virtual ~FCallerBase() = default;
  virtual void call(const A&... a) = 0;
};

template <typename T, typename... A>
struct FCaller0 final : FCallerBase<A...> {
  explicit FCaller0(const T& t) : t(t) {}
  explicit FCaller0(T&& t) : t(std::move(t)) {}

  void call(const A&... a) override {
    // std::tuple<A...> args(a...);
    t();
  }
  T t;
};

template <typename T, typename... A>
struct FCaller1 final : FCallerBase<A...> {
  explicit FCaller1(const T& t) : t(t) {}
  explicit FCaller1(T&& t) : t(std::move(t)) {}

  void call(const A&... a) override {
    std::tuple<A...> args(a...);
    t(std::get<0>(args));
  }
  T t;
};

template <typename T, typename... A>
struct FCaller2 final : FCallerBase<A...> {
  explicit FCaller2(T&& t) : t(std::move(t)) {}
  explicit FCaller2(const T& t) : t(t) {}

  void call(const A&... a) override {
    std::tuple<A...> args(a...);
    t(std::get<0>(args), std::get<1>(args));
  }
  T t;
};

template <typename T, typename... A>
struct FCaller3 final : FCallerBase<A...> {
  explicit FCaller3(T&& t) : t(std::move(t)) {}
  explicit FCaller3(const T& t) : t(t) {}

  void call(const A&... a) override {
    std::tuple<A...> args(a...);
    t(std::get<0>(args), std::get<1>(args), std::get<2>(args));
  }
  T t;
};

template <typename... A>
class CallbackCaller {
 public:
  template <typename T>
  require_fn3<T, void> callme(T&& t) {
    auto s = std::make_shared<
        FCaller3<typename std::remove_reference<T>::type, A...>>(
        std::forward<T>(t));
    callbacks.push_back(s);
    return {};
  }

  template <typename T>
  require_fn2<T, void> callme(T&& t) {
    auto s = std::make_shared<
        FCaller2<typename std::remove_reference<T>::type, A...>>(
        std::forward<T>(t));
    callbacks.push_back(s);
    return {};
  }

  template <typename T>
  require_fn1<T, void> callme(T&& t) {
    auto s = std::make_shared<
        FCaller1<typename std::remove_reference<T>::type, A...>>(
        std::forward<T>(t));
    callbacks.push_back(s);
    return {};
  }

  template <typename T>
  require_fn0<T, void> callme(T&& t) {
    auto s = std::make_shared<
        FCaller0<typename std::remove_reference<T>::type, A...>>(
        std::forward<T>(t));
    callbacks.push_back(s);
    return {};
  }

  void call(const A&... a) {
    for (auto& cb : callbacks) {
      cb->call(a...);
    }
  }

  std::vector<std::shared_ptr<FCallerBase<A...>>> callbacks;
};

}  // namespace utils
