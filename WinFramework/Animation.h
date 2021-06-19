#pragma once

#include "Surface.h"
#include "Graphics.h"
#include <vector>

class Animation
{
public:
	Animation(float x, float y, float width, float height, int count, const Surface& s, float holdTime);
	void Draw(int* in_buffer, Vec2<float> pos, Graphics& gfx);
	void Draw(int* in_buffer, Vec2<float> pos, const Rect<float>& clip, Graphics& gfx);
	void Update(float dt);
private:
	void Advance();
private:
	const Surface& sprite;
	std::vector<Rect<float>> frames;
	int iCurFrame = 0;
	float holdTime = 0.0f;
	float curFrameTime = 0.0f;
};