#include "Internal/Vector2.h"

Vector2::Vector2() : X(0), Y(0) {}
Vector2::Vector2(float x, float y) : X(x), Y(y) {}

bool Vector2::operator<(const Vector2& vector) const
{
	if (X < vector.X) 
	{
		return true;
	}
	else if (X == vector.X) 
	{
		return Y < vector.Y;
	}
	else 
	{
		return false;
	}
}
