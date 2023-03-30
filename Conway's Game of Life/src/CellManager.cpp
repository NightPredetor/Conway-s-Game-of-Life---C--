#include "CellManager.h"
#include "Cell.h"

#include <time.h>

// Public
CellManager::CellManager(const int width, const int height, const CellStateEnum defaultState)
{
	CreateCells(width, height, defaultState);
	SetupCellNeighbours();
}

void CellManager::UpdateCells() const
{
	for (const auto& data : cellDict)
	{
		data.second->CalculateNewState();
	}

	for (const auto& data : cellDict)
	{
		data.second->UpdateToNewState();
	}
}

std::vector<Cell*> CellManager::GetNeigbourList(const Cell* cell)
{
	// Edge Connecting -
	// In case a cell is at the edge of the grid,
	// this function loops to the other end of the grid to get the cell,
	// so the simulation can run without any dead end walls.
	auto getPosition = [=](const int x, const int y)
	{
		for (int i = 0; i < 3; i++)
		{
			Vector2 position;
			switch (i)
			{
				case 1:
					position = Vector2(0, cell->getPosition().Y + y);
					break;
				case 2:
					position = Vector2(cell->getPosition().X + x, 0);
					break;
				default:
					position = Vector2(cell->getPosition().X + x, cell->getPosition().Y + y);
					break;
			}

			if (cellDict.count(position))
			{
				return position;
			}
		}
	};

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
			Vector2 position = getPosition(x, y);

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

		cellDict[position] = new Cell(position, (CellStateEnum)enumValue);
	}
}

void CellManager::SetupCellNeighbours()
{
	for (const auto& data : cellDict)
	{
		data.second->SetupNeighboursList(this);
	}
}
