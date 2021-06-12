#pragma once
#include "Vec2.h"

template <typename T>
class Rect
{
public:
	Rect() = default;
	Rect(T left_in, T right_in, T top_in, T bottom_in)
		:
		left(left_in),
		right(right_in),
		top(top_in),
		bottom(bottom_in)
	{

	}
	Rect(const Vec2<T>& topLeft, const Vec2<T>& bottomRight)
		:
		Rect(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{

	}
	Rect(const Vec2<T>& topLeft, T width, T height)
		:
		RectF(topLeft, topLeft + Vec2<T>(width, height))
	{

	}
	static Rect FromCenter(const Vec2<T>& center, T halfWidth, T halfHeight)
	{
		const Vec2<T> half(halfWidth, halfHeight);
		return Rect(center - half, center + half);
	}
	bool IsOverlappingWith(const Rect<T>& other) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}
public:
	T left;
	T top;
	T right;
	T bottom;
};

