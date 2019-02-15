#include "Box.h"

Box::Box(Texture* t, vector2d pos, vector2d size, int bx, int by, GameObject* go) : 
	GameObject(t, pos, size), boardX(bx), boardY(by), content(go) {}

Box::~Box() {
	content = nullptr;
}

// Renders itself and its content
void Box::render() const {
	GameObject::render();
	if (content != nullptr) {
		content->render();
	}
}

GameObject * Box::getContent() {
	return content;
}

vector2d Box::getIndex() {
	return { (float)boardX, (float)boardY };
}

void Box::setContent(GameObject* object) {
	content = object;
}
