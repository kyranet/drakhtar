// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <map>
#include <stack>

class Font;

struct FontInfo {
  FontInfo(const std::string& name, const std::string& path, const int size,
           const int lineJumpLimit)
      : name(name), path(path), size(size), lineJumpLimit(lineJumpLimit) {}
  ~FontInfo() = default;
  const std::string name;
  const std::string path;
  const int size;
  const int lineJumpLimit;
};

class FontManager {
  static FontManager* instance_;
  FontManager();
  ~FontManager();

  std::map<std::string, Font*> map_;
  std::stack<FontInfo*> stack_;

 public:
  static FontManager* getInstance();
  static void destroy();
  static Font* get(const std::string& name);
  FontInfo* add(const std::string& name, const std::string& path, int size,
                int lineJumpLimit);
  void init();
};
