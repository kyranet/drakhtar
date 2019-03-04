#pragma once

#include "State.h"
#include "BoardController.h"

State::State(Game* game, SDL_Renderer* renderer)
	: GameState(game,renderer), game_(game)
{
}

State::~State()
{
	game_ = nullptr;
	delete team1;
	delete team2;
	delete factory;
	delete turnBar_;
}

void State::_preload()
{
	// TextureManager
	gameObjects_.push_back(new GameObject(TextureManager::get("Maps-FirstBattle"), Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D<int>(WIN_WIDTH, WIN_HEIGHT)));
	
	// Board
	board_ = new Board(TextureManager::get("UI-cellFrame"), 8, 12, 50);
	gameObjects_.push_back(new GameObject(TextureManager::get("Maps-FirstBattle"), Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D<int>(WIN_WIDTH, WIN_HEIGHT)));
    gameObjects_.push_back(board_);
	
	// Test Teams
	team1 = new Team(board_);
	team2 = new Team(board_);
	
	// Test Factory
	factory = new UnitFactory();
	gameObjects_.push_back(factory->newSoldier(team1, board_->getBoxAt(0, 2), 10));
	gameObjects_.push_back(factory->newArcher(team1, board_->getBoxAt(0, 3), 10));
	gameObjects_.push_back(factory->newWizard(team1, board_->getBoxAt(0, 4), 10));
	gameObjects_.push_back(factory->newKnight(team1, board_->getBoxAt(0, 5), 10));
	gameObjects_.push_back(factory->newMonster(team1, board_->getBoxAt(0, 6), 10));


	gameObjects_.push_back(factory->newSoldier(team2, board_->getBoxAt(11, 0), 10));
	gameObjects_.push_back(factory->newArcher(team2, board_->getBoxAt(11, 1), 10));
	gameObjects_.push_back(factory->newWizard(team2, board_->getBoxAt(11, 2), 10));
	gameObjects_.push_back(factory->newKnight(team2, board_->getBoxAt(10, 0), 10));
	gameObjects_.push_back(factory->newMonster(team2, board_->getBoxAt(10, 1), 10));

	// Dialog
	auto exampleDialog = new DialogScene(game_, "dialog1_start", "Retron2000");
	gameObjects_.push_back(exampleDialog);


	//sounds
	audioManager.init();
	audioManager.loadMusic(0, "../audio/background/Smash Mouth - All Star _Official Music Video_.mp3");
	audioManager.loadSound(1, "../audio/sound/Glass_Running.mp3");
	//audioManager.playMusic(0, 1);
	audioManager.setMusicVolume(2);
  
	// Turn Bar
	turnBar_ = new TurnBar(team1->getUnitList(), team2->getUnitList());
	gameObjects_.push_back(turnBar_);


	// Controller
	addEventListener(new BoardController(board_, turnBar_));
}

void State::_handleEvents(SDL_Event& e)
{
	while (!_exit && SDL_PollEvent(&e))
	{
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
			case SDLK_e:
				cout << "Pause";
				break;
			}
		}

		// For each game object, run the event handler
		for (auto gameObject : gameObjects_)
			gameObject->handleEvents(e);

		GameState::_handleEvents(e);
	}
}

void State::playASound(int tag, int loop, int channel)
{
	audioManager.playChannelTimed(tag, loop, channel,3000);
	audioManager.FadeOutChannel(1, 3000);
}


	while (!_exit && SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_e:
				playASound(1, 2, 2);
				break;
			case SDLK_ESCAPE:
				game_->getStateMachine()->pushState(new MainMenu(game_, renderer_));
				break;
			}
		}

		// For each game object, run the event handler
		for (auto gameObject : gameObjects_)
			gameObject->handleEvents(e);

		GameState::_handleEvents(e);
	delete team1;
	delete team2;
	delete factory;
	delete turnBar_;