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
			int* TileMap = GetTileMap(MapX, MapY);
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

bool TileMap::IsWalkable(const Vec2& pos)
{
	TX = (int)(pos.x / TileWidth);
	TY = (int)(pos.y / TileHeight);
	MapX = rawPos.MapX;
	MapY = rawPos.MapY;

	if (TX < 0)
	{
		TX = countX + TX;
		--MapX;
	}
	if (TX >= countX)
	{
		TX = TX - countX;
		MapX++;
	}
	if (TY < 0)
	{
		TY = countY + TY;
		--MapY;
	}
	if (TY >= countY)
	{
		TY = TY - countY;
		MapY++;
	}
	int* TileMap = GetTileMap(MapX, MapY);
	if (TileMap)
	{
		int TileValue = GetTileValue(TileMap, TX, TY);
		if (TileValue == 2)
		{
			return true;
		}
	}	
	return false;
}

Vec2 TileMap::GetTileCorner() const
{
	return Vec2(UpperLeftX, UpperLeftY);
}

void TileMap::SetWorldPosition(const tilemap_position& Pos)
{
	rawPos = Pos;
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

tilemap_position TileMap::GetTileMapPosition() const
{
	tilemap_position Result = rawPos;
	return Result;
}

tilemap_position TileMap::ToWorldLocation(tilemap_position* Pos)
{
	tilemap_position Result = *Pos;
	float X = Pos->pos.x - UpperLeftX;
	float Y = Pos->pos.y - UpperLeftY;
	Result.TileX = (int)(X / TileWidth);
	Result.TileY = (int)(Y / TileHeight);
	Result.pos.x = X - TX *TileWidth;
	Result.pos.y = Y - TY *TileHeight;
	return Result;
}
