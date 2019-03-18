// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "SDL.h"
#include "EventListener.h"
#include "DialogScene.h"

class DialogController : public EventListener
{
 private:
    DialogScene *dialogScene_;
    bool endOfDialog_ = false;

 public:
    explicit DialogController(DialogScene *dialogScene);
    virtual void run(SDL_Event event);
    void onClick(SDL_Point p);
};
