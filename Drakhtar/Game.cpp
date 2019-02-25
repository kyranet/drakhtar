#include "Game.h"
#include "SDLError.h"

Game::Game()
	: window_(nullptr), renderer_(nullptr)
{
	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
	{
		string message = string("Error initializing SDL.\nReason: ") + SDL_GetError();
		throw new SDLError(message);
	}
	
	if (TTF_Init() != 0)
	{
		string message = string("Error initializing TTF.\nReason: ") + TTF_GetError();
		throw new SDLError(message);
	}

	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0)
	{
		string message = string("Error initializing MIX.\nReason: ") + Mix_GetError();
		throw new SDLError(message);
	}

	// Units
	textureManager_->add("Units-Abeizhul", "../images/Units/Abeizhul.png", 2, 1);
	textureManager_->add("Units-BlueArcher", "../images/Units/BlueArcher.png", 2, 1);
	textureManager_->add("Units-BlueKnight", "../images/Units/BlueKnight.png", 2, 1);
	textureManager_->add("Units-BlueMage", "../images/Units/BlueMage.png", 2, 1);
	textureManager_->add("Units-BlueMonster", "../images/Units/BlueMonster.png", 2, 1);
	textureManager_->add("Units-BlueSoldier", "../images/Units/BlueSoldier.png", 2, 1);
	textureManager_->add("Units-BlueValar", "../images/Units/BlueValar.png", 2, 1);
	textureManager_->add("Units-Dreilay", "../images/Units/Dreilay.png", 2, 1);
	textureManager_->add("Units-RedArcher", "../images/Units/RedArcher.png", 2, 1);
	textureManager_->add("Units-RedKnight", "../images/Units/RedKnight.png", 2, 1);
	textureManager_->add("Units-RedMonster", "../images/Units/RedMonster.png", 2, 1);
	textureManager_->add("Units-RedSoldier", "../images/Units/RedSoldier.png", 2, 1);
	textureManager_->add("Units-Sheissa", "../images/Units/Sheissa.png", 2, 1);
	textureManager_->add("Units-Thassa", "../images/Units/Thassa.png", 2, 1);
	textureManager_->add("Units-Valar", "../images/Units/Valar.png", 2, 1);
	textureManager_->add("Units-Zamdran", "../images/Units/Zamdran.png", 2, 1);

	// UI
	textureManager_->add("UI-cellFrame", "../images/UI/cellFrame.png", 1, 1);
	textureManager_->add("UI-dialogueBackground", "../images/UI/dialogueBackground.png", 1, 1);

	// Portraits
	textureManager_->add("Portraits-Archer", "../images/Portraits/Archer.png", 1, 1);
	textureManager_->add("Portraits-ArcherEnemy", "../images/Portraits/ArcherEnemy.png", 1, 1);
	// TODO: Nuke this
	textureManager_->add("Portraits-characterPlaceholder", "../images/Portraits/characterPlaceholder.png", 1, 1);
	textureManager_->add("Portraits-Knight", "../images/Portraits/Knight.png", 1, 1);
	textureManager_->add("Portraits-KnightEnemy", "../images/Portraits/KnightEnemy.png", 1, 1);
	textureManager_->add("Portraits-Mage", "../images/Portraits/Mage.png", 1, 1);
	textureManager_->add("Portraits-MageEnemy", "../images/Portraits/MageEnemy.png", 1, 1);
	textureManager_->add("Portraits-Narrator", "../images/Portraits/Narrator.png", 1, 1);
	textureManager_->add("Portraits-SoldierEnemy", "../images/Portraits/SoldierEnemy.png", 1, 1);
	textureManager_->add("Portraits-Thassa", "../images/Portraits/Thassa.png", 3, 3)
		->addAnimation("default", { 0 })
		->addAnimation("angry", { 1 })
		->addAnimation("pray", { 2 })
		->addAnimation("courage", { 3 })
		->addAnimation("shout", { 4 })
		->addAnimation("surprise", { 5 })
		->addAnimation("sad", { 6 });

	// Maps
	textureManager_->add("Maps-FirstBattle", "../images/Maps/FirstBattle.png", 1, 1);
	textureManager_->add("Maps-SecondBattle", "../images/Maps/SecondBattle.png", 1, 1);


	// Create the window and renderer
	window_ = SDL_CreateWindow("Drakhtar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	textureManager_->init(renderer_);

	// If window or renderer is a null pointer, throw a SDLError
	if (window_ == nullptr || renderer_ == nullptr)
		throw new SDLError("Error loading the SDL window or renderer");

	stateMachine = new GameStateMachine();
	stateMachine->pushState(new State(this,renderer_));
}

void Game::run()
{
	stateMachine->getCurrentState()->run();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	delete state_;
	delete stateMachine;

	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
}

SDL_Renderer* Game::getRenderer()
{
	return renderer_;
}

Game* Game::instance = nullptr;

Game* Game::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Game();
	}

	return instance;
}

/*State* Game::currentState()
{
	return getInstance()->state_;
}*/
