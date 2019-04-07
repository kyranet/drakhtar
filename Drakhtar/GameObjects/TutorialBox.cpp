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

TutorialBox::TutorialBox(Scene *scene, std::ifstream &file, Font *textfont,
                         SDL_Rect tutorialArea, SDL_Rect dialogueBackground)
    : GameObject(scene, nullptr, Vector2D<int>(WIN_WIDTH / 2, WIN_HEIGHT / 2),
                 Vector2D<int>(1, 1)) {
  readFromFile(file);

  int lineJumpLimit = dialogueBackground.w * 0.95;

  auto tutorialImage = new GameObject(
      scene, TextureManager::get(imageText_),
      Vector2D<int>(tutorialArea.x,
                    dialogueBackground.y + dialogueBackground.h / 3),
      Vector2D<int>(tutorialArea.h * WIN_WIDTH / 4,
                    tutorialArea.h * WIN_HEIGHT / 4));

  SDL_Color textColor = {0, 0, 0, 1};

  auto tutorialTextSprite =
      new Text(scene_, textfont,
               Vector2D<int>(tutorialArea.x + dialogueBackground.w / 80,
                             tutorialArea.y - dialogueBackground.h / 80),
               textColor, dialogText_, lineJumpLimit);

  addChild(tutorialImage);
  addChild(tutorialTextSprite);

  /*nextButton->addEventListener(
      new TutorialSceneOnClick(nextButton));
  continueButton->addEventListener(
      new TutorialSceneOnClick(continueButton));*/
}

void TutorialBox::readFromFile(std::ifstream &file) {
  file >> imageText_;

  std::string text;       // full dialog text
  std::string word = "";  // word added to text each iteration
  while (word != ".") {
    file >> word;
    if (word != ".") text += word + " ";
  }
  dialogText_ = text;
}
