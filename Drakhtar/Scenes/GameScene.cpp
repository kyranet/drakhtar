// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameScene.h"
#include "../EventListeners/BoardController.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/DialogScene.h"
#include "../GameObjects/Pause.h"
#include "../GameObjects/TurnBar.h"
#include "../Managers/SDLAudioManager.h"
#include "../Managers/TextureManager.h"
#include "../Structures/Game.h"
#include "../Structures/Team.h"
#include "../Structures/UnitFactory.h"
#include "../Utils/Constants.h"

GameScene::~GameScene() {
  delete team1_;
  delete team2_;
}

void buttonPause() { Game::getSceneMachine()->getCurrentScene()->pause(); }

void GameScene::preload() {
  // Add the background and the board.
  const auto background =
      new GameObject(this, TextureManager::get("Maps-FirstBattle"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  auto board = new Board(this, 8, 12, static_cast<float>(WIN_HEIGHT / 10));
  addGameObject(background);
  addGameObject(board);

  // Create the teams.
  team1_ = new Team(board, Color::BLUE);
  team2_ = new Team(board, Color::RED);

  // Create a temporary factory to create the units easily.
  UnitFactory factory = UnitFactory(this);
  addGameObject(factory.newSoldier(team1_, board->getBoxAt(0, 2), 10));
  addGameObject(factory.newArcher(team1_, board->getBoxAt(0, 3), 10));
  addGameObject(factory.newWizard(team1_, board->getBoxAt(0, 4), 10));
  addGameObject(factory.newKnight(team1_, board->getBoxAt(0, 5), 10));
  addGameObject(factory.newMonster(team1_, board->getBoxAt(0, 6), 10));

  addGameObject(factory.newSoldier(team2_, board->getBoxAt(11, 2), 10));
  addGameObject(factory.newArcher(team2_, board->getBoxAt(11, 3), 10));
  addGameObject(factory.newWizard(team2_, board->getBoxAt(11, 4), 10));
  addGameObject(factory.newKnight(team2_, board->getBoxAt(11, 5), 10));
  addGameObject(factory.newMonster(team2_, board->getBoxAt(11, 6), 10));

  // Add the GUI features now
  auto turnBar =
      new TurnBar(this, team1_->getUnitList(), team2_->getUnitList());
  auto dialog = new DialogScene(this, "dialog1_start", "DialogFont");
  auto pauseButton = new Button(
      this, TextureManager::get("Button-Pause"),
      Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 24, WIN_HEIGHT / 18),
      Vector2D<int>(WIN_WIDTH / 21.6, WIN_HEIGHT / 14.4), buttonPause);

  addGameObject(turnBar);
  addGameObject(dialog);
  addGameObject(pauseButton);

  board->addEventListener(new BoardController(board, turnBar, this));

  auto audio = SDLAudioManager::getInstance();
  audio->haltMusic();
  audio->setChannelVolume(100, 0);
  audio->playMusic(1, -1);
  audio->setMusicVolume(30);
}

void GameScene::pause() {
  if (!isPaused()) addGameObject(new Pause(this));
  Scene::pause();
}
