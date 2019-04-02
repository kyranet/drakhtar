// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.
// Work derived from https://github.com/photonstorm/phaser, all credits to
// photonstorm and its contributors.

#pragma once
#include <functional>
#include "Managers/TweenManager.h"
#include "Utils/Vector2D.h"

enum class TweenState {
  CREATED,
  INIT,
  DELAY,
  OFFSET_DELAY,
  HOLD_DELAY,
  REPEAT_DELAY,
  COMPLETE,
  PENDING_ADD,
  PAUSED,
  LOOP_DELAY,
  ACTIVE,
  COMPLETE_DELAY,
  PENDING_REMOVE,
  REMOVED
};

class Tween final {
  /**
   * \brief A reference to the parent of this Tween.
   */
  TweenManager* tweenManager_ = nullptr;
  Vector2D<double> from_;
  Vector2D<double> to_;
  /**
   * \brief The amount of times to loop this Tween, -1 for infinite loop.
   */
  int loop_ = 0;
  /**
   * \brief Time in frames before the tween loops.
   */
  int loopDelay_ = 0;
  /**
   * \brief The amount of loops left to run.
   */
  int loopCounter_ = 0;
  /**
   * \brief The time in frames before the 'onComplete' event fires. This never
   * fires if loop_ = -1.
   */
  int completeDelay_ = 0;
  /**
   * \brief Countdown timer.
   */
  int countdown_ = 0;
  /**
   * \brief The current state of the tween.
   */
  TweenState state_ = TweenState::PENDING_ADD;
  /**
   * \brief The state of the tween when it was paused (used by resume).
   */
  TweenState pausedState_ = TweenState::PENDING_ADD;
  /**
   * \brief Whether or not the tween is paused.
   */
  bool paused_ = false;
  /**
   * \brief The elapsed time in frames of this run through the tween.
   */
  int elapsed_ = 0;
  /**
   * \brief The total elapsed time in frames of the entire tween, including
   * looping.
   */
  int totalElapsed_ = 0;
  /**
   * \brief The time in frames for the whole tween to play through once,
   * excluding loo amounts and loop delays.
   */
  int duration_ = 0;
  /**
   * \brief Value between 0 and 1. The amount through the tween, excluding
   * loops.
   */
  double progress_ = 0;
  /**
   * \brief The time in frames for the whole tween to complete, including
   * looping.
   */
  int totalDuration_ = 0;
  /**
   * \brief Value between 0 and 1. The amount through the entire tween,
   * including loops.
   */
  double totalProgress_ = 0;

  std::function<void()> onComplete_ = nullptr;
  std::function<void()> onLoop_ = nullptr;
  std::function<void()> onRepeat_ = nullptr;
  std::function<void()> onStart_ = nullptr;
  std::function<void(Vector2D<double>)> onUpdate_ = nullptr;

  void calculateDuration();

 public:
  explicit Tween(TweenManager* tweenManager);
  ~Tween();
  Tween* from(const Vector2D<int>& start);
  Tween* to(const Vector2D<int>& end);
  Tween* setLoops(int loops);
  Tween* play();
  Tween* restart();
  Tween* pause();
  Tween* resume();
  Tween* seek(double position);
  Tween* complete(int delay = 0);
  Tween* remove();
  Tween* stop(double position = -1.0);

  Tween* setOnComplete(const std::function<void()>& callback);
  Tween* setOnLoop(const std::function<void()>& callback);
  Tween* setOnRepeat(const std::function<void()>& callback);
  Tween* setOnStart(const std::function<void()>& callback);
  Tween* setOnUpdate(const std::function<void(Vector2D<double>)>& callback);
  Tween* setState(TweenState state);

  Tween* setDuration(int duration);
  int getDuration() const;

  bool init();
  void update();

  bool isPlaying() const;
  bool isPaused() const;
  TweenState getState() const;
};
