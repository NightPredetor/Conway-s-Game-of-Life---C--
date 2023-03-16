#pragma once

// Holds a 2D vector.
struct Vector2
{
	float X;
	float Y;

	Vector2();
	Vector2(float x, float y);
	bool operator<(const Vector2& vector) const;
};