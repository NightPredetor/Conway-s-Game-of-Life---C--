#include "Cell.h"
#include "CellManager.h"

Cell::Cell(Vector2 position, CellStateEnum newCellState) : position(position), cellState(newCellState)
{
	updatedCellState = CellStateEnum::Dead;
}

void Cell::CalculateNewState()
{
	int aliveCellsCount = 0;

	for (Cell const* cell : neighbourCellList)
	{
		if (cell == nullptr) continue;

		// Get the amount of alive cells.
		if (cell->getCellState() == CellStateEnum::Alive)
		{
			aliveCellsCount++;
		}

		// No cell can live if they have more than 4 cell.
		// So break out if alive cell count is 4.
		if (aliveCellsCount == 4)
		{
			break;
		}
	}

	if (getCellState() == CellStateEnum::Alive)
	{
		if (aliveCellsCount <= 1 || aliveCellsCount == 4)
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

void Cell::UpdateToNewState()
{
	cellState = updatedCellState;
}

void Cell::SetupNeighboursList(CellManager* cellManager)
{
	if (cellManager == nullptr) return;

	neighbourCellList = cellManager->GetNeigbourList(this);
}

Vector2 Cell::getPosition() const { return position; }

void Cell::setUpdatedCellState(const CellStateEnum newCellState) { updatedCellState = newCellState; }
CellStateEnum Cell::getCellState() const { return cellState; }