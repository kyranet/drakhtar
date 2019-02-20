#include "TextureManager.h"
#include "DrakhtarError.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}

	return instance;
}

TextureManager::TextureManager() {}

TextureInfo* TextureManager::add(string name, string path, ushort columns, ushort rows)
{
	auto info = new TextureInfo(name, path, columns, rows);
	stack_.push(info);
	return info;
}

void TextureManager::init(SDL_Renderer* renderer)
{
	while (!stack_.empty())
	{
		auto info = stack_.top();
		auto texture = (new Texture(renderer))->loadFromImage(info->path, info->rows, info->columns);

		// Add all the queued animations
		for (auto animation : info->animations) texture->addAnimation(animation.name, animation.frames);

		// If there was no default animation override, add it
		if (!texture->hasAnimation("default"))
		{
			ushort frames = texture->getColumnAmount() * texture->getRowAmount();
			vector<ushort> animation(frames);
			for (ushort i = 0; i < frames; i++) animation[i] = i;
			texture->addAnimation("default", animation);
		}

		texture->setAnimation("default");

		// Insert the texture to the map, pop the stack, and delete the temporary information
		insert(pair<string, Texture*>(info->name, texture));
		stack_.pop();
		delete info;
	}
}

void TextureManager::tick()
{
	if (instance == nullptr) return;
	for (auto pair : (*this))
	{
		pair.second->tick();
	}
}

Texture* TextureManager::get(string name)
{
	return (*getInstance())[name];
}

void TextureManager::destroy()
{
	if (instance != nullptr)
	{
		// while (!instance->stack_.empty()) instance->stack_.pop();
		for (auto pair : (*instance))
			delete pair.second;
		instance->clear();
		instance = nullptr;
	}
}
