#pragma once

#include "ResourceManager.h"
#include "Texture.h"
#include <stack>

struct TextureInfo
{
	string name;
	string path;
	uint columns;
	uint rows;
};

class TextureManager : public ResourceManager<Texture*>
{
private:
	static TextureManager* instance;
	TextureManager();
	stack<TextureInfo> stack_;
public:
	virtual ~TextureManager();
	void add(string name, string path, ushort columns, ushort rows);
	void init(SDL_Renderer* renderer);
	static Texture* get(string name);

	static TextureManager* getInstance();
};
