#pragma once
#include "Graphics.h"
#include "Vec2.h"

struct tilemap_position
{
	int TileX;
	int TileY;
};

class TileMap
{
public:
	TileMap();
	TileMap(const TileMap&) = delete;
	TileMap operator=(const TileMap&) = delete;
	~TileMap();
	void Draw(int* Colors, Graphics& gfx);
	bool IsWalkable(const Vec2& pos);
	Vec2 GetTileCorner() const;
	tilemap_position GetTileMapPosition(const Vec2& pos)const;

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