#include "Game.h"
#include "SDLError.h"
#include "SDL.h"

Game::Game()
	: window_(nullptr), renderer_(nullptr)
{
	// Create the window and renderer
	window_ = SDL_CreateWindow("Drakhtar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

	// If window or renderer is a null pointer, throw a SDLError
	if (window_ == nullptr || renderer_ == nullptr)
		throw new SDLError("Error loading the SDL window or renderer");

	textures_ = new Texture*[NUMBER_TEXTURES];
	// Create the textures
	for (uint i = 0; i < NUMBER_TEXTURES; i++)
		textures_[i] = new Texture(renderer_, TEXTURES[i].path, TEXTURES[i].rows, TEXTURES[i].columns);

	state_ = new State(this, renderer_);
}

void Game::run()
{
	state_->run();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();

	for (int i = 0; i < NUMBER_TEXTURES; i++) delete textures_[i];
	delete[] textures_;
	delete state_;
}

Texture** Game::getTextures() {
	return textures_;
}
