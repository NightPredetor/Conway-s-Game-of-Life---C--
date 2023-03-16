#pragma once

#include <vector>
#include "CellManager.h"
#include "Internal/Vector2.h"
#include "enums/CellStateEnum.h"

// A base empty cell class that occupies a position in a grid.
class Cell
{
public:
	explicit Cell(Vector2 position, CellStateEnum newCellState, CellManager<Cell>* cellManagerRef);
	virtual ~Cell() = default;

	virtual void CalculateNewState();
	virtual void UpdateToNewState();

	virtual void setPosition(const Vector2 newPosition);
	virtual Vector2 getPosition() const;

	virtual CellStateEnum getCellState() const;

protected:
	std::vector<Cell*> GetNeighboursList() const;
	CellManager<Cell>* getCellManager();

	virtual void setUpdatedCellState(const CellStateEnum newCellState);

private:
	Vector2 position;
	CellStateEnum cellState;
	CellStateEnum updatedCellState;
	CellManager<Cell>* cellManager;
};