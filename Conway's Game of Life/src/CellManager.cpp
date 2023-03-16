#include "CellManager.h"
#include "Cell.h"

#include <time.h>

// Public
CellManager::CellManager(const int width, const int height, const CellStateEnum defaultState)
{
	CreateCells(width, height, defaultState);
}

void CellManager::UpdateCells() const
{
	for (auto cellData : cellDict)
	{
		cellData.second->CalculateNewState();
	}

	for (auto cellData : cellDict)
	{
		cellData.second->UpdateToNewState();
	}
}

std::vector<Cell*> CellManager::GetNeigbourList(const Cell* cell)
{
	// Create array for holding cells.
	std::vector<Cell*> neighbourList;

	// Loop 3 times in X.
	for (int x = -1; x <= 1; x++)
	{
		// Loop 3 times in Y.
		for (int y = -1; y <= 1; y++)
		{
			// Ignore the mid cell.
			if (x == 0 && y == 0) { continue; }

			// This will give us all the 8 neighboring cells.
			auto position = Vector2(cell->getPosition().X + x, cell->getPosition().Y + y);
			if (cellDict.count(position))
			{
				neighbourList.push_back(cellDict[position]);
			}
		}
	}

	return neighbourList;
}

std::map<Vector2, Cell*> CellManager::getCellDict() const
{
	return cellDict;
}

// Private
void CellManager::CreateCells(const int width, const int height, const CellStateEnum defaultState)
{
	srand(time(NULL));
	auto enumValue = (int)defaultState;

	std::vector<Vector2> gridList = Grid::CreateGrid(width, height);

	for (Vector2 position : gridList)
	{
		if (cellDict.count(position)) { continue; }

		if (defaultState == CellStateEnum::NONE)
		{
			enumValue = rand() % 3 + 1;
		}

		cellDict[position] = new Cell(position, (CellStateEnum)enumValue, this);
	}
}