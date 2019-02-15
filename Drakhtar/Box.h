#pragma once

#include "GameObject.h"

class Box : public GameObject {
protected:
	int boardX, boardY;
	vector2d boardIndex;
	GameObject* content;
public:
	Box(Texture* t, vector2d pos, vector2d size, int boardX, int boardY, GameObject* go);
	virtual ~Box();

	virtual void render() const;
	GameObject* getContent();
	vector2d getIndex();
	void setContent(GameObject* object);
};