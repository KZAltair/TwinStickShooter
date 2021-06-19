#pragma once
#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma(int* buffer, Color c)
			:
			in_buffer(buffer),
			chroma(c)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.DrawPixel(in_buffer, xDest, yDest, cSrc);
			}
		}
	private:
		Color chroma;
		int* in_buffer = nullptr;
	};

	class AlphaBlend
	{
	public:
		AlphaBlend(int* buffer)
			:
			in_buffer(buffer)
		{}
		void operator()(Color src, int xDest, int yDest, Graphics& gfx) const
		{
			//pre-exract Alpha from source
			const int cAlpha = 255 - src.GetA();
			const Color dst = gfx.GetPixel(in_buffer, xDest, yDest);

			if (cAlpha != 255)
			{
				const int rb = (((dst.dword & 0xFF00FFu) * cAlpha) >> 8) & 0xFF00FFu;
				const int g = (((dst.dword & 0x00FF00u) * cAlpha) >> 8) & 0x00FF00u;
				gfx.DrawPixel(in_buffer, xDest, yDest, rb + g + src.dword);
			}
		}
	private:
		int* in_buffer = nullptr;
	};

}