#include "SkillButtonListener.h"
#include "GameObjects/GameObject.h"

SkillButtonListener::SkillButtonListener(GameObject* hoveredObject,
                                         GameObject* panel)
    : ListenerOnHover(hoveredObject), panel_(panel) {}

SkillButtonListener::~SkillButtonListener() {}

void SkillButtonListener::onHoverStart() { panel_->setRenderizable(true); }

void SkillButtonListener::onHoverStop() { panel_->setRenderizable(false); }