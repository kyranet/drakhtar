#include "DialogScene.h"

DialogScene::DialogScene(Game* game, string filename, string fontfile): GameObject(nullptr, Vector2D<int>(0,0), Vector2D<int>(1,1)) // default position and size(adjust it to move DialogScene)
{
	dialogBlockSprite = new GameObject(TextureManager::get("UI-dialogueBackground"), Vector2D<int>(getRect().x + WIN_WIDTH - 400, getRect().y + WIN_HEIGHT - 100), Vector2D<int>(getRect().w*600, getRect().h*160));
	textFont = new Font("../fonts/" + fontfile + ".ttf", 12, dialogBlockSprite->getRect().x + 150);
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

void DialogScene::render() const
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
			dialogChain[i] = new Dialog(game, file, textFont, getRect());
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
	// close dialog and go to next event(for now it just now restarts the whole dialog)
	currentDialogIndex = 0;
	destroy();
}

