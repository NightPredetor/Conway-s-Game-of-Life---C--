#include "Cell.h"
#include "CellManager.h"

Cell::Cell(Vector2 position, CellStateEnum newCellState, CellManager<Cell>* cellManagerRef) : position(position), cellState(newCellState), cellManager(cellManagerRef)
{
	updatedCellState = CellStateEnum::NONE;
}

void Cell::CalculateNewState()
{
	// Contains no logic as the base cell will always remain empty.
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

CellManager<Cell>* Cell::getCellManager()
{
	return cellManager;
}

void Cell::setUpdatedCellState(const CellStateEnum newCellState) { updatedCellState = newCellState; }
CellStateEnum Cell::getCellState() const { return cellState; }