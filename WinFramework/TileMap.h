#pragma once
#include "Graphics.h"
#include "Vec2.h"

struct canonical_position
{
	int MapX;
	int MapY;

	int TileX;
	int TileY;

	Vec2 pos;
};

struct raw_position
{
	int MapX;
	int MapY;

	float X;
	float Y;
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
	bool IsWorldWalkable(const canonical_position& CanPos);
	Vec2 GetTileCorner() const;
	void SetWorldPosition(const canonical_position& Pos);
	int* GetTileMap(unsigned int MX, unsigned int MY);
	int GetTileValue(int* TileMap, int TestTileX, int TestTileY) const;
	int GetTileSizeInPixels() const;
	canonical_position GetCanonicalPosition(raw_position Pos);
	void RemapCoord(int TileCount, int* Map, int* Tile, float* TileRel);
	canonical_position RemapPosition(canonical_position Pos);
	canonical_position GetTileMapPosition()const;
	int GetPixelsFromMeters()const;
	float GetTileSizeInMeters() const;

private:
	bool IsTileWalkable(int* TileMap, int TileX, int TileY);
private:
	static constexpr unsigned int countX = 17;
	static constexpr unsigned int countY = 9;
	static constexpr unsigned int mapSize = 2;
	static constexpr int TileSizeInPixels = 80;
	static constexpr float TileSizeInMeters = 1.0f;
	static constexpr int MetersToPixels = TileSizeInPixels / TileSizeInMeters;
	float UpperLeftX = -(float)(TileSizeInPixels)/2.0f;
	float UpperLeftY = 0.0f;

	world World[mapSize][mapSize];
	canonical_position CanPos = {};

	int Map00[countY][countX] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,1,2,1,2,2,2,2,2,1},
		{1,2,1,1,1,2,2,2,2,2,1,2,2,2,2,2,2},
		{1,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
	};
	int Map01[countY][countX] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1},
		{2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
	};
	int Map10[countY][countX] =
	{
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2},
		{1,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	int Map11[countY][countX] =
	{
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,2,1,2,2,2,2,2,2,1},
		{2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
};