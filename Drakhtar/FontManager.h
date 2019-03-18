// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Font.h"
#include <map>
#include <stack>


struct FontInfo
{
    FontInfo(string name, string path, int size, int lineJumpLimit)
        : name_(name), path_(path), size_(size), lineJumpLimit_(lineJumpLimit) {}
    ~FontInfo() { }
    string name_;
    string path_;
    int size_;
    int lineJumpLimit_;
};


class FontManager
{
private: 
    static FontManager * instance;
    FontManager();
    ~FontManager();

    map<string, Font*> map_;
    stack<FontInfo*> stack_;

public:
    static FontManager* getInstance();
    static void destroy();
    static Font* get(string name);
    FontInfo* add(string name, string path, int size, int lineJumpLimit);
    void init();
    
};

