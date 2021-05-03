#include "TileMap.h"
#include <assert.h>

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
				int MinX = (int)UpperLeftX + x * (int)TileWidth;
				int MaxX = MinX + (int)TileWidth;
				int MinY = (int)UpperLeftY + y * (int)TileHeight;
				int MaxY = MinY + (int)(TileHeight);
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

bool TileMap::IsWorldWalkable(const raw_position& pos)
{
	bool isWalkable = false;
	CanPos = GetCanonicalPosition(pos);
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

canonical_position TileMap::GetCanonicalPosition(raw_position Pos)
{
	canonical_position Result;
	Result.MapX = Pos.MapX;
	Result.MapY = Pos.MapY;

	float X = Pos.X - UpperLeftX;
	float Y = Pos.Y - UpperLeftY;

	Result.TileX = (int)(X / TileWidth);
	Result.TileY = (int)(Y / TileHeight);

	Result.pos.x = X - Result.TileX * TileWidth;
	Result.pos.y = Y - Result.TileY * TileHeight;

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

canonical_position TileMap::GetTileMapPosition() const
{
	canonical_position Result = CanPos;
	return Result;
}


