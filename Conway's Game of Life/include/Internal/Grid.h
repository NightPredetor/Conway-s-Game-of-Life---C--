#pragma once

#include <vector>

// For generating grids.
class Grid
{
public:
	// Creates a grid of a given X and Y Size.
	static std::vector<struct Vector2> CreateGrid(int xSize, int ySize);
};