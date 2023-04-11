#pragma once

#include <SFML/Graphics.hpp>

#include "Cell.h"
#include "CellManager.h"

class SimulationManager
{
public:
	SimulationManager();

	sf::VertexArray GetCellsForDraw();
	void ToggleCellState(const class Vector2 cellPos);
	void TogglePause();
	void ToggleClearBoard();
	void PerformStep();
	void OnStepTrue();
	void OnRestart();
	void UpdateCells();

	// Const variables getter.
	int getWidth() const;
	int getTotalWidth() const;

	int getLength() const;
	int getTotalLength() const;

	int getCellSize() const;
	int getUiSpace() const;
	sf::Color getBgColor() const;
	sf::RectangleShape getCellBg() const;

	// Getters.
	bool getPauseSimulation() const;
	bool getClearBoard() const;
	int getGenerationsElapsed() const;

private:
	// Set const variables.
	const int WIDTH = 100;
	const int LENGTH = 100;
	const int CELL_SIZE = 10;
	const int UI_SPACE = 200;
	const sf::Color BG_COLOR = sf::Color(150, 150, 150);

	int totalWidth;
	int totalLength;

	bool step = false;
	bool clearBoard = false;
	bool pauseSimulation = false;
	int generationElapsed = 0;

	CellManager cellManager = CellManager(WIDTH, LENGTH, CellStateEnum::NONE);
	std::map<Vector2, class Cell*> cellMap;

	sf::VertexArray vertexArray;
	sf::RectangleShape cellBackground = sf::RectangleShape(sf::Vector2f(WIDTH* CELL_SIZE, LENGTH* CELL_SIZE));

	void SetupVertexBuffer();
};