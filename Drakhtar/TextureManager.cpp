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

TextureManager::TextureManager()
	: stack_(stack<TextureInfo>())
{
}

TextureManager::~TextureManager()
{
	while (!stack_.empty()) stack_.pop();
	for (auto pair : (*this))
		delete pair.second;
	clear();
}

void TextureManager::add(string name, string path, ushort columns, ushort rows)
{
	stack_.push(TextureInfo{ name, path, columns, rows });
}

void TextureManager::init(SDL_Renderer* renderer)
{
	while (!stack_.empty())
	{
		auto info = stack_.top();
		auto texture = (new Texture(renderer))->loadFromImage(info.path, info.rows, info.columns);
		insert(pair<string, Texture*>(info.name, texture));
		stack_.pop();
	}
}

Texture* TextureManager::get(string name)
{
	return (*getInstance())[name];
}
