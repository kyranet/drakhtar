#include "Box.h"

Box::Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, GameObject* go)
	: GameObject(t, pos, size), content(go)
{
}

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
