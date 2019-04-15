// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameScene.h"
#include <fstream>
#include "Errors/DrakhtarError.h"
#include "EventListeners/PlayerController.h"
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
  team1_ = new Team(board_, Color::BLUE);
  team2_ = new Team(board_, Color::RED);

  // Create a temporary factory to create the units easily.
  auto factory = UnitFactory(this);

  // Blue Team
  const auto thassa = factory.newThassa(team1_, board_->getBoxAt(0, 0));
  team1_->setCommander(thassa);
  addGameObject(thassa);

  std::map<std::string, int>* army = GameManager::getInstance()->getArmy();

  if ((*army)["Soldier"] > 0)
    addGameObject(
        factory.newSoldier(team1_, board_->getBoxAt(0, 2), (*army)["Soldier"]));

  if ((*army)["Archer"] > 0)
    addGameObject(
        factory.newArcher(team1_, board_->getBoxAt(0, 3), (*army)["Archer"]));

  if ((*army)["Mage"] > 0)
    addGameObject(
        factory.newWizard(team1_, board_->getBoxAt(0, 4), (*army)["Mage"]));

  if ((*army)["Knight"] > 0)
    addGameObject(
        factory.newKnight(team1_, board_->getBoxAt(0, 5), (*army)["Knight"]));

  if ((*army)["Monster"] > 0)
    addGameObject(
        factory.newMonster(team1_, board_->getBoxAt(0, 6), (*army)["Monster"]));

  // Red Team
  this->loadRedTeam(factory);

  // Add the GUI features now
  const auto turnBar =
      new TurnBar(this, team1_->getUnitList(), team2_->getUnitList());

  const auto dialog =
      new DialogScene(this, "dialog" + std::to_string(battle_), "DialogFont");

  boardController_ = new BoardController(board_, turnBar, this);
  board_->addEventListener(boardController_);

  const auto skipTurnButton =
      new Button(this, TextureManager::get("Button-SkipTurn"),
                 Vector2D<int>(WIN_WIDTH / 6, WIN_HEIGHT / 18),
                 Vector2D<int>(static_cast<int>(WIN_WIDTH / 21.6),
                               static_cast<int>(WIN_HEIGHT / 14.4)),
                 [this]() { boardController_->advanceTurn(); });

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
                      board_, thassa, 0);

  addGameObject(turnBar);
  addGameObject(dialog);
  addGameObject(skipTurnButton);
  addGameObject(pauseButton);
  addGameObject(battleCryButton);

  board->addEventListener(new PlayerController(board, turnBar, this));

  if (battle_ == 1) {
    const auto tutorialSequence =
        new TutorialSequence(this, "tutorials", "TutorialFont");
    addGameObject(tutorialSequence);
  }
}

void GameScene::pause() {
  if (!isPaused()) {
    addGameObject(new Pause(this));
    audio->playChannel(7, 0, 0);
    Scene::pause();
  }
}

void GameScene::loadRedTeam(UnitFactory& factory) {
  std::ifstream file;
  file.open("../levels/level-" + std::to_string(battle_) + ".txt");

  if (!file.is_open()) throw DrakhtarError("Could not find file");

  std::string captainName;

  // File structure:
  // CaptainName row col
  // row col (for Soldier)
  // row col (for Archer)
  // row col (for Mage)
  // row col (for Knight)
  // row col (for Monster)

  file >> captainName;
  if (file.fail()) throw DrakhtarError("File is not a level file");

  int row, col, size;

  file >> row >> col;
  Commander* commander;
  if (captainName == "Zamdran") {
    commander = factory.newZamdran(team2_, board_->getBoxAt(row, col));

    const auto arrowRainButton =
        new SkillButton(this, TextureManager::get("Button-BattleCry"),
                        Vector2D<int>(WIN_WIDTH / 10, WIN_HEIGHT / 18),
                        Vector2D<int>(static_cast<int>(WIN_WIDTH / 21.6),
                                      static_cast<int>(WIN_HEIGHT / 14.4)),
                        board_, commander, 0);
    addGameObject(arrowRainButton);
  } else {
    throw DrakhtarError(
        "File is not a level file or the captain is not implemented");
  }

  team2_->setCommander(commander);
  this->addGameObject(commander);
  if (!file.eof()) {
    file >> size >> row >> col;
    addGameObject(factory.newSoldier(team2_, board_->getBoxAt(row, col), size));
  }

  if (!file.eof()) {
    file >> size >> row >> col;
    addGameObject(factory.newArcher(team2_, board_->getBoxAt(row, col), size));
  }

  if (!file.eof()) {
    file >> size >> row >> col;
    addGameObject(factory.newWizard(team2_, board_->getBoxAt(row, col), size));
  }

  if (!file.eof()) {
    file >> size >> row >> col;
    addGameObject(factory.newKnight(team2_, board_->getBoxAt(row, col), size));
  }

  if (!file.eof()) {
    file >> size >> row >> col;
    addGameObject(factory.newMonster(team2_, board_->getBoxAt(row, col), size));
  }

  file.close();
}
