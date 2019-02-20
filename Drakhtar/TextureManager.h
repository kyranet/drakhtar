#pragma once

#include "ResourceManager.h"
#include "Texture.h"
#include <stack>
#include <vector>

struct AnimationTextureInfo
{
	string name;
	vector<ushort> frames;
};

class TextureInfo
{
public:
	TextureInfo(string name, string path, ushort columns, ushort rows, vector<AnimationTextureInfo> animations = {})
		: name(name), path(path), columns(columns), rows(rows), animations(animations) {}
	string name;
	string path;
	ushort columns;
	ushort rows;
	vector<AnimationTextureInfo> animations;
	TextureInfo* addAnimation(string name, vector<ushort> frames)
	{
		animations.push_back({ name, frames });
		return this;
	}
};

class TextureManager : public ResourceManager<Texture*>
{
private:

	static TextureManager* instance;
	TextureManager();
	stack<TextureInfo*> stack_;
public:
	virtual ~TextureManager();
	TextureInfo* add(string name, string path, ushort columns, ushort rows);
	void init(SDL_Renderer* renderer);
	static Texture* get(string name);

	static TextureManager* getInstance();
};
