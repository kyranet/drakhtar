// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TimePool.h"

TimePool::TimePool(const Uint32 ticksInterval, const Uint32 now)
    : ticksInterval_(ticksInterval), ticksLast_(now) {}

bool TimePool::next(const Uint32 now) {
  ticksAccumulated_ += now - ticksLast_;
  ticksLast_ = now;

  if (ticksAccumulated_ >= ticksInterval_) {
    ticksAccumulated_ %= ticksInterval_;
    return true;
  }

  return false;
}

Uint32 TimePool::getRemaining() const {
  return ticksAccumulated_ > ticksInterval_
             ? 0
             : ticksInterval_ - ticksAccumulated_;
}
