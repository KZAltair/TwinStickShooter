#pragma once
#include "Graphics.h"

class TileMap
{
public:
	TileMap();
	TileMap(const TileMap&) = delete;
	TileMap operator=(const TileMap&) = delete;
	~TileMap();
	void Draw(int* Colors, Graphics& gfx);

private:
	static constexpr unsigned int countX = 17;
	static constexpr unsigned int countY = 9;
	float TileWidth = 80.0f;
	float TileHeight = 80.0f;
	float UpperLeft = -40.0f;
	float UpperTop = 0.0f;

	int Map[countY][countX] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,1,1,1,2,2,2,2,1,1,1,2,2,2,2,2},
		{1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
	};
};