// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "SDL.h"

class TimePool {
 private:
  Uint32 ticksInterval_ = 0;
  Uint32 ticksAccumulated_ = 0;
  Uint32 ticksLast_ = 0;

 public:
  TimePool(Uint32 ticksInterval, Uint32 now);
  bool next(Uint32 now);
  Uint32 getRemaining() const;
};
