#include "Graphics.h"
#include <iostream>
#include <assert.h>

Graphics::Graphics(int WindowWidth, int WindowHeight)
	:
	WinWidth(WindowWidth),
	WinHeight(WindowHeight)
{
}

Graphics::~Graphics()
{
}

void Graphics::FillScreenFast(int* Colors, unsigned char r, unsigned char g, unsigned char b)
{
	for (int* i = Colors, *end = &Colors[WinWidth * WinHeight]; i < end; i++)
	{
		*i = (r << 16) | (g << 8) | b;
	}
}

void Graphics::ClearScreenSuperFast(int* Colors)
{
	std::memset(Colors, 0, WinWidth * WinHeight * 4);
}

void Graphics::DrawPixel(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	if (x > 0 && x < WinWidth && y > 0 && y < WinHeight)
	{
		Colors[y * WinWidth + x] = (r << 16) | (g << 8) | b;
	}
}

void Graphics::DrawRectancle(int* Colors, int xMin, int xMax, int yMin, int yMax, unsigned char r, unsigned char g, unsigned char b)
{
	for (int y = yMin; y < yMax; y++)
	{
		for (int x = xMin; x < xMax; x++)
		{
			DrawPixel(Colors, x, y, r, g, b);
		}
	}
}

