// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "Game.h"
#include "../Errors/SDLError.h"
#include "../Managers/FontManager.h"
#include "../Managers/SDLAudioManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/TransitionScene.h"
#include "../Utils/Constants.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

Game::Game() {
  if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
    const auto message =
        std::string("Error initializing SDL.\nReason: ") + SDL_GetError();
    throw SDLError(message);
  }

  if (TTF_Init() != 0) {
    const auto message =
        std::string("Error initializing TTF.\nReason: ") + TTF_GetError();
    throw SDLError(message);
  }

  if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
    const auto message =
        std::string("Error initializing MIX.\nReason: ") + Mix_GetError();
    throw SDLError(message);
  }

  auto textures = TextureManager::getInstance();

  // Units
  textures
      ->add("Units-BlueArcher", "../images/Units/BlueArcher.png", 4, 3,
            SDL_FLIP_HORIZONTAL)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10});
  textures->add("Units-BlueKnight", "../images/Units/BlueKnight.png", 2, 1,
                SDL_FLIP_HORIZONTAL);
  textures->add("Units-BlueMage", "../images/Units/BlueMage.png", 4, 2)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6});
  textures->add("Units-BlueMonster", "../images/Units/BlueMonster.png", 3, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8});
  textures
      ->add("Units-BlueSoldier", "../images/Units/BlueSoldier.png", 5, 2,
            SDL_FLIP_HORIZONTAL)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9});
  textures->add("Units-BlueValar", "../images/Units/BlueValar.png", 2, 1,
                SDL_FLIP_HORIZONTAL);
  textures
      ->add("Units-Thassa", "../images/Units/Thassa.png", 3, 3,
            SDL_FLIP_HORIZONTAL)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8});
  textures->add("Units-Abeizhul", "../images/Units/Abeizhul.png", 5, 2)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9});
  textures->add("Units-Dreilay", "../images/Units/Dreilay.png", 2, 1);
  textures->add("Units-RedArcher", "../images/Units/RedArcher.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10});
  textures->add("Units-RedKnight", "../images/Units/RedKnight.png", 2, 1);
  textures->add("Units-RedMage", "../images/Units/RedMage.png", 3, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8});
  textures->add("Units-RedMonster", "../images/Units/RedMonster.png", 2, 1);
  textures->add("Units-RedSoldier", "../images/Units/RedSoldier.png", 5, 2)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9});
  textures->add("Units-Sheissa", "../images/Units/Sheissa.png", 3, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8});
  textures->add("Units-Valar", "../images/Units/RedValar.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10});
  textures->add("Units-Zamdran", "../images/Units/Zamdran.png", 2, 1);

  // UI
  textures->add("UI-cellFrame", "../images/UI/cellFrame.png", 1, 1);
  textures->add("UI-cellHover", "../images/UI/cellHover.png", 1, 1);
  textures->add("UI-cellInRange", "../images/UI/cellInRange.png", 1, 1);
  textures->add("UI-enemyInRange", "../images/UI/enemyInRange.png", 1, 1);
  textures->add("UI-activeUnit", "../images/UI/activeUnitCell.png", 1, 1);
  textures->add("UI-dialogueBackground", "../images/UI/dialogueBackground.png",
                1, 1);
  textures->add("UI-dialogueArrow", "../images/UI/arrow_Dialog.png", 7, 1);
  textures->add("UI-dialoguePortrait", "../images/UI/portrait.png", 1, 1);

  textures->add("UI-turnBar", "../images/UI/rock_bar.png", 1, 1);
  textures->add("UI-circle", "../images/UI/circle.png", 1, 1);

  // Button
  textures->add("Button-Play", "../images/MainMenu/Play_Button.png", 1, 1);
  textures->add("Button-Options", "../images/MainMenu/Options_Button.png", 1,
                1);
  textures->add("Button-BattleCry", "../images/UI/battlecry_icon.png", 1, 1);
  textures->add("Button-Pause", "../images/Pause/Pause_Button.png", 1, 1);
  textures->add("Button-Resume", "../images/Pause/Resume_Button.png", 1, 1);
  textures->add("Button-Restart", "../images/Pause/Restart_Button.png", 1, 1);
  textures->add("Button-Exit", "../images/Pause/Exit_Button.png", 1, 1);
  textures->add("Button-Skip", "../images/UI/skipButton.png", 1, 1);

  // Pause
  textures->add("Pause-Panel", "../images/Pause/Panel.png", 1, 1);
  textures->add("Pause-Background", "../images/Pause/Fondo.png", 1, 1);

  // Portraits
  textures->add("Portraits-Archer", "../images/Portraits/Archer.png", 1, 1);
  textures->add("Portraits-ArcherEnemy", "../images/Portraits/ArcherEnemy.png",
                1, 1);
  // TODO(Javi): Nuke this
  textures->add("Portraits-Valar", "../images/Portraits/Valar.png", 1, 1);
  textures->add("Portraits-EvilValar", "../images/Portraits/EvilValar.png", 1,
                1);

  textures->add("Portraits-Knight", "../images/Portraits/Knight.png", 1, 1);
  textures->add("Portraits-KnightEnemy", "../images/Portraits/KnightEnemy.png",
                1, 1);
  textures->add("Portraits-Mage", "../images/Portraits/Mage.png", 1, 1);
  textures->add("Portraits-MageEnemy", "../images/Portraits/MageEnemy.png", 1,
                1);
  textures->add("Portraits-Narrator", "../images/Portraits/Narrator.png", 1, 1);
  textures->add("Portraits-SoldierEnemy",
                "../images/Portraits/SoldierEnemy.png", 1, 1);
  textures->add("Portraits-Thassa", "../images/Portraits/Thassa.png", 3, 3)
      ->addAnimation("default", {0})
      ->addAnimation("angry", {1})
      ->addAnimation("pray", {2})
      ->addAnimation("courage", {3})
      ->addAnimation("shout", {4})
      ->addAnimation("surprise", {5})
      ->addAnimation("sad", {6});

  // Maps
  textures->add("Maps-Test", "../images/Maps/TestMap.png", 1, 1);
  textures->add("Maps-FirstBattle", "../images/Maps/FirstBattle.png", 1, 1);
  textures->add("Maps-SecondBattle", "../images/Maps/SecondBattle.png", 1, 1);

  // Transition
  textures->add("Transition-Map1", "../images/Maps/TestMap.png", 1, 1);
  textures->add("Transition-Map2", "../images/Transition/Transition_2.png", 1,
                1);

  // Recruitment
  textures->add("Recruitment-Background",
                "../images/Recruitment/recruitment.png", 1, 1);
  textures->add("Recruitment-Panel",
                "../images/Recruitment/recruitment_Panel.png", 1, 1);
  textures->add("Quantity-Button", "../images/Recruitment/quantity_Button.png",
                1, 1);
  textures->add("Accept-Button", "../images/Recruitment/accept_Button.png", 1,
                1);
  textures->add("Cancel-Button", "../images/Recruitment/cancel_Button.png", 1,
                1);

  auto fonts = FontManager::getInstance();

  // Create the window and renderer
  window_ = SDL_CreateWindow("Drakhtar", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT,
                             SDL_WINDOW_SHOWN);
  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  textures->init(renderer_);

  // Fonts
  fonts->add("DialogFont", "../fonts/Retron2000.ttf", WIN_WIDTH / 66,
             WIN_WIDTH);
  fonts->add("Retron2000", "../fonts/Retron2000.ttf", WIN_WIDTH / 88,
             WIN_WIDTH);
  fonts->init();

  auto audio = SDLAudioManager::getInstance();
  audio->init();

  // background music
  audio->loadMusic(
      0, "../audio/background/MenuSceneMusic - by AShamaluevMusic.ogg");
  audio->loadMusic(
      1, "../audio/background/FirstGameSceneMusic - by Always Music.ogg");

  // sound effects

  /*
                channel 0 = UI sounds
                channel 1 = unit sounds

  */
  audio->loadSound(0, "../audio/sound/UI-sounds/basic_click.mp3");
  audio->loadSound(1, "../audio/sound/UI-sounds/button_click.mp3");
  audio->loadSound(2, "../audio/sound/UI-sounds/hitPlayMenu.mp3");
  audio->loadSound(3, "../audio/sound/UI-sounds/accionBloqueada.mp3");
  audio->loadSound(4, "../audio/sound/UI-sounds/attackCommand.mp3");
  audio->loadSound(5, "../audio/sound/UI-sounds/attackConfirm.mp3");
  audio->loadSound(6, "../audio/sound/UI-sounds/quitButton.mp3");
  audio->loadSound(7, "../audio/sound/UI-sounds/pauseButton.mp3");

  // If window or renderer is a null pointer, throw a SDLError
  if (window_ == nullptr || renderer_ == nullptr)
    throw SDLError("Error loading the SDL window or renderer");

  sceneMachine_ = new SceneMachine();
  sceneMachine_->pushScene(new MenuScene());
}

Game::~Game() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);

  delete sceneMachine_;

  SDL_Quit();
  TTF_Quit();
  Mix_Quit();
}

void Game::run() const {
  while (!sceneMachine_->isEmpty()) {
    sceneMachine_->getCurrentScene()->run();
  }
}

SDL_Renderer *Game::getRenderer() { return getInstance()->renderer_; }

Game *Game::instance_ = nullptr;

Game *Game::getInstance() {
  if (instance_ == nullptr) {
    instance_ = new Game();
  }

  return instance_;
}

SceneMachine *Game::getSceneMachine() { return getInstance()->sceneMachine_; }
