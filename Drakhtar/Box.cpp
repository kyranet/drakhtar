#include "Box.h"
#include "Unit.h"
#include"TextureManager.h"

Box::Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, Vector2D<int> bi, Unit* go) :
	GameObject(t, pos, size), boardIndex(bi), content(go) 
{
	textureHover = TextureManager::get("UI-cellHover");
	hovered = false;
}

Box::~Box() {
	content = nullptr;
}

// Renders itself and its content
void Box::render() {
	if (!hovered) {
		GameObject::render();
	}
	else 
	{ 
		SDL_Rect dest{
		pos_.getX() - size_.getX() / 2,
		pos_.getY() - size_.getY() / 2,
		size_.getX(),
		size_.getY()
		};
		textureHover->render(dest, texture_->getAnimation()[texture_->getFrame()]); 
	}
	setHovered(false);
	if (content != nullptr) {
		content->render();
	}
}

void Box::handleEvents(SDL_Event event)
{
	SDL_Point p = { event.motion.x, event.motion.y };
	if (SDL_PointInRect(&p, &this->getRect())) {
		hovered = true;
	}
	else { hovered = false; }
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