#pragma once

#include "State.h"
#include "BoardController.h"


State::State(Game* game, SDL_Renderer* renderer)
	: GameState(game,renderer), game_(game)
{
}

State::~State()
{
	for (auto gameObject : gameObjects_)
		delete gameObject;
	game_ = nullptr;
	pauseInterface = nullptr;
	delete team1;
	delete team2;
	delete factory;

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
	team1 = new Team(board_, Color::BLUE);
	team2 = new Team(board_, Color::RED);
	
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
	auto turnBar_ = new TurnBar(team1->getUnitList(), team2->getUnitList());
	gameObjects_.push_back(turnBar_);

	// Controller
	addEventListener(new BoardController(board_, turnBar_));

	//Button
	Pause_Button= new Button(TextureManager::get("Button-Pause"), 770, 30, 50, 50, Pause_game, game_, renderer_);
	gameObjects_.push_back(Pause_Button);
}

void State::_render()
{
	if (!paused_) {
		GameState::_render();
	}
	if (paused_) {
		pauseInterface->_render();
	}
}

void State::_update()
{
	if (!paused_) {
		GameState::_update();
		pauseInterface = nullptr;
		delete pauseInterface;
	}
}

void State::_handleEvents(SDL_Event& e)
{
	while (!_exit && SDL_PollEvent(&e))
	{
		Pause_Button->handleEvents(e);
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_e:
				playSound(1, 2, 2);
				break;
			case SDLK_ESCAPE:
				//game_->getStateMachine()->pushState(new MainMenu(game_, renderer_));
				pauseInterface = new Pause(game_, renderer_);
				paused_ = !paused_;
				break;
			}
		}
		//calls handleevent of pause only when it is up only
		if (pauseInterface != nullptr) {
			pauseInterface->_handleEvents(e);
		}
		if (!paused_) {
			// For each game object, run the event handler
			for (auto gameObject : gameObjects_)
				gameObject->handleEvents(e);

			GameState::_handleEvents(e);
		}
	}
}

void State::playSound(int tag, int loop, int channel)
{
	audioManager.playChannelTimed(tag, loop, channel,3000);
	audioManager.FadeOutChannel(1, 3000);
}

void State::Pause_game(Game * game, SDL_Renderer * renderer)
{	
	cout << "Pause";
}
void State::setPause()
{
	paused_ = !paused_;
}
