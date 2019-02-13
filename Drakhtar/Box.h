#pragma once

#include "GameObject.h"

class Box : public GameObject {
protected:
	GameObject* content;
public:
	Box(Texture* t, vector2d pos, vector2d size, GameObject* go);
	virtual ~Box();

	virtual void render() const;
};

