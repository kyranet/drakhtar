// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameScene.h"

#include <fstream>

#include "Controllers/PlayerController.h"
#include "Errors/DrakhtarError.h"
#include "GameObjects/Battalion.h"
#include "GameObjects/Button.h"
#include "GameObjects/Commanders/Thassa.h"
#include "GameObjects/Commanders/Zamdran.h"
#include "GameObjects/DialogScene.h"
#include "GameObjects/Pause.h"
#include "GameObjects/SkillButton.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/TutorialSequence.h"
#include "Managers/GameManager.h"
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
  const auto background = new GameObject(
      this, TextureManager::get("Maps-" + std::to_string(battle_) + "Battle"),
      Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
      Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  board_ = new Board(this, 8, 12, static_cast<float>(WIN_HEIGHT / 10.0f));
  addGameObject(background);
  addGameObject(board_);

  // Create the teams.
  team1_ = new Team(Color::BLUE);
  team2_ = new Team(Color::RED);

  // Create a temporary factory to create the units easily.
  auto factory = UnitFactory(this);

  // Blue Team
  const auto thassa =
      factory.newCommander("Thassa", team1_, board_->getBoxAt(0, 0));
  team1_->addCommander(thassa);
  addGameObject(thassa);

  auto army = GameManager::getInstance()->getArmy();
  auto typeOrder = GameManager::getInstance()->getTypeOrder();

  int y = 2;
  for (const auto& pair : typeOrder) {
    if (army[pair.second] > 0) {
      addGameObject(factory.newBattalion(
          pair.second, team1_, board_->getBoxAt(0, y), army[pair.second]));
      y++;
    }
  }

  // Red Team
  this->loadRedTeam(factory);

  // Sort both teams by their speeds
  team1_->sortUnits();
  team2_->sortUnits();

  // Add the GUI features now
  const auto turnBar =
      new TurnBar(this, team1_->getUnits(), team2_->getUnits());

  turnBar->setTransparent(true);

  const auto dialog =
      new DialogScene(this, "dialog" + std::to_string(battle_), "DialogFont");

  team1_->setController(new PlayerController(board_, turnBar->getTurnManager(),
                                             this, team1_, team2_));
  team2_->setController(new PlayerController(board_, turnBar->getTurnManager(),
                                             this, team2_, team1_));

  const auto pauseButton =
      new Button(this, TextureManager::get("Button-Pause"),
                 Vector2D<int>(WIN_WIDTH - WIN_WIDTH / 24, WIN_HEIGHT / 18),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 21.6),
                               static_cast<int>(WIN_HEIGHT / 14.4)),
                 buttonPause, " ", "ButtonFont");

  audio->haltMusic();
  if (audio->getDefault()) audio->setMusicVolume(10);
  audio->playMusic(1, 999);
  /*
   // Reactivar cuando se implementen las habilidades definitivamente
  const auto battleCryButton =
      new SkillButton(this, TextureManager::get("Button-BattleCry"),
                      Vector2D<int>(WIN_WIDTH / 24, WIN_HEIGHT / 18),
                      Vector2D<int>(static_cast<int>(WIN_WIDTH / 21.6),
                                    static_cast<int>(WIN_HEIGHT / 14.4)),
                      board_, thassa, 0);
  */
  addGameObject(turnBar);
  addGameObject(dialog);
  addGameObject(pauseButton);
  // addGameObject(battleCryButton);

  if (battle_ == 1) {
    const auto tutorialSequence =
        new TutorialSequence(this, "tutorials", "TutorialFont");
    addGameObject(tutorialSequence);
  }

  setGame(true);

  team1_->getController()->start();
}

void GameScene::pause() {
  if (!isPaused()) {
    Scene::pause();
    pauseInterface = new Pause(this);
    addGameObject(pauseInterface);
    audio->playChannel(7, 0, 0);
  }
}

void GameScene::loadRedTeam(UnitFactory& factory) {
  std::ifstream file;
  file.open("../levels/level-" + std::to_string(battle_) + ".txt");

  if (!file.is_open()) throw DrakhtarError("Could not find file");

  std::string commanderName;

  // File structure:
  // CommanderName row col
  // UnitType battalionSize row col
  // ...
  // UnitType battalionSize row col

  file >> commanderName;
  if (file.fail()) throw DrakhtarError("File is not a level file");

  int row, col, size;

  file >> row >> col;
  Commander* commander =
      factory.newCommander(commanderName, team2_, board_->getBoxAt(row, col));
  if (commander == nullptr)
    throw DrakhtarError(
        "File is not a level file or the captain is not implemented");

  team2_->addCommander(commander);
  addGameObject(commander);
  while (!file.eof()) {
    std::string unitType;
    file >> unitType >> size >> row >> col;
    addGameObject(factory.newBattalion(unitType, team2_,
                                       board_->getBoxAt(row, col), size));
  }

  file.close();
}

void GameScene::addPrize(int prize) { prize_ += prize; }

void GameScene::saveStatus() {
  auto army = GameManager::getInstance()->getArmy();
  auto units = team1_->getUnits();
  for (auto unit : units) {
    if (army.find(unit->getType()) != army.end()) {
      army[unit->getType()] =
          reinterpret_cast<Battalion*>(unit)->getBattalionSize();
    }
  }
  GameManager::getInstance()->addMoney(prize_);
}

Board* GameScene::getBoard() const { return board_; }

int GameScene::getBattleInd() { return battle_; }
