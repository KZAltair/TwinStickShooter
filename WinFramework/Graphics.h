#pragma once
#include <stdint.h>
#include <assert.h>
#include "Surface.h"
#include "Rect.h"

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

class Graphics
{
public:
	Graphics(int WindowWidth, int WindowHeight);
	Graphics(const Graphics&) = delete;
	Graphics operator=(const Graphics&) = delete;
	~Graphics();

	void FillScreenFast(int* Colors, unsigned char r, unsigned char g, unsigned char b);
	void ClearScreenSuperFast(int* Colors);
	void DrawPixel(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b);
	void DrawPixel(int* in_buffer, int x, int y, Color c);
	Color GetPixel(int* in_buffer, int x, int y);
	void DrawRectancle(int* Colors, int xMin, int xMax, int yMin, int yMax, 
		unsigned char r, unsigned char g, unsigned char b);

	//Sprite drawing helper functions
	template <typename E>
	void DrawSprite(int* in_buffer, int x, int y, const Surface& s, E effect)
	{
		DrawSprite(in_buffer, x, y, s.GetRect(), s, effect);
	}
	template <typename E>
	void DrawSprite(int* in_buffer, int x, int y, Rect<float> srcRect, const Surface& s, E effect)
	{
		DrawSprite(in_buffer, x, y, srcRect, Rect<float>(0.0f, (float)WinWidth, 0.0f, (float)WinHeight), s, effect);
	}
	template <typename E>
	void DrawSprite(int* in_buffer, int x, int y, Rect<float> srcRect,
		const Rect<float> clip, const Surface& s, E effect)
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
				effect(
					s.GetPixel(sx, sy),
					x + sx - (int)srcRect.left,
					y + sy - (int)srcRect.top,
					*this
				);
			}
		}
	}
private:
	int WinWidth;
	int WinHeight;
};