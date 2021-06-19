#pragma once

#include <map>
#include "Surface.h"

class Assets
{
public:
	static Assets& get()
	{
		static Assets assets;
		return assets;
	}
	Assets(const Assets&) = delete;
	void operator=(const Assets&) = delete;

	Surface* GetSprite(std::string name)
	{
		return mSprites[name];
	}

	void LoadSprites();
private:
	Assets();
	~Assets();
private:
	std::map<std::string, Surface*> mSprites;
};