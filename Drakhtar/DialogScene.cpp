#include "DialogScene.h"



DialogScene::DialogScene(Game* game, string filename)
{
	//dialogBlockSprite = new GameObject(game->getTextures()[AÑADIR TEXTURA AL ENUM], vector2d{ 400, 400 }, vector2d{ 200, 80 });
	readFromFile(game, filename);
}


DialogScene::~DialogScene()
{
	delete dialogBlockSprite;
	dialogBlockSprite = nullptr;
}

void DialogScene::render()
{
	dialogBlockSprite->render();
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

void DialogScene::readFromFile(Game* game, string filename)
{
	ifstream file;
	file.open(filename + ".txt");
	if (!file.is_open()) throw "No se encuentra el fichero";
	else
	{
		file >> dialogChainSize;
		dialogChain.reserve(dialogChainSize);

		for (int i = 0;i < dialogChainSize;i++)
		{
			dialogChain[i] = new Dialog(game, file);
		}
		
	}
	file.close();
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
	// close dialog and go to next event
}

