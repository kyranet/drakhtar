#pragma once

#include "SDL.h"
#include <list>
#include "GameObject.h"
#include "Board.h"
#include "Game.h"
#include "DialogScene.h"
#include "Unit.h"
#include "GameState.h"
#include "Button.h"

using namespace std;

class DialogScene;

class State : public GameState
{
private:
	bool _exit = false;
	Game* game_ = nullptr;
protected:
	Button *Prueba;
	//SDL_Renderer *renderer_ = nullptr;
	void _preload();
	/*virtual void _create();
	virtual void _render() const;
	virtual void _update();
	virtual void _handleEvents();
	virtual void _afterUpdate();
	virtual void _events();
	virtual void _destroy();
	virtual void _end() {};*/
	void boton() { cout << "boton"; }
public:
	State(Game* game, SDL_Renderer* renderer);
	virtual ~State();
	virtual void addGameObject(GameObject* gameObject);
	virtual void removeGameObject(GameObject* gameObject);
	static void startGame(Game* game);
};

