// Copyright 2014 the sasq64/tween authors. All rights reserved. MIT license.
// (https://github.com/sasq64/tween)

#pragma once
#include <cmath>
#include <functional>
#include <limits>
#include <memory>
#include <mutex>
#include <vector>
#include "callback.h"

namespace tween {

class Tween;

template <typename C, typename R>
using IsCompound = typename std::enable_if<std::is_compound<C>::value, R>::type;

struct TweenAttrBase {
  virtual ~TweenAttrBase() = default;
  virtual void set(double v, Tween& t) = 0;
  virtual bool compare(void* p) { return false; }
  double delay = 0.0;
};

template <typename T>
struct TweenAttr final : TweenAttrBase {
  TweenAttr(T* target, T value, int cycles)
      : startValue(*target),
        delta(value - *target),
        maxValue(std::numeric_limits<T>::max()),
        target(target) {
    if (cycles != 1) {
      maxValue = delta + 1;
      delta = (delta + 1) * cycles - 1;
    }
  }

  T startValue;
  T delta;
  T maxValue;

  T* target;

  utils::CallbackCaller<T&, Tween, double> onUpdateCb;

  void set(double v, Tween& t) override {
    T newValue = startValue + static_cast<T>(fmod(v * delta, maxValue));
    if (newValue != *target) {
      *target = newValue;
      onUpdateCb.call(*target, t, v);
    }
  }

  bool compare(void* p) override { return p == static_cast<void*>(target); }
};

template <typename T>
class TweenT;

struct TweenImpl {
  TweenImpl(const double t, const std::function<double(double)> f,
            const bool it = true)
      : startTime(t), totalTime(0), speed(0), tween_func(f), isTweening(it) {}

  ~TweenImpl();

  double startTime;
  double totalTime;
  double speed;

  bool doRep = false;
  bool backTo = false;

  std::vector<std::shared_ptr<TweenAttrBase>> args;
  std::function<double(double)> tween_func;
  utils::CallbackCaller<Tween&, double> on_complete_cb;
  std::vector<std::shared_ptr<void>> refs;

  bool isTweening = true;

  bool step();
};

class Tween {
 protected:
  explicit Tween(std::shared_ptr<TweenImpl> i);

 public:
  explicit Tween(int dummy = 0);
  // Tween& operator=(const Tween &other) = delete;
  // Tween(const Tween& other) = delete;

  static Tween make();

  void start() const;

  Tween& seconds(float s);
  Tween& speed(float s);
  Tween& linear();
  Tween& smoothstep();
  Tween& easeinback();
  Tween& easeoutback();
  Tween& easeinsine();
  Tween& easeoutsine();
  Tween& sine();
  Tween& repeating();

  // template <typename T, class = typename
  // std::enable_if<std::is_compound<T>::value>::type>
  template <typename T>
  IsCompound<T, Tween&> to(T& target, T value, int cycles = 1) {
    for (auto i = 0; i < target.size(); i++) {
      to(target[i], value[i], cycles);
    }
    return *this;
  }

  template <typename T, typename U>
  TweenT<T> to(T& target, U value, int cycles = 1) {
    std::lock_guard<std::mutex> guard(tweenMutex_);
    auto* targetp = &target;
    for (auto& t : allTweens_) {
      auto it = t->args.begin();
      while (it != t->args.end()) {
        if ((*it)->compare(static_cast<void*>(targetp))) {
          // Already tweening this value
          it = t->args.erase(it);
        } else
          ++it;
      }
    }

    auto taptr =
        std::make_shared<TweenAttr<T>>(targetp, static_cast<T>(value), cycles);
    impl_->args.emplace_back(taptr);
    return TweenT<T>(impl_, taptr);
  }

  // template <typename T, class = typename
  // std::enable_if<std::is_compound<T>::value>::type>
  template <typename T>
  IsCompound<T, Tween&> from(T& target, T value) {
    for (int i = 0; i < target.size(); i++) {
      from(target[i], value[i]);
    }
    return *this;
  }

  template <typename T, typename U>
  TweenT<T> from(T& target, U value) {
    T realValue = target;
    target = value;
    return to(target, realValue);
  }

  template <typename OBJ>
  void retain(std::shared_ptr<OBJ> obj) {
    impl_->refs.push_back(std::shared_ptr<void>(obj));
  }

  template <typename T, typename U>
  TweenT<T> fromTo(T& target, U v0, U v1, int cycles = 1) {
    *target = static_cast<T>(v0);
    return to(target, v1);
  }

  template <typename T, typename U>
  TweenT<T> fromTo(T v0, U v1, int cycles = 1) {
    auto p = std::make_shared<T>(v0);
    retain(p);
    return to(*(p.get()), v1);
  }

  template <typename F>
  Tween& onComplete(F&& f) {
    impl_->on_complete_cb.callme(std::forward<F>(f));
    return *this;
  }

  void cancel() const;
  void finish();

  static int updateTweens(double t);
  static void addTween(const TweenImpl& ti);

 protected:
  static double linear_fn(double t);
  static double smoothStep_fn(double t);
  static double easeInSine_fn(double t);
  static double easeOutSine_fn(double t);
  static double easeInOutSine_fn(double t);
  static double easeInBack_fn(double t);
  static double easeOutBack_fn(double t);
  static double easeInOutBack_fn(double t);
  static double sine_fn(double t);

  std::shared_ptr<TweenImpl> impl_;

 public:
  static double currentTime_;
  static std::vector<std::shared_ptr<TweenImpl>> allTweens_;
  static std::mutex tweenMutex_;
};

template <typename T>
class TweenT : public Tween {
 public:
  TweenT(const std::shared_ptr<TweenImpl> i, std::shared_ptr<TweenAttr<T>> ta)
      : Tween(i), ta_(ta) {}

  TweenT(const TweenT& t) { impl_ = t.impl_; }

  template <typename F>
  TweenT& onUpdate(F&& f) {
    ta_->on_update_cb.callme(std::forward<F>(f));
    return *this;
  }

  TweenT& delay(float d) {
    ta_->delay = d;
    return *this;
  }

  std::shared_ptr<TweenAttr<T>> ta_;
};

};  // namespace tween
