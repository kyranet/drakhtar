#include "GameScene.h"
#include "Button.h"
#include "DialogScene.h"
#include "Team.h"
#include "TextureManager.h"
#include "TurnBar.h"
#include "UnitFactory.h"

GameScene::~GameScene() {
  delete team1;
  delete team2;
  delete pauseObject;
}

void GameScene::preload() {
  // Add the background and the board.
  auto background = new GameObject(TextureManager::get("Maps-FirstBattle"),
                                   Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                                   Vector2D<int>(WIN_WIDTH, WIN_HEIGHT));
  auto board = new Board(TextureManager::get("UI-cellFrame"), 8, 12, 50.0f);
  addGameObject(background);
  addGameObject(board);

  // Create the teams.
  team1 = new Team(board, Color::BLUE);
  team2 = new Team(board, Color::RED);

  // Create a temporary factory to create the units easily.
  UnitFactory factory;
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
  auto turnBar = new TurnBar(team1->getUnitList(), team2->getUnitList());
  auto dialog = new DialogScene("dialog1_start", "Retron2000");
  auto pauseButton =
      new Button(TextureManager::get("Button-Pause"), 770, 30, 50, 50, []() {
        if (!isPaused()) pause();
      });

  addGameObject(turnBar);
  addGameObject(dialog);
  addGameObject(pauseButton);
}

void GameScene::pause() {
  Scene::pause();
  // TODO(Antonio Román): Add GameObject::enable()
  // pauseObject->enable();
}

void GameScene::resume() {
  Scene::resume();
  // TODO(Antonio Román): Add GameObject::disable()
  // pauseObject->disable();
}
