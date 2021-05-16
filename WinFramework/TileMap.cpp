#include "TileMap.h"
#include <assert.h>
#include <math.h>

TileMap::TileMap()
{
	TileMapChunk.Tiles = (u32*)TempTiles;
	World.TileChunks = &TileMapChunk;
}

TileMap::~TileMap()
{
}

void TileMap::Draw(int* Colors, Graphics& gfx)
{
	u32 ScreenCenterX = (u32)(0.5f * 1280.0f);
	u32 ScreenCenterY = (u32)(0.5f * 720.0f);
	for (i32 RelRow = -10; RelRow < 10; ++RelRow)
	{
		for (i32 RelCol = -20; RelCol < 20; ++RelCol)
		{
			u32 Column = CanPos.AbsTileX + RelCol;
			u32 Row = CanPos.AbsTileY + RelRow;
			u32 TileValue = GetTileValueFromWorld(Column, Row);
			
			i32 MinX = ScreenCenterX - (i32)(CanPos.pos.x * GetPixelsFromMeters()) + RelCol * TileSizeInPixels;
			i32 MaxX = MinX + TileSizeInPixels;
			i32 MinY = ScreenCenterY - (i32)(CanPos.pos.y * GetPixelsFromMeters()) + RelRow * TileSizeInPixels;
			i32 MaxY = MinY + TileSizeInPixels;
			unsigned char ColorValue = 0;
			if (TileValue == 1)
			{
				ColorValue = 122;
			}
			if (TileValue == 2)
			{
				ColorValue = 80;
			}
			if (TileValue == 0)
			{
				ColorValue = 255;
			}
			if (Column == CanPos.AbsTileX && Row == CanPos.AbsTileY)
			{
				ColorValue = 0;
			}
			gfx.DrawRectancle(Colors, MinX, MaxX, MinY, MaxY, ColorValue, ColorValue, ColorValue);
			
		}
	}
}

bool TileMap::IsWorldWalkable(const canonical_position& CanPos)
{
	bool isWalkable = false;
	tile_chunk_position ChunkPos = GetTileChunkPosition(CanPos.AbsTileX, CanPos.AbsTileY);
	CurrentChunk = GetTileChunk(ChunkPos.TileChunkX, ChunkPos.TileChunkY);
	isWalkable = IsTileWalkable(CurrentChunk, ChunkPos.RelTileX, ChunkPos.RelTileY);
	return isWalkable;
}

u32 TileMap::GetTileValueFromWorld(u32 TileX, u32 TileY)
{
	u32 TileValue = 0;
	tile_chunk_position TestPos = GetTileChunkPosition(TileX, TileY);
	tile_chunk* TestChunk = GetTileChunk(TestPos.TileChunkX, TestPos.TileChunkY);
	TileValue = GetTileValueFromChunk(TestChunk, TestPos.RelTileX, TestPos.RelTileY);
	return TileValue;
}

bool TileMap::IsTileWalkable(tile_chunk* Chunk, u32 TestTileX, u32 TestTileY)
{
	if (Chunk)
	{
		u32 TileValue = GetTileValueFromChunk(Chunk, TestTileX, TestTileY);
		if (TileValue == 2)
		{
			return true;
		}
	}
	return false;
}

tile_chunk_position TileMap::GetTileChunkPosition(u32 AbsTileX, u32 AbsTileY)
{
	tile_chunk_position Result;
	Result.TileChunkX = AbsTileX >> ChunkShift;
	Result.TileChunkY = AbsTileY >> ChunkShift;
	Result.RelTileX = AbsTileX & ChunkMask;
	Result.RelTileY = AbsTileY & ChunkMask;
	return Result;
}

tile_chunk* TileMap::GetTileChunk(u32 ChunkX, u32 ChunkY)
{
	tile_chunk* Result = nullptr;
	if (ChunkX <= MapSizeX && ChunkY <= MapSizeY)
	{
		Result = &World.TileChunks[ChunkY * MapSizeX + ChunkX];
	}
	return Result;
}

u32 TileMap::GetTileValueFromChunk(tile_chunk* Chunk, u32 TestTileX, u32 TestTileY) const
{
	assert(TestTileX <= ChunkDim);
	assert(TestTileY <= ChunkDim);
	u32 TileValue = 0;
	if (Chunk)
	{
		TileValue = Chunk->Tiles[TestTileY * ChunkDim + TestTileX];
	}
	return TileValue;
}

Vec2 TileMap::GetTileCorner() const
{
	return Vec2(UpperLeftX, UpperLeftY);
}

void TileMap::SetWorldPosition(const canonical_position& Pos)
{
	CanPos = Pos;
}

int TileMap::GetTileValue(int* TileMap, int TestTileX, int TestTileY) const
{
	assert(TestTileX >= 0);
	assert(TestTileX < countX);
	assert(TestTileY >= 0);
	assert(TestTileY < countY);
	int TileValue = TileMap[TestTileY * countX + TestTileX];
	return TileValue;
}

int TileMap::GetTileSizeInPixels() const
{
	return TileSizeInPixels;
}


void TileMap::RemapCoord(u32* Tile, float* TileRel)
{
	i32 Offset = (i32)(floorf(*TileRel / (float)(TileSizeInMeters)));
	*Tile += Offset;
	*TileRel -= (float)(Offset * TileSizeInMeters);
	assert(*TileRel <= (float)TileSizeInMeters);
}

canonical_position TileMap::RemapPosition(canonical_position Pos)
{
	canonical_position Result = Pos;
	RemapCoord(&Result.AbsTileX, &Result.pos.x);
	RemapCoord(&Result.AbsTileY, &Result.pos.y);
	return Result;
}

canonical_position TileMap::GetTileMapPosition() const
{
	canonical_position Result = CanPos;
	return Result;
}

int TileMap::GetPixelsFromMeters() const
{
	return MetersToPixels;
}

float TileMap::GetTileSizeInMeters() const
{
	return TileSizeInMeters;
}


