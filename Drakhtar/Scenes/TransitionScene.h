// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#pragma once
#include "Scene.h"

class TransitionScene final : public Scene {
public:		
	TransitionScene(int battle);
	void preload() override;
	//void run();
private:
	int battle_;
	//DialogScene dialog;
};
