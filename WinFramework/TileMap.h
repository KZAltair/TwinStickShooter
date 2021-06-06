#pragma once
#include "Graphics.h"
#include "Vec2.h"

struct canonical_position
{
	u32 AbsTileX;
	u32 AbsTileY;

	Vec2 pos;
};

struct tile_chunk_position
{
	u32 TileChunkX;
	u32 TileChunkY;

	u32 RelTileX;
	u32 RelTileY;
};

struct tile_chunk
{
	u32* Tiles;
};

struct world
{
	tile_chunk* TileChunks;
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
	int GetTileValue(int* TileMap, int TestTileX, int TestTileY) const;
	int GetTileSizeInPixels() const;
	void RemapCoord(u32* Tile, float* TileRel);
	canonical_position RemapPosition(canonical_position Pos);
	canonical_position GetTileMapPosition()const;
	int GetPixelsFromMeters()const;
	void InitMap();
	float GetTileSizeInMeters() const;
	bool IsMapInitialized()const;
private:
	bool IsTileWalkable(tile_chunk* Chunk, u32 TestTileX, u32 TestTileY);
	tile_chunk_position GetTileChunkPosition(u32 AbsTileX, u32 AbsTileY);
	tile_chunk* GetTileChunk(u32 ChunkX, u32 ChunkY);
	u32 GetTileValueFromChunk(tile_chunk* Chunk, u32 TestTileX, u32 TestTileY) const;
	u32 GetTileValueFromWorld(u32 TileX, u32 TileY);
	void SetTileValueInChunk(u32 AbsTileX, u32 AbsTileY, u32 TileValue);
private:
	static constexpr unsigned int countX = 17;
	static constexpr unsigned int countY = 9;
	static constexpr u32 MapSizeX = 10;
	static constexpr u32 MapSizeY = 10;
	static constexpr u32 ChunkDim = 16;
	static constexpr int TileSizeInPixels = 10;
	static constexpr float TileSizeInMeters = 1.0f;
	static constexpr i32 MetersToPixels = (i32)((float)TileSizeInPixels / TileSizeInMeters);
	float UpperLeftX = -(float)(TileSizeInPixels)/2.0f;
	float UpperLeftY = 0.0f;

	world World;
	tile_chunk* CurrentChunk = nullptr;
	tile_chunk TileMapChunk;
	canonical_position CanPos = {};

	u32 ChunkShift = 4;
	u32 ChunkMask = (1 << ChunkShift) - 1;
	bool MapInit = false;
	//u32 ChunkMask = 0xFF;

	/*
	u32 TempTiles[ChunkDim][ChunkDim] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,1,2,1,2,2,2,2,2,1,1,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1},
		{1,2,1,1,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1},
		{1,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,1,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1,1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,1,2,2,2,2,2,2,1,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1},
		{1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

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
	*/
};