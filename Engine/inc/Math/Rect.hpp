#pragma once
template <typename T = int>
class Rect
{
public:
	Rect() :width(0), height(0), left(0), top(0)
	{
	}
	Rect(T width, T height) :left(0), top(0), width(width), height(height)
	{
	}
	Rect(T left, T top, T width, T height) :left(left), top(top), width(width), height(height)
	{
	}
	Rect(const Rect& rect) :left(rect.left), top(rect.top), width(rect.width), height(rect.height)
	{
	}
public:
	T width, height, left, top;
};