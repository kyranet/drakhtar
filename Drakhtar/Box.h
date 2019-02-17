#pragma once

#include "GameObject.h"

class Unit;

class Box : public GameObject {
protected:
	Vector2D<int> boardIndex;
	Unit* content;
public:
	Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, Vector2D<int> boardIndex, Unit* go);
	virtual ~Box();

	virtual void render() const;
	Unit* getContent();
	Vector2D<int> getIndex();
	void setContent(Unit* object);
};
