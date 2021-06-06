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
#include "Tracker.h"
#include "TrackerEvents/SessionEndEvent.h"
#include "TrackerEvents/SessionStartEvent.h"

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

  locale_.init("es");
  locale_.load();

  // Units
  textures->add("Units-BlueArcher", "images/Units/BlueArcher.png", 5, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->addAnimation("walk", {11, 12}, 4)
      ->addAnimation("death", {13, 14, 15, 16, 17})
      ->setOffset({-0.05, 0});
  textures->add("Units-BlueKnight", "images/Units/BlueKnight.png", 5, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->addAnimation("walk", {11, 12, 13, 14}, 4)
      ->addAnimation("death", {15, 16, 17, 18, 19})
      ->setScale({1.5, 1.5})
      ->setOffset({-0.035, 0});
  textures->add("Units-BlueMage", "images/Units/BlueMage.png", 4, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6})
      ->addAnimation("walk", {7, 8}, 4)
      ->addAnimation("death", {9, 10, 11, 12})
      ->setOffset({-0.05, 0});
  textures->add("Units-BlueMonster", "images/Units/BlueMonster.png", 4, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8})
      ->addAnimation("walk", {9, 10}, 4)
      ->addAnimation("death", {11, 12, 13, 14, 15})
      ->setOffset({-0.05, -0.05});
  textures->add("Units-BlueSoldier", "images/Units/BlueSoldier.png", 4, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8})
      ->addAnimation("walk", {9, 10}, 4)
      ->addAnimation("death", {11, 12, 13, 14, 15});
  textures->add("Units-Thassa", "images/Units/Thassa.png", 7, 6)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8})
      ->addAnimation("walk", {9, 10, 11, 12, 13}, 5)
      ->addAnimation("death", {14, 15, 16, 17, 18})
      ->addAnimation("ability1", {19, 20, 21, 22, 23, 24, 25, 26, 27})
      ->addAnimation("ability2", {28, 29, 30, 31, 32, 33, 34, 35, 36, 37});
  textures->add("Units-Abeizhul", "images/Units/Abeizhul.png", 7, 6)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9})
      ->addAnimation("walk", {10, 11}, 4)
      ->addAnimation("death", {12, 13, 14, 15, 16})
      ->addAnimation("ability1", {17, 18, 19, 20, 21, 22, 23, 24, 25})
      ->addAnimation("ability2", {26, 27, 28, 29, 30, 31})
      ->addAnimation("ability3", {32, 33, 34, 35, 36, 37})
      ->setFlip(SDL_FLIP_HORIZONTAL);
  textures->add("Units-Dreilay", "images/Units/Dreilay.png", 6, 5)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->addAnimation("walk", {11, 12, 13, 14}, 4)
      ->addAnimation("death", {15, 16, 17, 18, 19})
      ->addAnimation("ability1", {20, 21, 22, 23, 24, 25, 26, 27, 28, 29})
      ->setFlip(SDL_FLIP_HORIZONTAL)
      ->setScale({1.5, 1.5});
  textures->add("Units-RedArcher", "images/Units/RedArcher.png", 5, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->addAnimation("walk", {11, 12}, 4)
      ->addAnimation("death", {13, 14, 15, 16, 17})
      ->setFlip(SDL_FLIP_HORIZONTAL)
      ->setOffset({0.05, 0});
  textures->add("Units-RedKnight", "images/Units/RedKnight.png", 5, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->addAnimation("walk", {11, 12, 13, 14}, 4)
      ->addAnimation("death", {15, 16, 17, 18, 19})
      ->setFlip(SDL_FLIP_HORIZONTAL)
      ->setScale({1.5, 1.5})
      ->setOffset({0.035, 0});
  textures->add("Units-RedMage", "images/Units/RedMage.png", 4, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8})
      ->addAnimation("walk", {9, 10}, 4)
      ->addAnimation("death", {11, 12, 13, 14, 15})
      ->setFlip(SDL_FLIP_HORIZONTAL)
      ->setOffset({0.05, 0});
  textures->add("Units-RedMonster", "images/Units/RedMonster.png", 4, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8})
      ->addAnimation("walk", {9, 10}, 4)
      ->addAnimation("death", {11, 12, 13, 14, 15})
      ->setFlip(SDL_FLIP_HORIZONTAL)
      ->setOffset({0.05, -0.05});
  textures->add("Units-RedSoldier", "images/Units/RedSoldier.png", 4, 4)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8})
      ->addAnimation("walk", {9, 10}, 4)
      ->addAnimation("death", {11, 12, 13, 14, 15})
      ->setFlip(SDL_FLIP_HORIZONTAL);
  textures->add("Units-Sheissah", "images/Units/Sheissah.png", 5, 5)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8})
      ->addAnimation("walk", {9, 10}, 4)
      ->addAnimation("death", {11, 12, 13, 14, 15})
      ->addAnimation("ability1", {16, 17, 18, 19, 20})
      ->setFlip(SDL_FLIP_HORIZONTAL);
  textures->add("Units-BlueValar", "images/Units/BlueValar.png", 5, 5)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->addAnimation("walk", {11, 12, 13, 14, 15, 16}, 4)
      ->addAnimation("death", {17, 18, 19, 20, 21});
  textures->add("Units-RedValar", "images/Units/RedValar.png", 6, 5)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10})
      ->addAnimation("walk", {11, 12, 13, 14, 15, 16}, 4)
      ->addAnimation("death", {17, 18, 19, 20, 21})
      ->addAnimation("ability1", {22, 23, 24, 25, 26, 27})
      ->setFlip(SDL_FLIP_HORIZONTAL);
  textures->add("Units-Zamdran", "images/Units/Zamdran.png", 6, 5)
      ->addAnimation("default", {0, 1})
      ->addAnimation("attack", {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12})
      ->addAnimation("walk", {13, 14}, 4)
      ->addAnimation("death", {15, 16, 17, 18, 19})
      ->addAnimation("ability1", {20, 21, 22, 23, 24, 25, 26, 27})
      ->setFlip(SDL_FLIP_HORIZONTAL);

  // Obstacles
  textures
      ->add("Obstacle-BottomTruck", "images/Obstacles/BottomTruck.png", 1, 1)
      ->addAnimation("default", {0});
  textures->add("Obstacle-Box", "images/Obstacles/Box.png", 1, 1)
      ->addAnimation("default", {0});
  textures->add("Obstacle-Fence", "images/Obstacles/Fence.png", 1, 1)
      ->addAnimation("default", {0});
  textures->add("Obstacle-Rock", "images/Obstacles/Rock.png", 1, 1)
      ->addAnimation("default", {0});
  textures->add("Obstacle-TopTruck", "images/Obstacles/TopTruck.png", 1, 1)
      ->addAnimation("default", {0});
  textures->add("Obstacle-Torch", "images/Obstacles/Torch.png", 1, 1)
      ->addAnimation("default", {0});
  textures->add("Obstacle-Trees", "images/Obstacles/Trees.png", 1, 1)
      ->addAnimation("default", {0});

  // UI
  textures->add("UI-cellFrame", "images/UI/cellFrame.png", 1, 1);
  textures->add("UI-cellHover", "images/UI/cellHover.png", 1, 1);
  textures->add("UI-cellHoverBlue", "images/UI/cellHoverBlue.png", 1, 1);
  textures->add("UI-cellHoverRed", "images/UI/cellHoverRed.png", 1, 1);
  textures->add("UI-cellInRange", "images/UI/cellInRange.png", 1, 1);
  textures->add("UI-enemyInRange", "images/UI/enemyInRange.png", 1, 1);
  textures->add("UI-activeUnit", "images/UI/activeUnitCell.png", 1, 1);
  textures->add("UI-dialogueBackground", "images/UI/dialogueBackground.png", 1,
                1);
  textures->add("UI-tutorialBackground", "images/UI/tutorialBackground.png", 1,
                1);
  textures->add("UI-dialogueArrow", "images/UI/arrow_Dialog.png", 7, 1);
  textures->add("UI-dialoguePortrait", "images/UI/portrait.png", 1, 1);

  textures->add("UI-turnBar", "images/UI/rock_bar.png", 1, 1);
  textures->add("UI-circle", "images/UI/circle.png", 9, 1);
  textures->add("UI-healthBar_background", "images/UI/healthBar_background.png",
                1, 1);
  textures->add("UI-healthBar_life", "images/UI/healthBar_life.png", 1, 1);
  textures->add("UI-healthBar_damage", "images/UI/healthBar_damage.png", 1, 1);
  textures->add("UI-healthBar_blue", "images/UI/healthBar_blue.png", 1, 1);
  textures->add("UI-BattalionCircle", "images/UI/unitBatallionCircle.png", 1,
                1);
  textures->add("UI-BattalionCircle2", "images/UI/unitBatallionCircle2.png", 1,
                1);
  textures->add("UI-commanderIcon", "images/UI/goldskull.png", 1, 1);
  textures->add("UI-OptionsMenu", "images/UI/OptionsMenu.png", 1, 1);
  textures->add("UI-ActiveSound", "images/UI/ActiveSound.png", 1, 1);
  textures->add("UI-MuteSound", "images/UI/MuteSound.png", 1, 1);
  textures->add("UI-WhiteBox", "images/UI/WhiteBox.png", 1, 1);
  textures->add("UI-greenTick", "images/UI/green-check.png", 1, 1);
  textures->add("UI-statUp", "images/UI/statUp.png", 1, 1);
  textures->add("UI-statDown", "images/UI/statDown.png", 1, 1);
  textures->add("UI-arrowAnim", "images/UI/arrow_anim.png", 4, 5);

  // Button
  textures->add("Button-BattleCry", locale_.getAsset("battlecry_icon.png"), 1,
                1);
  textures->add("Button-BattleCry-disabled",
                locale_.getAsset("battlecry_icon_disabled.png"), 1, 1);
  textures->add("Button-HeroicStrike",
                locale_.getAsset("heroic_strike_icon.png"), 1, 1);
  textures->add("Button-HeroicStrike-disabled",
                locale_.getAsset("heroic_strike_icon_disabled.png"), 1, 1);
  textures->add("Button-Enemy-Skill", "images/UI/enemy_skill_icon.png", 1, 1);
  textures->add("Button-Enemy-Skill-disabled",
                "images/UI/enemy_skill_disabled_icon.png", 1, 1);
  textures->add("Button-Pause", "images/Pause/Pause_Button.png", 1, 1);
  textures->add("Button-Skip", locale_.getAsset("skipButton.png"), 1, 1);
  textures->add("Button-SkipTurn", locale_.getAsset("skipTurnButton.png"), 1,
                1);
  textures->add("Vanilla-Button", "images/Pause/Button.png", 1, 1);

  // Pause
  textures->add("Pause-Panel", locale_.getAsset("Panel.png"), 1, 1);
  textures->add("Pause-Background", "images/Pause/Fondo.png", 1, 1);

  // Portraits
  textures->add("Portraits-Archer", "images/Portraits/Archer.png", 1, 1);
  textures->add("Portraits-ArcherEnemy", "images/Portraits/ArcherEnemy.png", 1,
                1);
  textures->add("Portraits-Valar", "images/Portraits/Valar.png", 1, 1);
  textures->add("Portraits-EvilValar", "images/Portraits/EvilValar.png", 1, 1);

  textures->add("Portraits-Knight", "images/Portraits/Knight.png", 1, 1);
  textures->add("Portraits-KnightEnemy", "images/Portraits/KnightEnemy.png", 1,
                1);
  textures->add("Portraits-Mage", "images/Portraits/Mage.png", 1, 1);
  textures->add("Portraits-MageEnemy", "images/Portraits/MageEnemy.png", 1, 1);
  textures->add("Portraits-Narrator", "images/Portraits/Narrator.png", 1, 1);
  textures->add("Portraits-SoldierEnemy", "images/Portraits/SoldierEnemy.png",
                1, 1);
  textures->add("Portraits-Thassa", "images/Portraits/Thassa.png", 3, 3)
      ->addAnimation("default", {0})
      ->addAnimation("angry", {1})
      ->addAnimation("pray", {2})
      ->addAnimation("courage", {3})
      ->addAnimation("shout", {4})
      ->addAnimation("surprise", {5})
      ->addAnimation("sad", {6});

  // Maps
  textures->add("Maps-Test", "images/Maps/TestMap.png", 1, 1);
  textures->add("Maps-1Battle", "images/Maps/FirstBattle.png", 4, 1)
      ->addAnimation("default", {0, 1, 2, 3}, 1);
  textures->add("Maps-2Battle", "images/Maps/SecondBattle.png", 4, 1)
      ->addAnimation("default", {0, 1, 2, 3}, 1);
  textures->add("Maps-3Battle", "images/Maps/ThirdBattle.png", 1, 1);
  textures->add("Maps-4Battle", "images/Maps/FourthBattle.png", 1, 1);
  textures->add("Maps-5Battle", "images/Maps/FifthBattle.png", 1, 1);

  // Logos
  textures->add("Logos-VG", "images/Logos/VG.jpg", 1, 1);
  textures->add("Logos-logo", locale_.getAsset("Logo.png"), 1, 1);

  // Tutorial images
  textures->add("tutorial_", "images/Tutorials/tutorial_.png", 1, 1);
  textures->add("tutorial-1", "images/Tutorials/tutorial_1.png", 1, 1);
  textures->add("tutorial-2", "images/Tutorials/tutorial_2.png", 1, 1);
  textures->add("tutorial-3", "images/Tutorials/tutorial_3.png", 1, 1);
  textures->add("tutorial-4", "images/Tutorials/tutorial_4.png", 1, 1);
  textures->add("tutorial-5", "images/Tutorials/tutorial_5.png", 1, 1);
  textures->add("tutorial-6", "images/Tutorials/tutorial_6.png", 1, 1);
  textures->add("tutorial-7", "images/Tutorials/tutorial_7.png", 1, 1);

  // Transition
  textures->add("Transition-Map1", "images/Maps/TestMap.png", 1, 1);
  textures->add("Transition-Map2", "images/Transition/Transition_2.png", 1, 1);
  textures->add("Transition-Map3", "images/Transition/Transition_3.png", 4, 1)
      ->addAnimation("default", {0, 1, 2, 3}, 1);
  textures->add("Transition-Map4", "images/Transition/Transition_4.png", 4, 1);
  textures->add("Transition-Map5", "images/Transition/Transition_5.png", 1, 1);
  textures->add("Transition-Menu", "images/Transition/Transition_1.png", 4, 1);
  textures->add("Transition-Map6", "images/Transition/Transition_6.png", 1, 1);

  // Recruitment
  textures->add("Recruitment-Background", "images/Recruitment/recruitment.png",
                1, 1);
  textures->add("Recruitment-Panel", "images/Recruitment/recruitment_Panel.png",
                1, 1);
  textures->add("Reward-Panel", "images/Recruitment/reward_Panel.png", 1, 1);
  textures->add("Quantity-Button", "images/Recruitment/quantity_Button.png", 1,
                1);
  textures->add("Accept-Button", "images/Recruitment/accept_Button.png", 1, 1);
  textures->add("Cancel-Button", "images/Recruitment/cancel_Button.png", 1, 1);
  textures->add("Coin-Anim", "images/Recruitment/coin_rot_anim.png", 6, 1);

  auto fonts = FontManager::getInstance();
  textures->init();

  // Fonts
  fonts->add("DialogFont", "fonts/Greenscr.ttf", WIN_WIDTH / 66, WIN_WIDTH);
  fonts->add("SkillButtonFont", "fonts/Greenscr.ttf", WIN_WIDTH / 40,
             WIN_WIDTH);
  fonts->add("Retron2000", "fonts/Greenscr.ttf", WIN_WIDTH / 88, WIN_WIDTH);
  fonts->add("TutorialFont", "fonts/Greenscr.ttf", WIN_WIDTH / 100, WIN_WIDTH);
  fonts->add("UnitFont", "fonts/Greenscr.ttf", WIN_WIDTH / 120, WIN_WIDTH);
  fonts->add("StatsFont", "fonts/Greenscr.ttf", WIN_WIDTH / 45, WIN_WIDTH);
  fonts->add("ButtonFont", "fonts/Greenscr.ttf", WIN_WIDTH / 50, WIN_WIDTH);
  fonts->add("ButtonFontQuantity", "fonts/Retron2000.ttf", WIN_WIDTH / 50,
             WIN_WIDTH);
  fonts->add("ButtonFontBig", "fonts/Greenscr.ttf", WIN_WIDTH / 20, WIN_WIDTH);
  fonts->init();

  auto audio = SDLAudioManager::getInstance();
  audio->init();
  // Background music
  audio->loadMusic(0,
                   "audio/background/MenuSceneMusic - by AShamaluevMusic.ogg");
  audio->loadMusic(
      1, "audio/background/FirstGameSceneMusic - by Always Music.ogg");
  audio->loadMusic(2,
                   "audio/background/Most Wondrous Battle Music Ever Light "
                   "And Darkness.ogg");
  audio->loadMusic(3,
                   "audio/background/Epic Dark Battle Music - Escape "
                   "[Powerful Fantasy Horror by Ebunny].ogg");
  audio->loadMusic(4,
                   "audio/background/"
                   "EpicMusicOrchestraCinematicBattleMusicDragonCastlebySymphon"
                   "y(CopyrightFreeMusic).ogg");
  audio->loadMusic(5,
                   "audio/background/[No Copyright Music] Endless Storm - "
                   "(Royalty Free Epic Battle Music).ogg");
  audio->loadMusic(6,
                   "audio/background/(Epic Pirate Battle Music) - Escaping "
                   "The Kraken -.ogg");
  audio->loadMusic(7, "audio/background/Glory by Whitesand.ogg");
  audio->loadMusic(8, "audio/background/Guardians by Evan King.ogg");
  audio->loadMusic(9, "audio/background/Dark Man by egmusic16.ogg");
  audio->loadMusic(10, "audio/background/Singularity by Evan King.ogg");

  // Sound effects
  /*
             channel 0 = UI sounds
             channel 1 = unit sounds
             channel 2 = dialogue

*/
  audio->loadSound(0, "audio/sound/UI-sounds/basic_click.mp3");
  audio->loadSound(1, "audio/sound/UI-sounds/button_click.mp3");
  audio->loadSound(2, "audio/sound/UI-sounds/hitPlayMenu.mp3");
  audio->loadSound(3, "audio/sound/UI-sounds/accionBloqueada.mp3");
  audio->loadSound(4, "audio/sound/UI-sounds/attackCommand.mp3");
  audio->loadSound(5, "audio/sound/UI-sounds/attackConfirm.mp3");
  audio->loadSound(6, "audio/sound/UI-sounds/quitButton.mp3");
  audio->loadSound(7, "audio/sound/UI-sounds/pauseButton.mp3");
  audio->loadSound(
      8, "audio/sound/Unit-sounds/Heroes/Thassa/HeroicStrikeShout.mp3");
  audio->loadSound(
      9, "audio/sound/Unit-sounds/Heroes/Thassa/hittingwithHeroicStrike.mp3");
  audio->loadSound(10,
                   "audio/sound/Unit-sounds/Heroes/Thassa/battleCrySound.mp3");
  audio->loadSound(11,
                   "audio/sound/Unit-sounds/Heroes/Zamdran/ArrowRainSkill.mp3");
  audio->loadSound(12, "audio/sound/UI-sounds/coin.wav");
  audio->loadSound(13, "audio/sound/UI-sounds/nextDialogue.wav");
  audio->loadSound(14, "audio/sound/UI-sounds/skipDialogue.wav");

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
  // Tracker::getInstance().trackEvent(new SessionStartEvent());
  Tracker::getInstance().init("TheFallOfDrakhtar");
  while (!sceneMachine_->isEmpty()) {
    sceneMachine_->getCurrentScene()->run();
  }
  Tracker::getInstance().end();
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

Locale* Game::getLocale() { return &locale_; }
