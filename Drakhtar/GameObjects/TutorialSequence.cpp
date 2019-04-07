#include "TutorialSequence.h"
#include "../Errors/DrakhtarError.h"
#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/GameScene.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"
#include "../GameObjects/Button.h"
#include "TutorialBox.h"
#include "Structures/Game.h"

void nextTutorial() {
	Game::getSceneMachine()->getCurrentScene()->setSkip(false);
}

void skipTutorial() {
	Game::getSceneMachine()->getCurrentScene()->setSkip(true);
}

TutorialSequence::TutorialSequence(Scene *scene, const std::string &filename,
	const std::string &fontfile)
	: GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2), Vector2D<int>(1, 1)) {

	const auto tutorialArea_ = getRect();

	auto dialogueBackground = new GameObject(
		scene_, TextureManager::get("UI-tutorialBackground"),
		Vector2D<int>(tutorialArea_.x,
			tutorialArea_.y - WIN_HEIGHT / 10),
		Vector2D<int>(tutorialArea_.w * WIN_WIDTH / 3,
			tutorialArea_.h * WIN_HEIGHT / 2));

	const auto nextButton = new Button(
		scene_, TextureManager::get("Button-Next"),
		Vector2D<int>(tutorialArea_.x - WIN_WIDTH / 10, tutorialArea_.y + WIN_HEIGHT / 10),
		Vector2D<int>(WIN_WIDTH / 15, WIN_HEIGHT / 21), nextTutorial);

	const auto closeButton = new Button(scene_,
		TextureManager::get("Button-Continue"), Vector2D<int>(tutorialArea_.x + WIN_WIDTH / 10, tutorialArea_.y + WIN_HEIGHT / 10), Vector2D<int>(WIN_WIDTH / 15, WIN_HEIGHT / 21), skipTutorial);

	addChild(dialogueBackground);
	addChild(closeButton);
	addChild(nextButton);

	readFromFile("../tutorials/" + filename + ".txt", FontManager::get(fontfile), tutorialArea_, dialogueBackground->getRect());

	currentTutorial->addEventListener(new TutorialSceneOnClick(currentTutorial));
	dialogueBackground->addEventListener(new TutorialSceneOnClick(dialogueBackground));
}

TutorialSequence::~TutorialSequence() {
	while (tutorials.size() != 0) {
		delete tutorials.front();
		tutorials.pop();
	}
}

void TutorialSequence::readFromFile(const std::string &filename,
                                    Font *textFont, SDL_Rect tutorialArea, SDL_Rect dialogueBackground) {
  std::ifstream file;
  file.open(filename);
  if (!file.is_open())
    throw new DrakhtarError("Could not find file");

  size_t lines, i;
  file >> lines;

  for (size_t i = 0; i < lines && !file.eof(); i++) {
    tutorials.push(new TutorialBox(scene_, file, textFont, tutorialArea, dialogueBackground));
  }

  file.close();

  createNextTutorial();
}

void TutorialSequence::createNextTutorial() {
	if (tutorials.size() != 0) {
		if (Game::getSceneMachine()->getCurrentScene()->getSkip())
			destroy();
		else
		{
			currentTutorial = tutorials.front();
			tutorials.pop();
		}
	}
	else {
		destroy();
	}
}


void TutorialSequence::render() const {
	if (currentTutorial != nullptr) {
		GameObject::render();
		currentTutorial->render();
	}
}

void TutorialSceneOnClick::onClickStop(SDL_Point point) {
	static_cast<TutorialSequence*>(getGameObject()->getParent())->createNextTutorial();  // NOLINT
}

