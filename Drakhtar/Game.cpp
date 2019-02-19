#include "Game.h"
#include "SDLError.h"

Game::Game()
	: window_(nullptr), renderer_(nullptr)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	if (TTF_Init() == -1)
	{
		string message = string("Error loading TTF.\nReason: ") + TTF_GetError();
		throw new SDLError(message);
	}

	// Create the window and renderer
	window_ = SDL_CreateWindow("Drakhtar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	// If window or renderer is a null pointer, throw a SDLError
	if (window_ == nullptr || renderer_ == nullptr)
		throw new SDLError("Error loading the SDL window or renderer");

	textures_ = new Texture*[NUMBER_TEXTURES];
	// Create the textures
	for (uint i = 0; i < NUMBER_TEXTURES; i++)
		textures_[i] = (new Texture(renderer_))->loadFromImage(TEXTURES[i].path, TEXTURES[i].rows, TEXTURES[i].columns);

	stateMachine = new GameStateMachine();
	state_ = new State(this, renderer_); 
	stateMachine->pushState(state_);

}

void Game::run()
{
	stateMachine->getCurrentState()->run();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();

	for (int i = 0; i < NUMBER_TEXTURES; i++) delete textures_[i];
	delete[] textures_;
	delete state_;
	delete stateMachine;
}

Texture** Game::getTextures() {
	return textures_;
}

SDL_Renderer* Game::getRenderer()
{
	return renderer_;
}
