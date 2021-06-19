#include "Surface.h"
#include <assert.h>
#include <fstream>
#include "WinLib.h"

#include <algorithm>

namespace Gdiplus
{
	using std::min;
	using std::max;
}

#include <gdiplus.h>

namespace gdi = Gdiplus;

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixels(new Color[width * height])
{
}

Surface::Surface(std::wstring& fileName)
{
#if 0
	std::ifstream file(fileName, std::ios::binary);
	assert(file);
	assert(file.is_open() == true);

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);

	const bool is32b = bmInfoHeader.biBitCount == 32;

	width = bmInfoHeader.biWidth;

	int yStart;
	int yEnd;
	int dy;
	if (bmInfoHeader.biHeight < 0)
	{
		height = -bmInfoHeader.biHeight;
		yStart = 0;
		yEnd = height;
		dy = 1;
	}
	else
	{
		height = bmInfoHeader.biHeight;
		yStart = height - 1;
		yEnd = -1;
		dy = -1;
	}


	pPixels = new Color[width * height];

	file.seekg(bmFileHeader.bfOffBits);

	//Padding is for 24-bit depth of image only
	const int padding = (4 - (width * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += dy)
	{
		for (int x = 0; x < width; x++)
		{
			PutPixel(x, y, Color(file.get(), file.get(), file.get()));
			if (is32b)
			{
				file.seekg(1, std::ios::cur);
			}
		}
		if (!is32b)
		{
			file.seekg(padding, std::ios::cur);
		}

	}
#else
	gdi::Bitmap bitmap(fileName.c_str());

	width = bitmap.GetWidth();
	height = bitmap.GetHeight();

	pPixels = new Color[width * height];

	const bool isAlpha = gdi::IsAlphaPixelFormat(bitmap.GetPixelFormat()) == TRUE;

	gdi::Color pixel;
	

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			bitmap.GetPixel(x, y, &pixel);
			if (isAlpha)
			{
				PutPixel(x, y, Color(pixel.GetA(), pixel.GetR(), pixel.GetG(), pixel.GetB()));
			}
			else
			{
				PutPixel(x, y, Color(pixel.GetR(), pixel.GetG(), pixel.GetB()));
			}
		}
	}

	if (isAlpha)
	{
		PremultiplyAlpha();
	}
#endif
}

Surface::Surface(const Surface& rhs)
	:
	Surface(rhs.width, rhs.height)
{
	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface& Surface::operator=(const Surface& rhs)
{
	width = rhs.width;
	height = rhs.height;

	delete[] pPixels;
	pPixels = new Color[width * height];

	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++)
	{
		pPixels[i] = rhs.pPixels[i];
	}
	return *this;
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

Rect<float> Surface::GetRect() const
{
	return Rect<float>(0.0f, (float)width, 0.0f, (float)height);
}

void Surface::PremultiplyAlpha()
{
	const int nPixels = GetWidth() * GetHeight();

	for (int i = 0; i < nPixels; i++)
	{
		auto pix = pPixels[i];
		const int alpha = pix.GetA();
		//premultiply alpha
		pix.SetR((pix.GetR() * alpha) / 256);
		pix.SetG((pix.GetG() * alpha) / 256);
		pix.SetB((pix.GetB() * alpha) / 256);

		pPixels[i] = pix;
	}
}
