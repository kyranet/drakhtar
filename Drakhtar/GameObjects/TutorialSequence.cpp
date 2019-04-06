#include "TutorialSequence.h"
#include "../Errors/DrakhtarError.h"
#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Structures/Font.h"
#include "../Utils/Constants.h"
#include "TutorialBox.h"

void TutorialSequence::readFromFile(const std::string &filename, Font *textFont)
{
	std::ifstream file;
	file.open(filename);
	if (!file.is_open()) throw new DrakhtarError("Could not find file");

	size_t lines, i;
	file >> lines;

	for (size_t i = 0; i < lines && !file.eof(); i++) {
		tutorials.push(new TutorialBox(scene_, file, textFont, lineJumpLimit));
	}

	file.close();
}

TutorialSequence::TutorialSequence(Scene * scene, const std::string & filename, const std::string & fontfile)
	: GameObject(scene, nullptr, Vector2D<int>(0, 0), Vector2D<int>(1, 1))
{
	readFromFile("../tutorials/" + filename + ".txt", FontManager::get(fontfile));
}

TutorialSequence::~TutorialSequence()
{
	while (tutorials.size() != 0)
	{
		delete tutorials.top();
		tutorials.pop();
	}
}

void TutorialSequence::createNextTutorial()
{
	currentTutorial = tutorials.top();
	tutorials.pop();
}

void TutorialSequence::render() const
{
	if (currentTutorial != nullptr)
		currentTutorial->render();
}
