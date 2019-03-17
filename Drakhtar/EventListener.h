// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

class EventListener
{
 public:
    EventListener(){}
    virtual ~EventListener(){}
    virtual void run(SDL_Event event) = 0;
};
