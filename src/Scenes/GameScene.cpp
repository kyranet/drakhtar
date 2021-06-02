// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "GameScene.h"

#include <algorithm>
#include <fstream>

#include "Controllers/AIController.h"
#include "Controllers/PlayerController.h"
#include "Errors/DrakhtarError.h"
#include "GameObjects/Battalion.h"
#include "GameObjects/Board.h"
#include "GameObjects/Box.h"
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
#include "Managers/State.h"
#include "Managers/TextureManager.h"
#include "Structures/Game.h"
#include "Structures/Team.h"
#include "Structures/UnitFactory.h"
#include "Tracker.h"
#include "TrackerEvents/LevelEndEvent.h"
#include "TrackerEvents/LevelStartEvent.h"
#include "TrackerEvents/PauseEndEvent.h"
#include "TrackerEvents/PauseStartEvent.h"
#include "Utils/Constants.h"

auto audio = SDLAudioManager::getInstance();

GameScene::GameScene(int battle) : battle_(battle) {}

GameScene::~GameScene() {
  delete team1_;
  delete team2_;
  delete state_;
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

  std::vector<Unit*> unitsInOrder;

  // Create a temporary factory to create the units easily.
  auto factory = UnitFactory(this);

  // Red Team
  this->readLevel(factory, unitsInOrder);
  state_ = new State();
  state_->setBoard(board_->getRows(), board_->getCols());

  // Blue Team
  const auto thassa =
      factory.newCommander("Thassa", team1_, board_->getBoxAt(0, 0));
  team1_->addCommander(thassa);
  thassa->setCommanderHealthBar();
  unitsInOrder.push_back(thassa);

  if (battle_ == 1) {
    const auto valar =
        factory.newCommander("BlueValar", team1_, board_->getBoxAt(0, 4));
    team1_->addCommander(valar);
    valar->setCommanderHealthBar();
    unitsInOrder.push_back(valar);
  }

  auto army = GameManager::getInstance()->getArmy();
  auto typeOrder = GameManager::getInstance()->getTypeOrder();

  uint16_t y = 1;
  for (const auto& pair : typeOrder) {
    if (army[pair.second] > 0) {
      unitsInOrder.push_back(factory.newBattalion(
          pair.second, team1_, board_->getBoxAt(0, y), army[pair.second]));
      y++;
    }
  }

  std::sort(unitsInOrder.begin(), unitsInOrder.end(),
            [](const Unit* a, const Unit* b) { return (*a) < (*b); });

  for (unsigned int i = 0; i < unitsInOrder.size(); i++)
    addGameObject(unitsInOrder[i]);
  firstUnit_ = unitsInOrder.front();
  lastUnit_ = unitsInOrder.back();

  // Sort both teams by their speeds
  team1_->sortUnits();
  team2_->sortUnits();

  // Add the GUI features now
  const auto turnBar =
      new TurnBar(this, team1_->getUnits(), team2_->getUnits());

  turnBar->setTransparent(true);

  /*const auto dialog =
      new DialogScene(this, "dialog" + std::to_string(battle_), "DialogFont");*/

  const auto dialog = new DialogScene(this, "LINE_" + std::to_string(battle_),
                                      nLines[battle_ - 1], "DialogFont");

  team1_->setController(new PlayerController(board_, this, team1_, team2_));
  team2_->setController(new PlayerController(board_, this, team2_, team1_));

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

  const auto unitDescriptionBox = new UnitDescriptionBox(this, board_);

  addGameObject(turnBar);
  addGameObject(dialog);
  addGameObject(pauseButton);
  addGameObject(battleCryButton);
  addGameObject(heroicStrikeButton);
  addGameObject(enemySkillButton);
  addGameObject(unitDescriptionBox);

  if (battle_ == 1) {
    std::string x = "tutorials/tutorials.txt";
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
  Tracker::getInstance().trackEvent(
      new LevelStartEvent(getBattleInd(), getPlayerArmy()));
}

void GameScene::pause() {
  if (!isPaused()) {
    Tracker::getInstance().trackEvent(new PauseStartEvent(getBattleInd()));
    Scene::pause();
    pauseInterface = new Pause(this);
    addGameObject(pauseInterface);
    audio->playChannel(7, 0, 0);
  }
}

void GameScene::readLevel(UnitFactory& factory, std::vector<Unit*>& unitOrder) {
  std::ifstream file;
  file.open("levels/level-" + std::to_string(battle_) + ".txt");

  if (!file.is_open()) throw DrakhtarError("Could not find file");

  std::string commanderName;

  // File structure:
  // CommanderName row col
  // UnitType battalionSize row col
  // ...
  // UnitType battalionSize row col

  if (file.fail()) throw DrakhtarError("File is not a level file");

  uint16_t rowSize, columnSize;

  file >> rowSize >> columnSize;

  int trackNumber;

  file >> trackNumber;

  delete board_;
  board_ = nullptr;

  board_ = new Board(this, rowSize, columnSize, static_cast<float>(90));
  addGameObject(board_);

  file >> commanderName;

  uint16_t row, col, size;

  file >> row >> col;
  Commander* commander =
      factory.newCommander(commanderName, team2_, board_->getBoxAt(row, col));
  if (commander == nullptr)
    throw DrakhtarError(
        "File is not a level file or the captain is not implemented");

  team2_->addCommander(commander);
  commander->setCommanderHealthBar();
  unitOrder.push_back(commander);
  while (!file.eof()) {
    std::string unitType;
    file >> unitType >> size >> row >> col;
    unitOrder.push_back(factory.newBattalion(unitType, team2_,
                                             board_->getBoxAt(row, col), size));
  }

  audio->haltMusic();
  if (audio->getDefault()) audio->setMusicVolume(10);
  audio->playMusic(trackNumber, 999);

  file.close();
}

void GameScene::updateRenderOrder(Unit* unit) {
  auto it = gameObjects_.begin();
  while ((*it) != unit && it != gameObjects_.end()) it++;

  if (firstUnit_ == lastUnit_) {
    return;
  }
  bool sorted = false;
  bool sortToLeft = false;

  if ((*it) == lastUnit_) {
    sortToLeft = true;
  } else {
    auto next = it;
    next++;
    if ((*reinterpret_cast<Unit*>(*it)) < (*reinterpret_cast<Unit*>(*next)))
      sortToLeft = true;
  }

  while (!sorted) {
    auto next = it;
    if (sortToLeft) {
      if ((*it) == firstUnit_) return;
      next--;
      if ((*reinterpret_cast<Unit*>(*next)) < (*reinterpret_cast<Unit*>(*it))) {
        sorted = true;
      } else {
        if ((*it) == lastUnit_) {
          lastUnit_ = reinterpret_cast<Unit*>(*next);
        } else if ((*next) == firstUnit_) {
          firstUnit_ = reinterpret_cast<Unit*>(*it);
          sorted = true;
        }
        std::swap((*it), (*next));
        it--;
      }
    } else {
      if ((*it) == lastUnit_) return;
      next++;
      if ((*reinterpret_cast<Unit*>(*it)) < (*reinterpret_cast<Unit*>(*next))) {
        sorted = true;
      } else {
        if ((*it) == firstUnit_) {
          firstUnit_ = reinterpret_cast<Unit*>(*next);
        } else if ((*next) == lastUnit_) {
          lastUnit_ = reinterpret_cast<Unit*>(*it);
          sorted = true;
        }
        std::swap((*it), (*next));
        it++;
      }
    }
  }
}

void GameScene::gameOver(bool victory) {
  Scene::pause();
  const auto gameOverPanel_ =
      new GameOverPanel(this, TextureManager::get("UI-OptionsMenu"),
                        {WIN_WIDTH / 2, WIN_HEIGHT / 2},
                        {WIN_WIDTH / 2, WIN_HEIGHT / 2}, victory);
  if (victory) {
    saveStatus();
    Tracker::getInstance().trackEvent(new LevelEndEvent(
        getBattleInd(), LevelResult::VICTORY, getPlayerArmy()));
  } else {
    Tracker::getInstance().trackEvent(new LevelEndEvent(
        getBattleInd(), LevelResult::DEFEAT, getPlayerArmy()));
  }
  addGameObject(gameOverPanel_);
}

void GameScene::addPrize(int prize) { prize_ += prize; }

void GameScene::saveStatus() {
  auto army = GameManager::getInstance()->getArmy();
  auto units = team1_->getUnits();
  GameManager::getInstance()->updateUnits(units);
  GameManager::getInstance()->addMoney(prize_);
}

std::map<std::string, uint16_t>* GameScene::getPlayerArmy() {
  auto* army = new std::map<std::string, uint16_t>();
  for (Unit* unit : team1_->getUnits()) {
    if (unit->isCommander())
      army->insert(std::pair<std::string, uint16_t>(unit->getType(), 1));
    else
      army->insert(std::pair<std::string, uint16_t>(
          unit->getType(),
          reinterpret_cast<Battalion*>(unit)->getBattalionSize()));
  }
  return army;
}

Board* GameScene::getBoard() const { return board_; }

int GameScene::getBattleInd() { return battle_; }

void GameScene::activateTutorialBox() { addGameObject(tutorialBox); }

State* GameScene::getState() const { return state_; }

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
