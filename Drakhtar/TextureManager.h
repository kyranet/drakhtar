#pragma once

#include "ResourceManager.h"
#include "Texture.h"
#include <stack>

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
	~TextureInfo() { animations.clear(); }
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
