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

void Graphics::DrawPixel(int* in_buffer, int x, int y, Color c)
{
	if (x > 0 && x < WinWidth && y > 0 && y < WinHeight)
	{
		in_buffer[y * WinWidth + x] = c.dword;
	}
}

void Graphics::DrawRectancle(int* Colors, int xMin, int xMax, int yMin, int yMax, unsigned char r, unsigned char g, unsigned char b)
{
	if (yMin > yMax)
	{
		for (int y = yMin; y != yMax; y--)
		{
			for (int x = xMin; x < xMax; x++)
			{
				DrawPixel(Colors, x, y, r, g, b);
			}
		}
	}
	else
	{
		for (int y = yMin; y < yMax; y++)
		{
			for (int x = xMin; x < xMax; x++)
			{
				DrawPixel(Colors, x, y, r, g, b);
			}
		}
	}
	
}

void Graphics::DrawSpriteNonChroma(int* in_buffer, int x, int y, const Surface& s)
{
	DrawSpriteNonChroma(in_buffer, x, y, s.GetRect(), s);
}

void Graphics::DrawSpriteNonChroma(int* in_buffer, int x, int y, Rect<float> srcRect, const Surface& s)
{
	DrawSpriteNonChroma(in_buffer, x, y, srcRect, Rect<float>(0.0f, (float)WinWidth, 0.0f, (float)WinHeight), s);
}

void Graphics::DrawSpriteNonChroma(int* in_buffer, int x, int y, Rect<float> srcRect, 
	const Rect<float> clip, const Surface& s)
{
	assert(srcRect.left >= 0);
	assert(srcRect.left <= s.GetWidth());
	assert(srcRect.top >= 0);
	assert(srcRect.bottom <= s.GetHeight());
	if ((float)x < clip.left)
	{
		srcRect.left += clip.left - (float)x;
		x = (int)clip.left;
	}
	if ((float)y < clip.top)
	{
		srcRect.top += clip.top - (float)y;
		y = (int)clip.top;
	}
	if ((float)x + srcRect.GetWidth() > clip.right)
	{
		srcRect.right -= (float)x + srcRect.GetWidth() - clip.right;
	}
	if ((float)y + srcRect.GetHeight() > clip.bottom)
	{
		srcRect.bottom -= (float)y + srcRect.GetHeight() - clip.bottom;
	}
	for (int sy = (int)srcRect.top; sy < (int)srcRect.bottom; sy++)
	{
		for (int sx = (int)srcRect.left; sx < (int)srcRect.right; sx++)
		{
			DrawPixel(in_buffer, x + sx - (int)srcRect.left, y + sy - (int)srcRect.top, s.GetPixel(sx, sy));
		}
	}
}

void Graphics::DrawSprite(int* in_buffer, int x, int y, const Surface& s, Color chroma)
{
	DrawSprite(in_buffer, x, y, s.GetRect(), s, chroma);
}

void Graphics::DrawSprite(int* in_buffer, int x, int y, Rect<float> srcRect, const Surface& s, Color chroma)
{
	DrawSprite(in_buffer, x, y, srcRect, Rect<float>(0.0f, (float)WinWidth, 0.0f, (float)WinHeight), s, chroma);
}

void Graphics::DrawSprite(int* in_buffer, int x, int y, Rect<float> srcRect, 
	const Rect<float> clip, const Surface& s, Color chroma)
{
	assert(srcRect.left >= 0);
	assert(srcRect.left <= s.GetWidth());
	assert(srcRect.top >= 0);
	assert(srcRect.bottom <= s.GetHeight());
	if ((float)x < clip.left)
	{
		srcRect.left += clip.left - (float)x;
		x = (int)clip.left;
	}
	if ((float)y < clip.top)
	{
		srcRect.top += clip.top - (float)y;
		y = (int)clip.top;
	}
	if ((float)x + srcRect.GetWidth() > clip.right)
	{
		srcRect.right -= (float)x + srcRect.GetWidth() - clip.right;
	}
	if ((float)y + srcRect.GetHeight() > clip.bottom)
	{
		srcRect.bottom -= (float)y + srcRect.GetHeight() - clip.bottom;
	}
	for (int sy = (int)srcRect.top; sy < (int)srcRect.bottom; sy++)
	{
		for (int sx = (int)srcRect.left; sx < (int)srcRect.right; sx++)
		{
			const Color srcPixel = s.GetPixel(sx, sy);
			if (srcPixel != chroma)
			{
				DrawPixel(in_buffer, x + sx - (int)srcRect.left, y + sy - (int)srcRect.top, srcPixel);
			}

		}
	}
}