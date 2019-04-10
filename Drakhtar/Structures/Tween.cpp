// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
// Work derived from https://github.com/photonstorm/phaser, all credits to
// photonstorm and its contributors.

#include "Tween.h"
#include <algorithm>

Tween::Tween(TweenManager* tweenManager) : tweenManager_(tweenManager) {}
Tween::~Tween() = default;

Tween* Tween::from(const Vector2D<int>& start) {
  from_.set(static_cast<double>(start.getX()),
            static_cast<double>(start.getY()));
  return this;
}

Tween* Tween::to(const Vector2D<int>& end) {
  to_.set(static_cast<double>(end.getX()), static_cast<double>(end.getY()));
  return this;
}

Tween* Tween::setRoute(const std::vector<Vector2D<double>>& route) {
  route_ = route;
  return this;
}

Tween* Tween::setLoops(const int loops) {
  loop_ = loops;
  return this;
}

Tween* Tween::play() {
  if (state_ == TweenState::ACTIVE) return this;
  if (state_ == TweenState::PENDING_REMOVE || state_ == TweenState::REMOVED) {
    init();
    tweenManager_->makeActive(this);
  }
  if (paused_) {
    paused_ = false;
    tweenManager_->makeActive(this);
  } else {
    state_ = TweenState::ACTIVE;
    if (onStart_ != nullptr) onStart_();
    tweenManager_->makeActive(this);
  }
  return this;
}

Tween* Tween::resume() {
  if (state_ == TweenState::PAUSED) {
    paused_ = false;
    state_ = pausedState_;
  } else {
    play();
  }
  return this;
}

Tween* Tween::restart() {
  if (state_ == TweenState::REMOVED) {
    seek(0);
  } else {
    stop();
    play();
  }
  return this;
}

Tween* Tween::pause() {
  if (state_ == TweenState::PAUSED) {
    paused_ = true;
    pausedState_ = state_;
    state_ = TweenState::PAUSED;
  }
  return this;
}

Tween* Tween::seek(const double position) {
  progress_ = position;
  return this;
}

Tween* Tween::complete(const int delay) {
  if (delay) {
    countdown_ = delay;
    state_ = TweenState::COMPLETE_DELAY;
  } else {
    if (onComplete_ != nullptr) onComplete_();
    state_ = TweenState::PENDING_REMOVE;
  }
  return this;
}

Tween* Tween::remove() {
  tweenManager_->remove(this);
  return this;
}

Tween* Tween::stop(const double position) {
  if (state_ == TweenState::ACTIVE) {
    if (position != -1) seek(position);
  }

  if (state_ != TweenState::REMOVED) {
    if (state_ == TweenState::PAUSED || state_ == TweenState::PENDING_ADD) {
      tweenManager_->remove(this);
    }
    state_ = TweenState::PENDING_REMOVE;
  }

  return this;
}

bool Tween::init() {
  calculateDuration();
  progress_ = 0;
  totalProgress_ = 0;
  elapsed_ = 0;
  totalElapsed_ = 0;

  if (paused_) {
    state_ = TweenState::PENDING_ADD;
    pausedState_ = TweenState::INIT;
    return false;
  }

  state_ = TweenState::INIT;
  return true;
}

Tween* Tween::setOnComplete(const std::function<void()>& callback) {
  onComplete_ = callback;
  return this;
}
Tween* Tween::setOnLoop(const std::function<void()>& callback) {
  onLoop_ = callback;
  return this;
}
Tween* Tween::setOnRepeat(const std::function<void()>& callback) {
  onRepeat_ = callback;
  return this;
}
Tween* Tween::setOnStart(const std::function<void()>& callback) {
  onStart_ = callback;
  return this;
}
Tween* Tween::setOnUpdate(
    const std::function<void(Vector2D<double>)>& callback) {
  onUpdate_ = callback;
  return this;
}
Tween* Tween::setState(const TweenState state) {
  state_ = state;
  return this;
}

Tween* Tween::setDuration(const int duration) {
  duration_ = duration;
  return this;
}

int Tween::getDuration() const { return duration_; }

void Tween::update() {
  if (isPaused()) return;
  elapsed_++;
  progress_ = std::min(
      static_cast<double>(elapsed_) / static_cast<double>(duration_), 1.0);

  totalElapsed_++;
  totalProgress_ = std::min(totalElapsed_ / totalDuration_, 1);

  switch (state_) {
    case TweenState::ACTIVE: {
      if (elapsed_ == duration_) {
        if (loopCounter_ > 0) {
          elapsed_ = 0;
          progress_ = 0;
          --loopCounter_;
          if (onLoop_ != nullptr) onLoop_();
          if (loopDelay_ > 0) {
            countdown_ = loopDelay_;
            state_ = TweenState::LOOP_DELAY;
          } else {
            state_ = TweenState::ACTIVE;
          }
        } else if (completeDelay_ > 0) {
          countdown_ = completeDelay_;
          state_ = TweenState::COMPLETE_DELAY;
        } else {
          if (onComplete_ != nullptr) onComplete_();
          state_ = TweenState::PENDING_REMOVE;
        }
      }
      break;
    }
    case TweenState::LOOP_DELAY: {
      if (--countdown_ <= 0) state_ = TweenState::ACTIVE;
      break;
    }
    case TweenState::OFFSET_DELAY: {
      if (--countdown_ <= 0) {
        if (onStart_ != nullptr) onStart_();
        state_ = TweenState::ACTIVE;
      }
      break;
    }
    case TweenState::COMPLETE_DELAY: {
      if (--countdown_ <= 0) {
        if (onComplete_ != nullptr) onComplete_();
        state_ = TweenState::PENDING_REMOVE;
      }
      break;
    }
    default:
      break;
  }

  if (state_ == TweenState::ACTIVE) {
    double x, y;
    if (route_.empty()) {
      x = (to_.getX() - from_.getX()) * progress_ + from_.getX();
      y = (to_.getY() - from_.getY()) * progress_ + from_.getY();
    } else {
      const auto progress = route_.size() * progress_;
      const auto node = std::floor(progress);
      const auto next = std::ceil(progress);
      const auto nodeRoute = route_[static_cast<int>(node)];

      // Handle last frame
      if (next == route_.size()) {
        x = nodeRoute.getX();
        y = nodeRoute.getY();
      } else {
        const auto nextRoute = route_[static_cast<int>(next)];
        const auto transition = progress - node;
        x = (nextRoute.getX() - nodeRoute.getX()) * transition +
            nodeRoute.getX();
        y = (nextRoute.getY() - nodeRoute.getY()) * transition +
            nodeRoute.getY();
      }
    }

    onUpdate_({x, y});
  }
}

bool Tween::isPlaying() const { return state_ == TweenState::ACTIVE; }

bool Tween::isPaused() const { return state_ == TweenState::PAUSED; }

TweenState Tween::getState() const { return state_; }

void Tween::calculateDuration() {
  loopCounter_ = loop_;
  if (loopCounter_ > 0) {
    totalDuration_ =
        duration_ + completeDelay_ + (duration_ + loopDelay_) * loopCounter_;
  } else if (loopCounter_ == 0) {
    totalDuration_ = duration_ + completeDelay_;
  } else {
    totalDuration_ = -1;
  }
}
