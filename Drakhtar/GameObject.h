#pragma once

#include "Texture.h"

class GameObject
{
private:
	double pos_x;
	double pos_y;
	double size_x;
	double size_y;
	Texture* texture_;
public:
	GameObject(Texture* texture, double pos_x, double pos_y, double size_x, double size_y);
	virtual ~GameObject();
	virtual void render() const;
};

