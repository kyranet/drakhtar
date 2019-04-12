#include "HealthBar.h"
#include "../Managers/TextureManager.h"
#include "../Scenes/Scene.h"
#include "../Utils/Constants.h"

HealthBar::HealthBar(Scene * scene, Vector2D<int> pos):
	GameObject(scene, TextureManager::get("UI-healthBar_background"), pos, Vector2D<int>(WIN_WIDTH/20, WIN_HEIGHT/60))
{
	lifeBar = new GameObject(scene, TextureManager::get("UI-healthBar_life"), pos, Vector2D<int>(WIN_WIDTH / 20, WIN_HEIGHT / 60));
	damageBar = new GameObject(scene, TextureManager::get("UI-healthBar_damage"), pos, Vector2D<int>(WIN_WIDTH / 20, WIN_HEIGHT / 60));
	addChild(lifeBar);
	addChild(damageBar);
	damageBar->setActive(false);

	originalWidth = lifeBar->getRect().w;
	currentHealth = maxHealth;
}

HealthBar::~HealthBar()
{
	delete lifeBar;
	delete damageBar;
}

void HealthBar::update()
{
	if (damageAnimationPlaying && damageBar->getRect().w > 0)
	{
		if (damageBar->getRect().w > damageAnimationSpeed)
		{
			damageBar->setSize(Vector2D<int>(damageBar->getRect().w - damageAnimationSpeed, damageBar->getRect().h));
		}
		else
		{
			damageBar->setSize(Vector2D<int>(0, damageBar->getRect().h));
			damageBar->setActive(false);
			damageAnimationPlaying = false;
		}
	}
}

void HealthBar::takeDamage()
{
	int damageProportion = currentHealth / maxHealth;
	lifeBar->setSize(Vector2D<int>(originalWidth * damageProportion, lifeBar->getRect().h);
	damageBar->setActive(true);
	damageAnimationPlaying = true;
}
