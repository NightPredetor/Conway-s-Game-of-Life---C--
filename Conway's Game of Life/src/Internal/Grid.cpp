#include "Internal/Grid.h"

#include "Internal/Vector2.h"

std::vector<Vector2> Grid::CreateGrid(int xSize, int ySize)
{
	// Dict for storing positions.
	std::vector<Vector2> gridList;

	// Loop in X direction.
	for (int x = 0; x < xSize; x++)
	{
		// Loop in Y direction.
		for (int y = 0; y < ySize; y++)
		{
			// Create a position and add to dict.
			gridList.push_back(Vector2(x, y));
		}
	}

	return gridList;
}