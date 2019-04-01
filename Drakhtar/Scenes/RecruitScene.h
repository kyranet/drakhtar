// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Scene.h"

class GameObject;

class RecruitScene : public Scene {
private:
	GameObject * soldier = nullptr;
public:
	//virtual ~RecruitScene();
	void preload() override;
	void update() override;
};