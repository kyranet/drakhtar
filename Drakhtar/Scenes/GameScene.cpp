// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameScene.h"
#include "EventListeners/BoardController.h"
#include "GameObjects/Button.h"
#include "GameObjects/Commanders/Thassa.h"
#include "GameObjects/Commanders/Zamdran.h"
#include "GameObjects/DialogScene.h"
#include "GameObjects/Pause.h"
#include "GameObjects/SkillButton.h"
#include "GameObjects/TurnBar.h"
#include "Managers/SDLAudioManager.h"
#include "Managers/TextureManager.h"
#include "Structures/Game.h"
#include "Structures/Team.h"
#include "Structures/UnitFactory.h"
#include "Utils/Constants.h"

auto audio = SDLAudioManager::getInstance();

GameScene::GameScene(int battle) : battle_(battle) {}

GameScene::~GameScene() {
  delete team1_;
  delete team2_;
}

void buttonPause() { Game::getSceneMachine()->getCurrentScene()->pause(); }

void GameScene::preload() {
  Scene::preload();
  // Add the background and the board.
  const auto background =
      new GameObject(this, TextureManager::get("Maps-" + std::to_string(battle_) + "Battle"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  auto board = new Board(this, 8, 12, static_cast<float>(WIN_HEIGHT / 10.0f));
  addGameObject(background);
  addGameObject(board);

  // Create the teams.
  team1_ = new Team(board, Color::BLUE);
  team2_ = new Team(board, Color::RED);

  // Create a temporary factory to create the units easily.
  auto factory = UnitFactory(this);

  // Blue Team
  const auto thassa = factory.newThassa(team1_, board->getBoxAt(0, 0));
  team1_->setCommander(thassa);
  addGameObject(thassa);
  addGameObject(factory.newSoldier(team1_, board->getBoxAt(0, 2), 10));
  addGameObject(factory.newArcher(team1_, board->getBoxAt(0, 3), 10));
  addGameObject(factory.newWizard(team1_, board->getBoxAt(0, 4), 10));
  addGameObject(factory.newKnight(team1_, board->getBoxAt(0, 5), 10));
  addGameObject(factory.newMonster(team1_, board->getBoxAt(0, 6), 10));

  // Red Team
  const auto zamdran_ = factory.newZamdran(team2_, board->getBoxAt(11, 0));
  team2_->setCommander(zamdran_);
  addGameObject(zamdran_);
  addGameObject(factory.newSoldier(team2_, board->getBoxAt(11, 2), 10));
  addGameObject(factory.newArcher(team2_, board->getBoxAt(11, 3), 10));
  addGameObject(factory.newWizard(team2_, board->getBoxAt(11, 4), 10));
  addGameObject(factory.newKnight(team2_, board->getBoxAt(11, 5), 10));
  addGameObject(factory.newMonster(team2_, board->getBoxAt(11, 6), 10));

  // Add the GUI features now
  const auto turnBar =
      new TurnBar(this, team1_->getUnitList(), team2_->getUnitList());

  const auto dialog = new DialogScene(this, "dialog" + std::to_string(battle_), "DialogFont");
  const auto pauseButton =
      new Button(this, TextureManager::get("Button-Pause"),
                 Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 24, WIN_HEIGHT / 18),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 21.6),
                               static_cast<int>(WIN_HEIGHT / 14.4)),
                 buttonPause);

  audio->haltMusic();
  audio->setMusicVolume(10);
  audio->playMusic(1, 999);

  const auto battleCryButton =
      new SkillButton(this, TextureManager::get("Button-BattleCry"),
                      Vector2D<int>(WIN_WIDTH / 24, WIN_HEIGHT / 18),
                      Vector2D<int>(static_cast<int>(WIN_WIDTH / 21.6),
                                    static_cast<int>(WIN_HEIGHT / 14.4)),
                      board, thassa, 0);

  const auto arrowRainButton =
      new SkillButton(this, TextureManager::get("Button-BattleCry"),
                      Vector2D<int>(WIN_WIDTH / 10, WIN_HEIGHT / 18),
                      Vector2D<int>(static_cast<int>(WIN_WIDTH / 21.6),
                                    static_cast<int>(WIN_HEIGHT / 14.4)),
                      board, zamdran_, 0);

  addGameObject(turnBar);
  addGameObject(dialog);
  addGameObject(pauseButton);
  addGameObject(battleCryButton);
  addGameObject(arrowRainButton);

  board->addEventListener(new BoardController(board, turnBar, this));
}

void GameScene::pause() {
  if (!isPaused()) {
    addGameObject(new Pause(this));
    audio->playChannel(7, 0, 0);
    Scene::pause();
  }
}
