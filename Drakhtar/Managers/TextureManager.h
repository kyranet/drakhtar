// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <list>
#include <map>
#include "../Structures/Texture.h"
#include "ResourceManager.h"

class TimePool;

class TextureManager final : public ResourceManager<Texture*> {
  struct Pool {
    TimePool *timePool;
    std::list<Texture*> textures;
  };

  static TextureManager* instance_;
  TextureManager();
  ~TextureManager();
  std::map<Uint16, Pool> pools_{};

  bool hasPool(Uint16 frameRate);
  void removePool(Uint16 frameRate);
  void ensurePool(Uint16 frameRate);

 public:
  Texture* add(const std::string& name, const std::string& path, Uint16 columns,
                   Uint16 rows);
  void tick();
  void init();

  void switchPool(Uint16 previous, Uint16 now, Texture* texture);

  static Texture* get(const std::string& name);
  static TextureManager* getInstance();
  static void destroy();
};
