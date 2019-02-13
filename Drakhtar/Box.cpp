#include "Box.h"

Box::Box(Texture* t, vector2d pos, vector2d size, GameObject* go) : GameObject(t, pos, size), content(go) {
}

Box::~Box() {
	content = nullptr;
}

void Box::render() const {
	if (content != nullptr) {
		content->render();
	}
}
