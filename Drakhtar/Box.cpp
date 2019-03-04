#include "Box.h"
#include "Unit.h"

Box::Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, Vector2D<int> bi, Unit* go) :
	GameObject(t, pos, size), boardIndex(bi), content(go) {}

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

Vector2D<int> Box::getIndex() {
	return boardIndex;
}

Unit * Box::getContent() {
	return content;
}

void Box::setContent(Unit* object) {
	content = object;
}

bool Box::getHovered() {
	return hovered;
}

void Box::setHovered(bool hover) {
	hovered = hover;
}