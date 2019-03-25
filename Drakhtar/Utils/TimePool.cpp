// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "TimePool.h"
#include <algorithm>

TimePool::TimePool(Uint32 ticksInterval, Uint32 now)
    : ticksInterval_(ticksInterval), ticksLast_(now), ticksAccumulated_(0) {}

bool TimePool::next(Uint32 now) {
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
