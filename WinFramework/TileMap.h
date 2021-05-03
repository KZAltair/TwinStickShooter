#pragma once
#include "Graphics.h"
#include "Vec2.h"

struct tilemap_position
{
	int MapX;
	int MapY;

	int TileX;
	int TileY;

	Vec2 pos;
};

struct world
{
	int* TileMap;
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
	void SetWorldPosition(const tilemap_position& Pos);
	int* GetTileMap(unsigned int MX, unsigned int MY);
	int GetTileValue(int* TileMap, int TestTileX, int TestTileY) const;
	tilemap_position GetTileMapPosition()const;
	tilemap_position ToWorldLocation(tilemap_position* Pos);
private:
	static constexpr unsigned int countX = 17;
	static constexpr unsigned int countY = 9;
	static constexpr unsigned int mapSize = 2;
	float TileWidth = 80.0f;
	float TileHeight = 80.0f;
	float UpperLeftX = -40.0f;
	float UpperLeftY = 0.0f;
	int MapX = 0;
	int MapY = 0;
	int TX = 0;
	int TY = 0;

	world World[mapSize][mapSize];
	tilemap_position rawPos = {};

	int Map00[countY][countX] =
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
	int Map01[countY][countX] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,1,1,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,1,1,2,2,2,2,2,1},
		{2,2,1,1,1,2,2,2,2,1,1,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
	};
	int Map10[countY][countX] =
	{
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	int Map11[countY][countX] =
	{
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{2,2,2,1,1,2,2,2,2,1,1,1,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
};