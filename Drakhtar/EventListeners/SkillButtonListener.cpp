// Copyright 2019 the Drakhtar authors. All rights reserved. MIT license.

#include "SkillButtonListener.h"

#include "GameObjects/GameObject.h"

SkillButtonListener::SkillButtonListener(GameObject* hoveredObject,
                                         GameObject* panel)
    : ListenerOnHover(hoveredObject), panel_(panel) {}

SkillButtonListener::~SkillButtonListener() {}

void SkillButtonListener::onHoverStart() { panel_->setRenderable(true); }

void SkillButtonListener::onHoverStop() { panel_->setRenderable(false); }
