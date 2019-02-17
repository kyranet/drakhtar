#include "Box.h"

Box::Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, GameObject* go)
	: GameObject(t, pos, size), content(go)
{
}

Box::~Box() {
	content = nullptr;
}

void Box::render() const {
	GameObject::render();
	if (content != nullptr) {
		content->render();
	}
}
