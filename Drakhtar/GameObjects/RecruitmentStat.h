// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "GameObject.h"
#include "EventListeners/UnitStoreController.h"
class Scene;
class Text;
class Font;
class RecruitmentStat : public GameObject {
private:
	StoreUnit* currentSelected_;
public:
	RecruitmentStat(Scene *scene,SDL_Rect BoxArea, StoreUnit* controller);
	void writeStat();
	~RecruitmentStat();
};
