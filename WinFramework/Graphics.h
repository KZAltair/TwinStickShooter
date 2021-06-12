#pragma once
#include <stdint.h>
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
	void DrawRectancle(int* Colors, int xMin, int xMax, int yMin, int yMax, 
		unsigned char r, unsigned char g, unsigned char b);

	//Sprite drawing helper functions
	void DrawSpriteNonChroma(int* in_buffer, int x, int y, const Surface& s);
	void DrawSpriteNonChroma(int* in_buffer, int x, int y, Rect<float> srcRect, const Surface& s);
	void DrawSpriteNonChroma(int* in_buffer, int x, int y, Rect<float> srcRect, const Rect<float> clip, const Surface& s);
	void DrawSprite(int* in_buffer, int x, int y, const Surface& s, Color chroma = Colors::Magenta);
	void DrawSprite(int* in_buffer, int x, int y, Rect<float> srcRect, 
		const Surface& s, Color chroma = Colors::Magenta);
	void DrawSprite(int* in_buffer, int x, int y, Rect<float> srcRect, 
		const Rect<float> clip, const Surface& s, Color chroma = Colors::Magenta);
private:
	int WinWidth;
	int WinHeight;
};