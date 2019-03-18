// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Game.h"
#include "SDLError.h"

Game::Game()
    : window_(nullptr), renderer_(nullptr)
{
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
    {
        string message = string("Error initializing SDL.\nReason: ") + SDL_GetError();
        throw new SDLError(message);
    }

    if (TTF_Init() != 0)
    {
        string message = string("Error initializing TTF.\nReason: ") + TTF_GetError();
        throw new SDLError(message);
    }

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0)
    {
        string message = string("Error initializing MIX.\nReason: ") + Mix_GetError();
        throw new SDLError(message);
    }

    // Units
    textureManager_->add("Units-BlueArcher", "../images/Units/BlueArcher.png", 2, 1, SDL_FLIP_HORIZONTAL);
    textureManager_->add("Units-BlueKnight", "../images/Units/BlueKnight.png", 2, 1, SDL_FLIP_HORIZONTAL);
    textureManager_->add("Units-BlueMage", "../images/Units/BlueMage.png", 2, 1, SDL_FLIP_HORIZONTAL);
    textureManager_->add("Units-BlueMonster", "../images/Units/BlueMonster.png", 2, 1, SDL_FLIP_HORIZONTAL);
    textureManager_->add("Units-BlueSoldier", "../images/Units/BlueSoldier.png", 2, 1, SDL_FLIP_HORIZONTAL);
    textureManager_->add("Units-BlueValar", "../images/Units/BlueValar.png", 2, 1, SDL_FLIP_HORIZONTAL);
    textureManager_->add("Units-Thassa", "../images/Units/Thassa.png", 2, 1, SDL_FLIP_HORIZONTAL);
    textureManager_->add("Units-Abeizhul", "../images/Units/Abeizhul.png", 2, 1);
    textureManager_->add("Units-Dreilay", "../images/Units/Dreilay.png", 2, 1);
    textureManager_->add("Units-RedArcher", "../images/Units/RedArcher.png", 2, 1);
    textureManager_->add("Units-RedKnight", "../images/Units/RedKnight.png", 2, 1);
    textureManager_->add("Units-RedMage", "../images/Units/RedMage.png", 2, 1);
    textureManager_->add("Units-RedMonster", "../images/Units/RedMonster.png", 2, 1);
    textureManager_->add("Units-RedSoldier", "../images/Units/RedSoldier.png", 2, 1);
    textureManager_->add("Units-Sheissa", "../images/Units/Sheissa.png", 2, 1);
    textureManager_->add("Units-Valar", "../images/Units/Valar.png", 2, 1);
    textureManager_->add("Units-Zamdran", "../images/Units/Zamdran.png", 2, 1);

    // UI
    textureManager_->add("UI-cellFrame", "../images/UI/cellFrame.png", 1, 1);
    textureManager_->add("UI-cellHover", "../images/UI/cellHover.png", 1, 1);
    textureManager_->add("UI-cellInRange", "../images/UI/cellInRange.png", 1, 1);
    textureManager_->add("UI-enemyInRange", "../images/UI/enemyInRange.png", 1, 1);
    textureManager_->add("UI-dialogueBackground", "../images/UI/dialogueBackground.png", 1, 1);
    textureManager_->add("UI-turnBar", "../images/UI/turnBar.png", 1, 1);

    // Button
    textureManager_->add("Button-Play", "../images/MainMenu/Play_Button.png", 1, 1);
    textureManager_->add("Button-Options", "../images/MainMenu/Options_Button.png", 1, 1);
    textureManager_->add("Button-Pause", "../images/Pause/Pause_Button.png", 1, 1);
    textureManager_->add("Button-Resume", "../images/Pause/Resume_Button.png", 1, 1);
    textureManager_->add("Button-Restart", "../images/Pause/Restart_Button.png", 1, 1);
    textureManager_->add("Button-Exit", "../images/Pause/Exit_Button.png", 1, 1);

    // Pause
    textureManager_->add("Pause-Panel", "../images/Pause/Panel.png", 1, 1);
    textureManager_->add("Pause-Background", "../images/Pause/Fondo.png", 1, 1);

    // Portraits
    textureManager_->add("Portraits-Archer", "../images/Portraits/Archer.png", 1, 1);
    textureManager_->add("Portraits-ArcherEnemy", "../images/Portraits/ArcherEnemy.png", 1, 1);
    // TODO(Javi): Nuke this
    textureManager_->add("Portraits-characterPlaceholder", "../images/Portraits/characterPlaceholder.png", 1, 1);
    textureManager_->add("Portraits-Knight", "../images/Portraits/Knight.png", 1, 1);
    textureManager_->add("Portraits-KnightEnemy", "../images/Portraits/KnightEnemy.png", 1, 1);
    textureManager_->add("Portraits-Mage", "../images/Portraits/Mage.png", 1, 1);
    textureManager_->add("Portraits-MageEnemy", "../images/Portraits/MageEnemy.png", 1, 1);
    textureManager_->add("Portraits-Narrator", "../images/Portraits/Narrator.png", 1, 1);
    textureManager_->add("Portraits-SoldierEnemy", "../images/Portraits/SoldierEnemy.png", 1, 1);
    textureManager_->add("Portraits-Thassa", "../images/Portraits/Thassa.png", 3, 3)
        ->addAnimation("default", {0})
        ->addAnimation("angry", {1})
        ->addAnimation("pray", {2})
        ->addAnimation("courage", {3})
        ->addAnimation("shout", {4})
        ->addAnimation("surprise", {5})
        ->addAnimation("sad", {6});

    // Maps
    textureManager_->add("Maps-Test", "../images/Maps/TestMap.png", 1, 1);
    textureManager_->add("Maps-FirstBattle", "../images/Maps/FirstBattle.png", 1, 1);
    textureManager_->add("Maps-SecondBattle", "../images/Maps/SecondBattle.png", 1, 1);

      // Fonts
      fontManager_->add("Retron2000", "../fonts/Retron2000.ttf", 12, WIN_WIDTH);
      fontManager_->init();

    // Create the window and renderer
    window_ = SDL_CreateWindow("Drakhtar", SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           WIN_WIDTH,
                                           WIN_HEIGHT,
                                           SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    textureManager_->init(renderer_);

    // If window or renderer is a null pointer, throw a SDLError
    if (window_ == nullptr || renderer_ == nullptr)
        throw new SDLError("Error loading the SDL window or renderer");

    stateMachine = new GameStateMachine();
    state_ = new MainMenu(this, renderer_);
    stateMachine->pushState(state_);
}

void Game::run()
{
    while (!stateMachine->getCurrentState()->getexit())
    {
        // Preload the state before running
        currentState_ = stateMachine->getCurrentState();
        stateMachine->getCurrentState()->_preload();

        // The event loop follows this scheme:
        // → Create all pending-to-create game objects
        // → Handle SDL events (provided by SDL's event poll)
        // → Handle updates (updates all game objects of the game)
        // → Handle after updates (called after all the updates have run)
        // → Render all the game objects from the scene
        // → Run all the pending events of this tick from the stack
        // → Destroy all the elements that are pending to destroy
        // Once all tasks are done, exit loop, perform cleanup, and finish

        uint lastTick = SDL_GetTicks();
        uint elapsedTicks = 0;
        uint requiredTicks = 1000 / ANIMATION_TICKS_PER_SECOND;
        while (stateMachine->getCurrentState() == currentState_ && !stateMachine->getCurrentState()->getexit())
        {
            stateMachine->getCurrentState()->_create();
            stateMachine->getCurrentState()->_handleEvents(event);
            stateMachine->getCurrentState()->_update();

            elapsedTicks = SDL_GetTicks() - lastTick;
            if (elapsedTicks >= requiredTicks)
            {
                lastTick += elapsedTicks;
                TextureManager::getInstance()->tick();
            }
            stateMachine->getCurrentState()->_afterUpdate();
            stateMachine->getCurrentState()->_render();
            stateMachine->getCurrentState()->_events();
            stateMachine->getCurrentState()->_destroy();
        }
        stateMachine->getCurrentState()->_end();
    }
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    delete stateMachine;
    FontManager::destroy();

    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
}

SDL_Renderer *Game::getRenderer()
{
    return renderer_;
}

Game *Game::instance = nullptr;

Game *Game::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Game();
    }

    return instance;
}

GameStateMachine *Game::getStateMachine()
{
    return stateMachine;
}

GameState *Game::currentState()
{
    return getInstance()->currentState_;
}

