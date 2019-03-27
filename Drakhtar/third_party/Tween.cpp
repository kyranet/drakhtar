// Copyright 2014 the sasq64/tween authors. All rights reserved. MIT license.
// (https://github.com/sasq64/tween)

#include "Tween.h"
#include <utility>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace tween {

std::vector<std::shared_ptr<TweenImpl>> Tween::allTweens_;
double Tween::currentTime_ = 0;
std::mutex Tween::tweenMutex_;

double Tween::linear_fn(const double t) { return t; }

double Tween::smoothStep_fn(const double t) { return (t * t * (3 - 2 * t)); }

double Tween::easeInSine_fn(const double t) { return 1 - cos(t * (M_PI / 2)); }

double Tween::sine_fn(double t) {
  return (sin(t * (M_PI * 2) - M_PI / 2) + 1.0) / 2.0;
}

double Tween::easeOutSine_fn(const double t) { return sin(t * (M_PI / 2)); }

double Tween::easeInOutSine_fn(const double t) {
  return -0.5 * (cos(M_PI * t) - 1);
}

double Tween::easeInBack_fn(const double t) {
  const auto s = 1.70158;
  return t * t * ((s + 1) * t - s);
}

double Tween::easeOutBack_fn(double t) {
  const auto s = 1.70158;
  t--;
  return (t * t * ((s + 1) * t + s) + 1);
}

double Tween::easeInOutBack_fn(double t) {
  const auto s = 1.70158 * 1.525;
  // double s2 = s * 1.525f;
  t *= 2;
  if (t < 1) return 1.0 / 2 * (t * t * ((s + 1) * t - s));
  const auto postFix = t -= 2;
  return 1.0 / 2 * ((postFix)*t * ((s + 1) * t + s) + 2);
}

TweenImpl::~TweenImpl() {
  if (!isTweening) {
    Tween::addTween(*this);
  }
}

Tween Tween::make() {
  return Tween(std::make_shared<TweenImpl>(currentTime_, smoothStep_fn, false));
}

void Tween::addTween(const TweenImpl &ti) {
  std::lock_guard<std::mutex> guard(tweenMutex_);
  allTweens_.push_back(std::make_shared<TweenImpl>(ti));
  allTweens_.back()->isTweening = true;
}

void Tween::cancel() const {
  std::lock_guard<std::mutex> guard(tweenMutex_);

  auto it = Tween::allTweens_.begin();
  while (it != Tween::allTweens_.end()) {
    if (*it == impl_) {
      Tween::allTweens_.erase(it);
      break;
    }
    ++it;
  }
}

bool TweenImpl::step() {
  size_t ended = 0;
  Tween tween;
  for (auto &a : args) {
    auto t = static_cast<float>((Tween::currentTime_ - startTime - a->delay) /
                                totalTime);
    if (t < 0.0) continue;
    if (t > 1.0) {
      if (doRep)
        t -= 1.0;
      else if (backTo) {
        ended++;
        a->set(0.0, tween);
      } else {
        ended++;
        a->set(1.0, tween);
        continue;
      }
    }
    a->set(tween_func(t), tween);
  }
  return ended < args.size();
}

int Tween::updateTweens(double t) {
  std::lock_guard<std::mutex> guard(tweenMutex_);

  static std::vector<std::shared_ptr<TweenImpl>> doneTweens;

  currentTime_ = t;
  auto it = allTweens_.begin();
  while (it != allTweens_.end()) {
    if (!(*it)->step()) {
      doneTweens.push_back(*it);
      it = allTweens_.erase(it);
    } else {
      ++it;
    }
  }

  for (auto &dt : doneTweens) {
    Tween tw;
    dt->on_complete_cb.call(tw, 1.0);
  }
  doneTweens.clear();

  return static_cast<int>(allTweens_.size());
}

Tween::Tween(int dummy)
    : impl_(std::make_shared<TweenImpl>(currentTime_, smoothStep_fn)) {}

Tween::Tween(std::shared_ptr<TweenImpl> i) : impl_(std::move(i)) {}

void Tween::finish() {
  for (auto &a : impl_->args) {
    a->set(1.0, *this);
  }
  cancel();
}

Tween &Tween::seconds(const float s) {
  impl_->totalTime = s;
  return *this;
}

Tween &Tween::speed(const float s) {
  impl_->speed = s;
  return *this;
}

Tween &Tween::linear() {
  impl_->tween_func = linear_fn;
  return *this;
}

Tween &Tween::smoothstep() {
  impl_->tween_func = smoothStep_fn;
  return *this;
}

Tween &Tween::easeinback() {
  impl_->tween_func = easeInBack_fn;
  return *this;
}

Tween &Tween::easeoutback() {
  impl_->tween_func = easeOutBack_fn;
  return *this;
}

Tween &Tween::easeinsine() {
  impl_->tween_func = easeInSine_fn;
  return *this;
}

Tween &Tween::easeoutsine() {
  impl_->tween_func = easeOutSine_fn;
  return *this;
}

Tween &Tween::sine() {
  impl_->tween_func = sine_fn;
  impl_->backTo = true;
  return *this;
}

Tween &Tween::repeating() {
  impl_->doRep = true;
  return *this;
}

void Tween::start() const {
  if (!impl_->isTweening) {
    impl_->startTime = currentTime_;
    std::lock_guard<std::mutex> guard(tweenMutex_);
    allTweens_.push_back(impl_);
    allTweens_.back()->isTweening = true;
  }
}

}  // namespace tween
