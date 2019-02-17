#pragma once

#include "GameObject.h"
//#include "Unit.h"

class Unit;

class Box : public GameObject {
protected:
	int boardX, boardY;
	Vector2D<int> boardIndex;
	Unit* content;
public:
	Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, int boardX, int boardY, Unit* go);
	virtual ~Box();

	virtual void render() const;
	Unit* getContent();
	Vector2D<int> getIndex();
	void setContent(Unit* object);

};
