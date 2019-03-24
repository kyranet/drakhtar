#include "GameScene.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/DialogScene.h"
#include "../GameObjects/Pause.h"
#include "../GameObjects/TurnBar.h"
#include "../Managers/TextureManager.h"
#include "../Structures/Game.h"
#include "../Structures/Team.h"
#include "../Structures/UnitFactory.h"
#include "../Utils/Constants.h"

GameScene::~GameScene() {
  delete team1;
  delete team2;
}

void buttonPause() { Game::getSceneMachine()->getCurrentScene()->pause(); }

void GameScene::preload() {
  // Add the background and the board.
  auto background =
      new GameObject(this, TextureManager::get("Maps-FirstBattle"),
                     Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                     Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  auto board = new Board(this, 8, 12, 50.0f);
  addGameObject(background);
  addGameObject(board);

  // Create the teams.
  team1 = new Team(board, Color::BLUE);
  team2 = new Team(board, Color::RED);

  // Create a temporary factory to create the units easily.
  UnitFactory factory = UnitFactory(this);
  addGameObject(factory.newSoldier(team1, board->getBoxAt(0, 2), 10));
  addGameObject(factory.newArcher(team1, board->getBoxAt(0, 3), 10));
  addGameObject(factory.newWizard(team1, board->getBoxAt(0, 4), 10));
  addGameObject(factory.newKnight(team1, board->getBoxAt(0, 5), 10));
  addGameObject(factory.newMonster(team1, board->getBoxAt(0, 6), 10));

  addGameObject(factory.newSoldier(team2, board->getBoxAt(11, 2), 10));
  addGameObject(factory.newArcher(team2, board->getBoxAt(11, 3), 10));
  addGameObject(factory.newWizard(team2, board->getBoxAt(11, 4), 10));
  addGameObject(factory.newKnight(team2, board->getBoxAt(11, 5), 10));
  addGameObject(factory.newMonster(team2, board->getBoxAt(11, 6), 10));

  // Add the GUI features now
  auto turnBar = new TurnBar(this, team1->getUnitList(), team2->getUnitList());
  auto dialog = new DialogScene(this, "dialog1_start", "Retron2000");
  auto pauseButton =
      new Button(this, TextureManager::get("Button-Pause"),
                 Vector2D<int>(770, 30), Vector2D<int>(50, 50), buttonPause);

  addGameObject(turnBar);
  addGameObject(dialog);
  addGameObject(pauseButton);
}

void GameScene::pause() {
  if (!isPaused()) addGameObject(new Pause(this));
  Scene::pause();
}
