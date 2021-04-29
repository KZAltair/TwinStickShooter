#include "TileMap.h"
#include <assert.h>

TileMap::TileMap()
{
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
			int TileValue = Map[y][x];
			int MinX = (int)UpperLeft + x * (int)TileWidth;
			int MaxX = MinX + (int)TileWidth;
			int MinY = (int)UpperTop + y * (int)TileHeight;
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

bool TileMap::IsWalkable(const Vec2& pos)
{
	int TileX = (int)(pos.x / TileWidth);
	int TileY = (int)(pos.y / TileHeight);

	if (pos.x > 0 && pos.x < TileWidth * countX &&
		pos.y > 0 && pos.y < TileHeight * countY)
	{
		int TileValue = Map[TileY][TileX];
		if (TileValue == 2)
		{
			return true;
		}
	}
	return false;
}

Vec2 TileMap::GetTileCorner() const
{
	return Vec2(UpperLeft, UpperTop);
}

tilemap_position TileMap::GetTileMapPosition(const Vec2& pos) const
{
	tilemap_position Result = {};
	int TileX = (int)(pos.x / TileWidth);
	int TileY = (int)(pos.y / TileHeight);
	Result.TileX = TileX;
	Result.TileY = TileY;
	return Result;
}
