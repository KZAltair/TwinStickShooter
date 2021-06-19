#include "Animation.h"
#include "SpriteEffect.h"

Animation::Animation(float x, float y, float width, float height, int count, const Surface& s, float holdTime)
	:
	sprite(s),
	holdTime(holdTime)

{
	for (int i = 0; i < count; i++)
	{
		frames.emplace_back(x + i * width, x + (i + 1) * width, y, y + height);
	}
}

void Animation::Draw(int* in_buffer, Vec2<float> pos, Graphics& gfx)
{
	gfx.DrawSprite(in_buffer, (int)pos.x, (int)pos.y, frames[iCurFrame], sprite, SpriteEffect::AlphaBlend{ in_buffer });
}

void Animation::Draw(int* in_buffer, Vec2<float> pos, const Rect<float>& clip, Graphics& gfx)
{
	gfx.DrawSprite(in_buffer, (int)pos.x, (int)pos.y, frames[iCurFrame],
		clip, sprite, SpriteEffect::AlphaBlend{ in_buffer });
}

void Animation::Update(float dt)
{
	curFrameTime += dt;
	while (curFrameTime >= holdTime)
	{
		Advance();
		curFrameTime -= holdTime;
	}
}

void Animation::Advance()
{
	if (++iCurFrame >= frames.size())
	{
		iCurFrame = 0;
	}
}