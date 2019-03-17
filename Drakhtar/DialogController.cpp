// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "DialogController.h"

DialogController::DialogController(DialogScene *dialogScene) : dialogScene_(dialogScene)
{
}

void DialogController::run(SDL_Event event)
{
    SDL_Point p = {event.motion.x, event.motion.y};

    switch (event.type)
    {
    case SDL_MOUSEBUTTONUP:
        if (!endOfDialog_)
            onClick(p);
        break;
    }
}

void DialogController::onClick(SDL_Point p)
{
    GameObject *dialogBlock = dialogScene_->getBlockSprite();

    if (SDL_PointInRect(&p, &dialogBlock->getRect()) && !endOfDialog_)
    {
        dialogScene_->nextDialog();
        if (dialogScene_->isEndOfDialog())
            endOfDialog_ = true;
    }
}
