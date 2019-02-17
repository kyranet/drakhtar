#pragma once

//#include "GameObject.h"
#include "Unit.h"

class Box : public GameObject {
protected:
	int boardX, boardY;
	vector2d boardIndex;
	Unit* content;
public:
	Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, Unit* go);
	virtual ~Box();

	virtual void render() const;
	Unit* getContent();
	vector2d getIndex();
	void setContent(Unit* object);
};
