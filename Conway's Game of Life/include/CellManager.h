#pragma once

#include <map>
#include <vector>

#include "Internal/Grid.h"
#include "enums/CellStateEnum.h"

class Cell;
struct Vector2;

// Holds the data for all the cells.
class CellManager
{
public:
	CellManager(const int width, const int height, const CellStateEnum defaultState);
	~CellManager() = default;

	void UpdateCells() const;

	std::vector<Cell*> GetNeigbourList(const Cell* cell);
	std::map<Vector2, Cell*> getCellDict() const;

private:
	std::map<Vector2, Cell*> cellDict;

	void CreateCells(const int width, const int height, const CellStateEnum defaultState);
	void SetupCellNeighbours() const;
};