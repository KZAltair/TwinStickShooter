#include "Assets.h"
#include <algorithm>

Assets::Assets()
{

}

Assets::~Assets()
{
	for (auto v = mSprites.begin(); v != mSprites.end(); v++)
	{
		delete v->second;
	}
}

void Assets::LoadSprites()
{
	auto load = [&](std::string sName, std::wstring FileName)
	{
		Surface* s = new Surface(FileName);
		mSprites[sName] = s;
	};

	load("hero", L"heropng.png");
}