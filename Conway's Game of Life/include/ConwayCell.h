#pragma once

#include <Cell.h>

class ConwayCell : public Cell
{
public:
	ConwayCell(Vector2 position, CellStateEnum newCellState, CellManager<Cell>* cellManagerRef);

	void CalculateNewState() override;
};