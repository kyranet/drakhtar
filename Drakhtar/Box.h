#pragma once

#include "GameObject.h"

class Unit;

class Box : public GameObject {
protected:
	Vector2D<int> boardIndex;
	Unit* content;
	int currentTexture;
	Texture * cellTextures[3];
public:
	Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, Vector2D<int> boardIndex, Unit* go);
	virtual ~Box();

	virtual void render();
	virtual void handleEvents(SDL_Event event);
	Unit* getContent();
	Vector2D<int> getIndex();
	void setContent(Unit* object);
	bool isEmpty();
	int getCurrentTexture() const;
	void setCurrentTexture(int textureInd);

	const enum textureInd {
		base,
		hover,
		movable
	};
};