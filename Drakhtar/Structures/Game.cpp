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

  // Create the window and renderer
  window_ = SDL_CreateWindow("Drakhtar", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT,
                             SDL_WINDOW_SHOWN);
  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  // If window or renderer is a null pointer, throw a SDLError
  if (window_ == nullptr || renderer_ == nullptr)
    throw SDLError("Error loading the SDL window or renderer");
}

void Game::load() {
  if (loaded_) throw DrakhtarError("Cannot run Game::load twice.");
  loaded_ = true;
  auto textures = TextureManager::getInstance();

  // Units
  textures->add("Units-BlueArcher", "../images/Units/BlueArcher.png", 5, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->setFlip(SDL_FLIP_HORIZONTAL);
  textures->add("Units-BlueKnight", "../images/Units/BlueKnight.png", 5, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12})
      ->setFlip(SDL_FLIP_HORIZONTAL)
      ->setScale({1.5, 1.5});
  textures->add("Units-BlueMage", "../images/Units/BlueMage.png", 3, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8});
  textures->add("Units-BlueMonster", "../images/Units/BlueMonster.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10});
  textures->add("Units-BlueSoldier", "../images/Units/BlueSoldier.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11})
      ->setFlip(SDL_FLIP_HORIZONTAL);
  textures->add("Units-Thassa", "../images/Units/Thassa.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->setFlip(SDL_FLIP_HORIZONTAL);
  textures->add("Units-Abeizhul", "../images/Units/Abeizhul.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
  textures->add("Units-Dreilay", "../images/Units/Dreilay.png", 5, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
  textures->add("Units-RedArcher", "../images/Units/RedArcher.png", 5, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
  textures->add("Units-RedKnight", "../images/Units/RedKnight.png", 5, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12})
      ->setScale({1.5, 1.5});
  textures->add("Units-RedMage", "../images/Units/RedMage.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->setFlip(SDL_FLIP_HORIZONTAL);
  textures->add("Units-RedMonster", "../images/Units/RedMonster.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->setFlip(SDL_FLIP_HORIZONTAL);
  textures->add("Units-RedSoldier", "../images/Units/RedSoldier.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
  textures->add("Units-Sheissa", "../images/Units/Sheissa.png", 4, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10});
  textures->add("Units-BlueValar", "../images/Units/BlueValar.png", 5, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
  textures->add("Units-RedValar", "../images/Units/RedValar.png", 5, 3)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
  textures->add("Units-Zamdran", "../images/Units/Zamdran.png", 4, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14});

  // UI
  textures->add("UI-cellFrame", "../images/UI/cellFrame.png", 1, 1);
  textures->add("UI-cellHover", "../images/UI/cellHover.png", 1, 1);
  textures->add("UI-cellInRange", "../images/UI/cellInRange.png", 1, 1);
  textures->add("UI-enemyInRange", "../images/UI/enemyInRange.png", 1, 1);
  textures->add("UI-activeUnit", "../images/UI/activeUnitCell.png", 1, 1);
  textures->add("UI-dialogueBackground", "../images/UI/dialogueBackground.png",
                1, 1);
  textures->add("UI-tutorialBackground", "../images/UI/tutorialBackground.png",
                1, 1);
  textures->add("UI-dialogueArrow", "../images/UI/arrow_Dialog.png", 7, 1);
  textures->add("UI-dialoguePortrait", "../images/UI/portrait.png", 1, 1);

  textures->add("UI-turnBar", "../images/UI/rock_bar.png", 1, 1);
  textures->add("UI-circle", "../images/UI/circle.png", 9, 1);
  textures->add("UI-healthBar_background",
                "../images/UI/healthBar_background.png", 1, 1);
  textures->add("UI-healthBar_life", "../images/UI/healthBar_life.png", 1, 1);
  textures->add("UI-healthBar_damage", "../images/UI/healthBar_damage.png", 1,
                1);
  textures->add("UI-commanderIcon", "../images/UI/goldskull.png", 1, 1);
  textures->add("UI-OptionsMenu", "../images/UI/OptionsMenu.png", 1, 1);
  textures->add("UI-ActiveSound", "../images/UI/ActiveSound.png", 1, 1);
  textures->add("UI-MuteSound", "../images/UI/MuteSound.png", 1, 1);
  textures->add("UI-WhiteBox", "../images/UI/WhiteBox.png", 1, 1);
  textures->add("UI-greenTick", "../images/UI/green-check.png", 1, 1);

  // Button
  textures->add("Button-BattleCry", "../images/UI/battlecry_icon.png", 1, 1);
  textures->add("Button-BattleCry-disabled", "../images/UI/battlecry_icon_disabled.png", 1, 1);
  textures->add("Button-Pause", "../images/Pause/Pause_Button.png", 1, 1);
  textures->add("Button-Skip", "../images/UI/skipButton.png", 1, 1);
  textures->add("Button-SkipTurn", "../images/UI/skipTurnButton.png", 1, 1);
  textures->add("Vanilla-Button", "../images/Pause/Button.png", 1, 1);

  // Pause
  textures->add("Pause-Panel", "../images/Pause/Panel.png", 1, 1);
  textures->add("Pause-Background", "../images/Pause/Fondo.png", 1, 1);

  // Portraits
  textures->add("Portraits-Archer", "../images/Portraits/Archer.png", 1, 1);
  textures->add("Portraits-ArcherEnemy", "../images/Portraits/ArcherEnemy.png",
                1, 1);
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
  textures->add("Maps-1Battle", "../images/Maps/FirstBattle.png", 4, 1)
      ->addAnimation("default", {0, 1, 2, 3}, 1);
  textures->add("Maps-2Battle", "../images/Maps/SecondBattle.png", 4, 1);

  // Tutorial images
  textures->add("tutorial-1", "../images/Tutorials/tutorial_1.png", 1, 1);
  textures->add("tutorial-2", "../images/Tutorials/tutorial_2.png", 1, 1);
  textures->add("tutorial-3", "../images/Tutorials/tutorial_3.png", 1, 1);
  textures->add("tutorial-4", "../images/Tutorials/tutorial_4.png", 1, 1);
  textures->add("tutorial-5", "../images/Tutorials/tutorial_5.png", 1, 1);
  textures->add("tutorial-6", "../images/Tutorials/tutorial_6.png", 1, 1);
  textures->add("tutorial-7", "../images/Tutorials/tutorial_7.png", 1, 1);

  // Transition
  textures->add("Transition-Map1", "../images/Maps/TestMap.png", 1, 1);
  textures->add("Transition-Map2", "../images/Transition/Transition_2.png", 1,
                1);
  textures->add("Transition-Menu", "../images/Transition/Transition_1.png", 4,
                1);

  // Recruitment
  textures->add("Recruitment-Background",
                "../images/Recruitment/recruitment.png", 1, 1);
  textures->add("Recruitment-Panel",
                "../images/Recruitment/recruitment_Panel.png", 1, 1);
  textures->add("Reward-Panel", "../images/Recruitment/reward_Panel.png", 1, 1);
  textures->add("Quantity-Button", "../images/Recruitment/quantity_Button.png",
                1, 1);
  textures->add("Accept-Button", "../images/Recruitment/accept_Button.png", 1,
                1);
  textures->add("Cancel-Button", "../images/Recruitment/cancel_Button.png", 1,
                1);

  auto fonts = FontManager::getInstance();
  textures->init();

  // Fonts
  fonts->add("DialogFont", "../fonts/Retron2000.ttf", WIN_WIDTH / 66,
             WIN_WIDTH);
  fonts->add("SkillButtonFont", "../fonts/Retron2000.ttf", WIN_WIDTH / 40,
             WIN_WIDTH);
  fonts->add("Retron2000", "../fonts/Retron2000.ttf", WIN_WIDTH / 88,
             WIN_WIDTH);
  fonts->add("TutorialFont", "../fonts/Retron2000.ttf", WIN_WIDTH / 100,
             WIN_WIDTH);
  fonts->add("UnitFont", "../fonts/Retron2000.ttf", WIN_WIDTH / 120, WIN_WIDTH);
  fonts->add("StatsFont", "../fonts/Retron2000.ttf", WIN_WIDTH / 37, WIN_WIDTH);
  fonts->add("ButtonFont", "../fonts/AURORA.ttf", WIN_WIDTH / 50, WIN_WIDTH);
  fonts->init();

  auto audio = SDLAudioManager::getInstance();
  audio->init();
  // Background music
  audio->loadMusic(
      0, "../audio/background/MenuSceneMusic - by AShamaluevMusic.ogg");
  audio->loadMusic(
      1, "../audio/background/FirstGameSceneMusic - by Always Music.ogg");

  // Sound effects
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

SDL_Renderer* Game::getRenderer() { return getInstance()->renderer_; }

Game* Game::instance_ = nullptr;

Game* Game::getInstance() {
  if (instance_ == nullptr) {
    instance_ = new Game();
  }

  return instance_;
}

SceneMachine* Game::getSceneMachine() { return getInstance()->sceneMachine_; }

SDL_Window* Game::getWindow() { return getInstance()->window_; }
