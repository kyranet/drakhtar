#pragma once

#include <map>
#include <SDL.h>

using namespace std;

template<class V>
class ResourceManager
{
protected:
	map<string, V> map_;
public:
	ResourceManager() {};
	virtual ~ResourceManager() {};
	virtual void init(SDL_Renderer* renderer) = 0;
};
