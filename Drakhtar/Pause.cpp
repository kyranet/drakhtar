// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Pause.h"
#include "State.h"
#include "Game.h"

Pause::Pause(Game *game, SDL_Renderer *renderer) : GameState(game, renderer), renderer_(renderer), game_(game)
{
    _preload();
}

Pause::~Pause()
{
}

void Pause::_preload()
{
    gameObjectsPause_.push_back(new GameObject(TextureManager::get("Pause-Panel"),
                                Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                                Vector2D<int>(400, 500)));
    Restart = new Button(TextureManager::get("Button-Restart"), WIN_WIDTH / 2, 250, 225, 100,
                         RestartGame, game_, renderer_);
    gameObjectsPause_.push_back(Restart);
    Exit = new Button(TextureManager::get("Button-Exit"), WIN_WIDTH / 2, 350, 225, 100,
                      ExitGame, game_, renderer_);
    gameObjectsPause_.push_back(Exit);
}

void Pause::_render()
{
    // Render each game object
    for (auto gameObject : gameObjectsPause_)
        gameObject->render();

    // Render the new frame
    SDL_RenderPresent(renderer_);
}

void Pause::_handleEvents(SDL_Event e)
{
    Restart->handleEvents(e);
    Exit->handleEvents(e);
}

void Pause::RestartGame(Game *game, SDL_Renderer *renderer)
{
    game->getStateMachine()->pushState(new State(game, renderer));
}

void Pause::ExitGame(Game *game, SDL_Renderer *renderer)
{
    game->getStateMachine()->pushState(new MainMenu(game, renderer));
}
