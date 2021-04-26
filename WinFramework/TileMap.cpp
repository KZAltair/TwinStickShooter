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
