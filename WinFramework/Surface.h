#pragma once
#include "Colors.h"
#include "Rect.h"
#include <string>
/*
This class prepares a buffer and loads data into newly created buffer
*/

class Surface
{
public:
	Surface(int width, int height);
	Surface(std::string fileName);
	Surface(const Surface&);
	Surface& operator=(const Surface&);
	~Surface();
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	Rect<float> GetRect() const;
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};