#include "Internal/Vector2.h"

Vector2::Vector2() : X(0), Y(0) {}
Vector2::Vector2(float x, float y) : X(x), Y(y) {}

bool Vector2::operator<(const Vector2& vector) const
{
	return X < vector.X && Y < vector.Y;
}
