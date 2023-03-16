#include "Cell.h"
#include "CellManager.h"

Cell::Cell(Vector2 position, CellStateEnum newCellState, CellManager* cellManagerRef) : position(position), cellState(newCellState), cellManager(cellManagerRef)
{
	updatedCellState = CellStateEnum::Dead;
}

void Cell::CalculateNewState()
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

void Cell::UpdateToNewState()
{
	cellState = updatedCellState;
}

void Cell::setPosition(const Vector2 newPosition) { position = newPosition; }
Vector2 Cell::getPosition() const { return position; }

std::vector<Cell*> Cell::GetNeighboursList() const
{
	if (cellManager == nullptr) return std::vector<Cell*>(0);

	return cellManager->GetNeigbourList(this);
}

CellManager* Cell::getCellManager()
{
	return cellManager;
}

void Cell::setUpdatedCellState(const CellStateEnum newCellState) { updatedCellState = newCellState; }
CellStateEnum Cell::getCellState() const { return cellState; }