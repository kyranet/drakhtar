// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameState.h"

void GameState::_render()
{
    // Clear the screen
    SDL_RenderClear(renderer_);

    // Render each game object
    for (auto gameObject : gameObjects_)
        gameObject->render();

    // Render the new frame
    SDL_RenderPresent(renderer_);
}

bool GameState::getexit()
{
    return _exit;
}

void GameState::_preload()
{
}

void GameState::_create()
{
}

void GameState::_update()
{
}

void GameState::_handleEvents(SDL_Event &const e)
{
    // Listen to SDL events
    if (e.type == SDL_QUIT)
    {
        _exit = true;
        // TODO(Gonzalo): Change State
    }

    for (auto listener : eventListeners_)
    {
        listener->run(e);
    }
}

void GameState::_afterUpdate()
{
}

void GameState::_events()
{
}

void GameState::_destroy()
{
    for (auto gameObject : pendingOnDestroy_)
    {
        // If the gameObject was already deleted from memory,
        // skip this search
        if (gameObject == nullptr)
            continue;

        auto it = gameObjects_.begin();
        while (it != gameObjects_.end())
        {
            if (*it == gameObject)
            {
                gameObjects_.erase(it);
                delete gameObject;
                break;
            }
            it++;
        }
    }

    pendingOnDestroy_.clear();
}

GameState::~GameState()
{
    // Clean up game objects
    for (auto gameObject : gameObjects_)
        delete gameObject;
    gameObjects_.clear();

    // Clean up event listeners
    while (!eventListeners_.empty())
    {
        EventListener *eventListener = eventListeners_.back();
        eventListeners_.pop_back();
        delete eventListener;
    }

    // Assign game to nullptr
    game_ = nullptr;
}
GameState *GameState::addEventListener(EventListener *eventListener)
{
    eventListeners_.push_back(eventListener);
    return this;
};

void GameState::addGameObject(GameObject *gameObject)
{
    gameObjects_.push_back(gameObject);
}

void GameState::removeGameObject(GameObject *gameObject)
{
    pendingOnDestroy_.push_back(gameObject);
}
