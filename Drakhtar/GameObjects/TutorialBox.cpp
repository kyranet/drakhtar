#include "TutorialBox.h"
#include "../Errors/DrakhtarError.h"
#include "../GameObjects/Button.h"
#include "../Managers/FontManager.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/GameScene.h"
#include "../Scenes/Scene.h"
#include "../Structures/Font.h"
#include "../Structures/Game.h"
#include "../Utils/Constants.h"
#include "GameObject.h"
#include "Text.h"

void skipDialog() {
  // Game::getSceneMachine()->getCurrentScene()->setSkip(true);
}

TutorialBox::TutorialBox(Scene *scene, const std::string &filename,
                         const std::string &fontFile)
    : GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                 Vector2D<int>(1, 1)) {

  readFromFile("../tutorials/" + filename + ".txt");

  const auto tutorialArea_ = getRect();

  auto tutorialBackground = new GameObject(
      scene_, TextureManager::get("UI-tutorialBackground"),
      Vector2D<int>(tutorialArea_.x + WIN_WIDTH / 4,
                    WIN_HEIGHT - tutorialArea_.h * WIN_HEIGHT / 1.5),
      Vector2D<int>(tutorialArea_.w * WIN_WIDTH / 3,
                    tutorialArea_.h * WIN_HEIGHT / 3));

  int lineJumpLimit = tutorialBackground->getRect().x + WIN_WIDTH / 2;

  auto tutorialImage = new GameObject(
      scene, TextureManager::get(imageText_),
      Vector2D<int>(tutorialArea_.x + tutorialArea_.w / 8,
                    tutorialArea_.y - tutorialArea_.h / 3),
      Vector2D<int>(tutorialArea_.h / 1.5, tutorialArea_.h / 1.5));

  SDL_Color textColor = {0, 0, 0, 1};

	auto dialogTextSprite =
		new Text(scene_, textfont,
			Vector2D<int>(tutorialArea_.x + tutorialArea_.w / 2.1,
				tutorialArea_.y + tutorialArea_.h / 2),
			textColor, dialogText_, lineJumpLimit);
	
	const auto skip = new Button(scene_, TextureManager::get("Button-Play"),
		Vector2D<int>(tutorialArea_.x + tutorialArea_.w / 1.05, tutorialArea_.y),
		Vector2D<int>(30, 30), skipDialog);

  const auto continueButton = new Button(
      scene_, TextureManager::get("Button-Play"), // Button continue
      Vector2D<int>(tutorialArea_.x + tutorialArea_.w / 1.05, tutorialArea_.y),
      Vector2D<int>(30, 30), skipDialog);

  /*const auto nextButton = new Button(scene_,
     TextureManager::get("Button-Next"), Vector2D<int>(tutorialArea_.x +
     tutorialArea_.w / 1.05, tutorialArea_.y), Vector2D<int>(30, 30),
     skipDialog);*/

  addChild(tutorialImage);
  addChild(dialogTextSprite);
  addChild(tutorialBackground);
  addChild(continueButton);
  // addChild(nextButton);
}

void TutorialBox::readFromFile(const std::string &filename) {
  std::ifstream file;
  file.open(filename);

  if (!file.is_open())
    throw new DrakhtarError("Could not find file");
  file >> imageText_;

  std::string text;      // full dialog text
  std::string word = ""; // word added to text each iteration
  while (word != ".") {
    file >> word;
    if (word != ".")
      text += word + " ";
  }
  dialogText_ = text;

  file.close();
}
