#include "DialogScene.h"



DialogScene::DialogScene(int dialogSize)
{
	dialogChainSize = dialogSize;
}


DialogScene::~DialogScene()
{
}

void DialogScene::render()
{
	dialogChain[currentDialogIndex]->render();
}

void DialogScene::handleEvents(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_e:
			nextDialog();
			break;
		}
	}
}

void DialogScene::readFromFile()
{
}

void DialogScene::nextDialog()
{
	if (currentDialogIndex < dialogChainSize)
		currentDialogIndex++;
	else
		endOfDialog();
}

void DialogScene::endOfDialog()
{
}

