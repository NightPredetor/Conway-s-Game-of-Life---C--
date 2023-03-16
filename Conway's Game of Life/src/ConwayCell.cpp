#include "ConwayCell.h"

ConwayCell::ConwayCell(Vector2 position, CellStateEnum newCellState, CellManager<Cell>* cellManagerRef) : Cell(position, newCellState, cellManagerRef) { }

void ConwayCell::CalculateNewState()
{
	std::vector<Cell*> cellList = getCellManager()->GetNeigbourList(this);

	int aliveCellsCount = 0;
	const int maxCellsCount = getCellState() == CellStateEnum::Alive ? 4 : 3;

	for (Cell const* cell : cellList)
	{
		if (cell == nullptr) continue;

		if (cell->getCellState() == CellStateEnum::Alive)
		{
			aliveCellsCount++;
		}

		if (aliveCellsCount == maxCellsCount)
		{
			break;
		}
	}

	if (getCellState() == CellStateEnum::Alive)
	{
		if (aliveCellsCount <= 1 || aliveCellsCount >= 4)
		{
			setUpdatedCellState(CellStateEnum::Dead);
		}
		else if (aliveCellsCount == 2 || aliveCellsCount == 3)
		{
			setUpdatedCellState(CellStateEnum::Alive);
		}
	}
	else
	{
		if (aliveCellsCount == 3)
		{
			setUpdatedCellState(CellStateEnum::Alive);
		}
	}
}