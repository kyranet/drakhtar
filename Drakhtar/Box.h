#pragma once

#include "GameObject.h"

class Box : public GameObject {
protected:
	GameObject* content;
public:
	Box(Texture* t, Vector2D<int> pos, Vector2D<int> size, GameObject* go);
	virtual ~Box();

	virtual void render() const;
};
