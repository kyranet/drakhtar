#include "ButtonListener.h"
#include "GameObjects/Button.h"

void ButtonListener::onClickStart() {
  reinterpret_cast<Button*>(getGameObject())->call();
}
