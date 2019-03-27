// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <SDL.h>
#include <map>

template <class V>
class ResourceManager {
 protected:
  std::map<std::string, V> map_;

 public:
  ResourceManager() {}
  virtual ~ResourceManager() {}
  virtual void init(SDL_Renderer *renderer) = 0;
};
