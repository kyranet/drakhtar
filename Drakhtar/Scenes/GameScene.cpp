// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameScene.h"

#include <fstream>

#include "Controllers/PlayerController.h"
#include "Errors/DrakhtarError.h"
#include "GameObjects/Battalion.h"
#include "GameObjects/Board.h"
#include "GameObjects/Button.h"
#include "GameObjects/Commanders/Thassa.h"
#include "GameObjects/Commanders/Zamdran.h"
#include "GameObjects/DialogScene.h"
#include "GameObjects/GameOverPanel.h"
#include "GameObjects/Pause.h"
#include "GameObjects/SkillButton.h"
#include "GameObjects/TurnBar.h"
#include "GameObjects/TutorialBox.h"
#include "GameObjects/UnitDescriptionBox.h"
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
  addGameObject(background);

  // Create the teams.
  team1_ = new Team(Color::BLUE);
  team2_ = new Team(Color::RED);

  // Create a temporary factory to create the units easily.
  auto factory = UnitFactory(this);

  // Red Team
  this->readLevel(factory);

  // Blue Team
  const auto thassa =
      factory.newCommander("Thassa", team1_, board_->getBoxAt(0, 0));
  team1_->addCommander(thassa);
  thassa->setCommanderHealthBar();
  addGameObject(thassa);

  if (battle_ == 1) {
    const auto valar =
        factory.newCommander("BlueValar", team1_, board_->getBoxAt(0, 4));
    team1_->addCommander(valar);
    addGameObject(valar);
  }

  auto army = GameManager::getInstance()->getArmy();
  auto typeOrder = GameManager::getInstance()->getTypeOrder();

  int y = 1;
  for (const auto& pair : typeOrder) {
    if (army[pair.second] > 0) {
      addGameObject(factory.newBattalion(
          pair.second, team1_, board_->getBoxAt(0, y), army[pair.second]));
      y++;
    }
  }

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

  const auto battleCryButton =
      new SkillButton(this, TextureManager::get("Button-BattleCry"),
                      TextureManager::get("Button-BattleCry-disabled"),
                      Vector2D<int>(WIN_WIDTH / 20, 80),
                      Vector2D<int>(static_cast<int>(WIN_WIDTH / 12),
                                    static_cast<int>(WIN_HEIGHT / 8)),
                      thassa, 0);

  const auto heroicStrikeButton =
      new SkillButton(this, TextureManager::get("Button-HeroicStrike"),
                      TextureManager::get("Button-HeroicStrike-disabled"),
                      Vector2D<int>(WIN_WIDTH / 20, 180),
                      Vector2D<int>(static_cast<int>(WIN_WIDTH / 12),
                                    static_cast<int>(WIN_HEIGHT / 8)),
                      thassa, 1);

  const auto enemySkillButton =
      new SkillButton(this, TextureManager::get("Button-Enemy-Skill"),
                      TextureManager::get("Button-Enemy-Skill-disabled"),
                      Vector2D<int>(WIN_WIDTH / 20, 280),
                      Vector2D<int>(static_cast<int>(WIN_WIDTH / 12),
                                    static_cast<int>(WIN_HEIGHT / 8)),
                      team2_->getCommanders()[0], 0);

  const auto unitDescriptionBox =
      new UnitDescriptionBox(this, board_, turnBar->getTurnManager());

  addGameObject(turnBar);
  addGameObject(dialog);
  addGameObject(pauseButton);
  addGameObject(battleCryButton);
  addGameObject(heroicStrikeButton);
  addGameObject(enemySkillButton);
  addGameObject(unitDescriptionBox);

  if (battle_ == 1) {
    std::string x = "../tutorials/tutorials.txt";
    tutorialBox = new TutorialBox(
        this, x, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 4),
        Vector2D<int>(WIN_WIDTH / 5, WIN_HEIGHT / 4),
        reinterpret_cast<PlayerController*>(team1_->getController()),
        reinterpret_cast<PlayerController*>(team2_->getController()));
  } else if (battle_ > 1) {
    reinterpret_cast<PlayerController*>(team1_->getController())
        ->setTutorialDone(true);
    reinterpret_cast<PlayerController*>(team2_->getController())
        ->setTutorialDone(true);
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

void GameScene::readLevel(UnitFactory& factory) {
  std::ifstream file;
  file.open("../levels/level-" + std::to_string(battle_) + ".txt");

  if (!file.is_open()) throw DrakhtarError("Could not find file");

  std::string commanderName;

  // File structure:
  // CommanderName row col
  // UnitType battalionSize row col
  // ...
  // UnitType battalionSize row col

  if (file.fail()) throw DrakhtarError("File is not a level file");

  int rowSize, columnSize;

  file >> rowSize >> columnSize;

  int trackNumber;

  file >> trackNumber;

  delete board_;
  board_ = nullptr;

  board_ = new Board(this, rowSize, columnSize,
                     static_cast<float>(WIN_HEIGHT / 10.0f));
  addGameObject(board_);

  file >> commanderName;

  int row, col, size;

  file >> row >> col;
  Commander* commander =
      factory.newCommander(commanderName, team2_, board_->getBoxAt(row, col));
  if (commander == nullptr)
    throw DrakhtarError(
        "File is not a level file or the captain is not implemented");

  team2_->addCommander(commander);
  commander->setCommanderHealthBar();
  addGameObject(commander);
  while (!file.eof()) {
    std::string unitType;
    file >> unitType >> size >> row >> col;
    addGameObject(factory.newBattalion(unitType, team2_,
                                       board_->getBoxAt(row, col), size));
  }

  audio->haltMusic();
  if (audio->getDefault()) audio->setMusicVolume(10);
  audio->playMusic(trackNumber, 999);

  file.close();
}

void GameScene::gameOver(bool victory) {
  Scene::pause();
  const auto gameOverPanel_ =
      new GameOverPanel(this, TextureManager::get("UI-OptionsMenu"),
                        {WIN_WIDTH / 2, WIN_HEIGHT / 2},
                        {WIN_WIDTH / 2, WIN_HEIGHT / 2}, victory);
  addGameObject(gameOverPanel_);
}

void GameScene::addPrize(int prize) { prize_ += prize; }

void GameScene::saveStatus() {
  auto army = GameManager::getInstance()->getArmy();
  auto units = team1_->getUnits();
  GameManager::getInstance()->updateUnits(units);
  GameManager::getInstance()->addMoney(prize_);
}

Board* GameScene::getBoard() const { return board_; }

int GameScene::getBattleInd() { return battle_; }

void GameScene::activateTutorialBox() { addGameObject(tutorialBox); }

Team* GameScene::getAlliedTeam(Unit* unit) {
  if (unit->getTeam() == team1_) return team1_;
  if (unit->getTeam() == team2_) return team2_;
  return nullptr;
}

Team* GameScene::getEnemyTeam(Unit* unit) {
  if (unit->getTeam() != team1_) return team1_;
  if (unit->getTeam() != team2_) return team2_;
  return nullptr;
}
