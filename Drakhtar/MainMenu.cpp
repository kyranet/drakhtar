// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "MainMenu.h"

MainMenu::MainMenu(Game *game, SDL_Renderer *renderer) : GameState(game, renderer), game_(game), renderer_(renderer)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::_preload()
{
    gameObjects_.push_back(new GameObject(TextureManager::get("Maps-Test"),
                                          Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                                          Vector2D<int>(WIN_WIDTH, WIN_HEIGHT)));
    Play = new Button(TextureManager::get("Button-Play"),
                      WIN_WIDTH / 2, 250, 200, 75, Play_game, game_, renderer_);
    gameObjects_.push_back(Play);
    Options = new Button(TextureManager::get("Button-Options"),
                         WIN_WIDTH / 2, 350, 200, 75, Options_game, game_, renderer_);
    gameObjects_.push_back(Options);
}

void MainMenu::Play_game(Game *game, SDL_Renderer *renderer)
{
    cout << "Play";
    game->getStateMachine()->pushState(new State(game, renderer));
}

void MainMenu::Options_game(Game *game, SDL_Renderer *renderer)
{
    cout << "Options";
}

void MainMenu::_handleEvents(SDL_Event const &e)
{
    while (!_exit && SDL_PollEvent(&e))
    {
        Play->handleEvents(e);
        Options->handleEvents(e);
        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_e:
                // game_->getStateMachine()->pushState(new State(game_, renderer_));
                break;
            }
        }

        // For each game object, run the event handler
        for (auto gameObject : gameObjects_)
            gameObject->handleEvents(e);

        GameState::_handleEvents(e);
    }
}
