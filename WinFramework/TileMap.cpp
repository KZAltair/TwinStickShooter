#include "TileMap.h"
#include <assert.h>
#include <math.h>

TileMap::TileMap()
{
	World[0][0].TileMap = (int*)Map00;
	World[0][1].TileMap = (int*)Map01;
	World[1][0].TileMap = (int*)Map10;
	World[1][1].TileMap = (int*)Map11;
}

TileMap::~TileMap()
{
}

void TileMap::Draw(int* Colors, Graphics& gfx)
{
	for (int y = 0; y < countY; y++)
	{
		for (int x = 0; x < countX; x++)
		{
			int* TileMap = GetTileMap(CanPos.MapX, CanPos.MapY);
			if (TileMap)
			{
				int TileValue = GetTileValue(TileMap, x, y);
				int MinX = (int)UpperLeftX + x * TileSizeInPixels;
				int MaxX = MinX + TileSizeInPixels;
				int MinY = (int)UpperLeftY + y * TileSizeInPixels;
				int MaxY = MinY + TileSizeInPixels;
				unsigned char ColorValue = 0;
				if (TileValue == 1)
				{
					ColorValue = 122;
				}
				if (TileValue == 2)
				{
					ColorValue = 80;
				}
				gfx.DrawRectancle(Colors, MinX, MaxX, MinY, MaxY, ColorValue, ColorValue, ColorValue);
			}
			
		}
	}
}

bool TileMap::IsWorldWalkable(const canonical_position& CanPos)
{
	bool isWalkable = false;
	int* TileMap = GetTileMap(CanPos.MapX, CanPos.MapY);
	isWalkable = IsTileWalkable(TileMap, CanPos.TileX, CanPos.TileY);
	return isWalkable;
}

bool TileMap::IsTileWalkable(int* TileMap, int TestTileX, int TestTileY)
{
	if (TileMap)
	{
		if (TestTileX >= 0 && TestTileX < countX &&
			TestTileY >= 0 && TestTileY < countY)
		{
			unsigned int TileValue = GetTileValue(TileMap, TestTileX, TestTileY);
			if (TileValue == 2)
			{
				return true;
			}
		}
	}
	return false;
}

Vec2 TileMap::GetTileCorner() const
{
	return Vec2(UpperLeftX, UpperLeftY);
}

void TileMap::SetWorldPosition(const canonical_position& Pos)
{
	CanPos = Pos;
}

int* TileMap::GetTileMap(unsigned int MX, unsigned int MY)
{
	assert(MX >= 0);
	assert(MX < mapSize);
	assert(MY >= 0);
	assert(MY < mapSize);
	int* Result = World[MY][MX].TileMap;
	return Result;
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

canonical_position TileMap::GetCanonicalPosition(raw_position Pos)
{
	canonical_position Result;
	Result.MapX = Pos.MapX;
	Result.MapY = Pos.MapY;

	float X = Pos.X - UpperLeftX;
	float Y = Pos.Y - UpperLeftY;

	Result.TileX = (int)(floorf(X / (float)(TileSizeInPixels)));
	Result.TileY = (int)(floorf(Y / (float)(TileSizeInPixels)));

	Result.pos.x = X - (float)(Result.TileX * TileSizeInPixels);
	Result.pos.y = Y - (float)Result.TileY * TileSizeInPixels;

	if (Result.TileX < 0)
	{
		Result.TileX = countX + Result.TileX;
		--Result.MapX;
	}
	if (Result.TileX >= countX)
	{
		Result.TileX = Result.TileX - countX;
		++Result.MapX;
	}
	if (Result.TileY < 0)
	{
		Result.TileY = countY + Result.TileY;
		--Result.MapY;
	}
	if (Result.TileY >= countY)
	{
		Result.TileY = Result.TileY - countY;
		++Result.MapY;
	}
	return Result;
}

void TileMap::RemapCoord(int TileCount, int* Map, int* Tile, float* TileRel)
{
	int Offset = (int)(floorf(*TileRel / (float)(TileSizeInMeters)));
	*Tile += Offset;
	*TileRel -= (float)(Offset * TileSizeInMeters);

	assert(*TileRel >= 0.0f);
	assert(*TileRel <= (float)TileSizeInMeters);

	if (*Tile < 0)
	{
		*Tile = TileCount + *Tile;
		--*Map;
	}
	if (*Tile >= TileCount)
	{
		*Tile = *Tile - TileCount;
		++*Map;
	}
}

canonical_position TileMap::RemapPosition(canonical_position Pos)
{
	canonical_position Result = Pos;
	RemapCoord(countX, &Result.MapX, &Result.TileX, &Result.pos.x);
	RemapCoord(countY, &Result.MapY, &Result.TileY, &Result.pos.y);
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


