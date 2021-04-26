#pragma once

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
	void DrawRectancle(int* Colors, int xMin, int xMax, int yMin, int yMax, unsigned char r, unsigned char g, unsigned char b);

private:
	int WinWidth;
	int WinHeight;
};