// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include <map>
#include "../Structures/Texture.h"
#include "ResourceManager.h"

class TimePool;

class TextureManager final : public ResourceManager<Texture*> {
  static TextureManager* instance_;
  TextureManager();
  ~TextureManager();

 public:
  Texture* add(const std::string& name, const std::string& path, Uint16 columns,
                   Uint16 rows);
  void tick();
  void init();

  static Texture* get(const std::string& name);
  static TextureManager* getInstance();
  static void destroy();
};
