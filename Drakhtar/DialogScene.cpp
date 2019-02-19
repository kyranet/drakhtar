#include "DialogScene.h"

DialogScene::DialogScene(Game* game, string filename, string fontfile)
{
	dialogBlockSprite = new GameObject(game->getTextures()[DIALOG_BLOCK], Vector2D<int>(400, 500), Vector2D<int>(600, 160));
	textFont = new Font("../fonts/" + fontfile + ".ttf", 8);
	readFromFile(game, "../dialog/" + filename + ".txt",+ textFont);
}

DialogScene::~DialogScene()
{
	for (auto dialog : dialogChain)
		delete dialog;
	delete dialogBlockSprite;
	dialogBlockSprite = nullptr;
	delete textFont;
	textFont = nullptr;
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

void DialogScene::readFromFile(Game* game, string filename, Font* textFont)
{
	ifstream file;
	file.open(filename);
	/*if (!file.is_open()) throw "No se encuentra el fichero";
	else
	{*/
		file >> dialogChainSize;
		dialogChain.resize(dialogChainSize);

		for (int i = 0;i < dialogChainSize;i++)
		{
			dialogChain[i] = new Dialog(game, file, textFont);
		}
		
	//}
	file.close();
}

void DialogScene::nextDialog()
{
	if (currentDialogIndex < dialogChainSize - 1)
		currentDialogIndex++;
	else
		endOfDialog();
}

void DialogScene::endOfDialog()
{
	currentDialogIndex = 0;
	// close dialog and go to next event
}

