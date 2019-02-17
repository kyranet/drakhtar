#include "Box.h"
#include "Unit.h"

Box::Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, int bx, int by, Unit* go) :
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

Unit * Box::getContent() {
	return content;
}

Vector2D<int> Box::getIndex() {
	return { boardX, boardY };
}

void Box::setContent(Unit* object) {
	content = object;
}
