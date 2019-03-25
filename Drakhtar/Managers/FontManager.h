// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include <map>
#include <stack>

class Font;

struct FontInfo
{
    FontInfo(std::string name, std::string path, int size, int lineJumpLimit)
        : name_(name), path_(path), size_(size), lineJumpLimit_(lineJumpLimit) {}
    ~FontInfo() { }
    std::string name_;
    std::string path_;
    int size_;
    int lineJumpLimit_;
};


class FontManager
{
 private:
    static FontManager * instance;
    FontManager();
    ~FontManager();

    std::map<std::string, Font*> map_;
    std::stack<FontInfo*> stack_;

 public:
    static FontManager* getInstance();
    static void destroy();
    static Font* get(std::string name);
    FontInfo* add(std::string name, std::string path, int size, int lineJumpLimit);
    void init();
};


