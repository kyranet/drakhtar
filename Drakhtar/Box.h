#pragma once

//#include "GameObject.h"
#include "Unit.h"

class Box : public GameObject {
protected:
	int boardX, boardY;
	vector2d boardIndex;
	Unit* content;
public:
	Box(Texture* t, vector2d pos, vector2d size, int boardX, int boardY, Unit* go);
	virtual ~Box();

	virtual void render() const;
	GameObject* getContent();
	Unit* getContent();
	vector2d getIndex();
	void setContent(Unit* object);
};