#pragma once

#include <map>
#include <vector>
#include "Internal/Grid.h"
#include "enums/CellStateEnum.h"

struct Vector2;

// Holds the data for all the cells.
template <typename T>
class CellManager
{
	static_assert(std::is_base_of<class Cell, T>::value, "T must be derived from Cell class.");

public:
	CellManager(const int xSize, const int ySize, const CellStateEnum cellStateEnum);
	~CellManager() = default;

	void UpdateCells() const;

	std::vector<T*> GetNeigbourList(const T* cell);
	std::map<Vector2, T*> getCellDict() const;

private:
	std::map<Vector2, T*> cellDict;

	void CreateCells(const int xSize, const int ySize, const CellStateEnum cellStateEnum);
};

// ----------------- Inline Declaration Start -----------------

// Public
template <typename T>
inline CellManager<T>::CellManager(const int xSize, const int ySize, const CellStateEnum cellStateEnum)
{
	CreateCells(xSize, ySize, cellStateEnum);
}

template <typename T>
void CellManager<T>::UpdateCells() const
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

template <typename T>
std::vector<T*> CellManager<T>::GetNeigbourList(const T* cell)
{
	// Create array for holding cells.
	std::vector<T*> neighbourList;

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

template <typename T>
std::map<Vector2, T*> CellManager<T>::getCellDict() const
{
	return cellDict;
}

// Private
template <typename T>
void CellManager<T>::CreateCells(const int xSize, const int ySize, const CellStateEnum cellStateEnum)
{
	std::vector<Vector2> gridList = Grid::CreateGrid(xSize, ySize);

	for (Vector2 position : gridList)
	{
		if (cellDict.count(position)) { continue; }

		//cellDict[position] = new T(position, cellStateEnum, this);
	}
}

// ----------------- Inline Declaration End -----------------