#include "SimulationManager.h"
#include "Internal/Vector2.h"

#include <iostream>
#include <math.h>

// ----- Public -----

SimulationManager::SimulationManager()
{
	totalWidth = WIDTH * CELL_SIZE;
	totalLength = LENGTH * CELL_SIZE;

	// Get cell dictionary.
	cellMap = cellManager.getCellDict();
	if (cellMap.empty())
	{
		std::cout << "No cells found!";
	}

	// Setup vertex buffer.
	SetupVertexBuffer();

	// Cell Background rect.
	cellBackground.setFillColor(BG_COLOR);
}

void SimulationManager::ToggleCellState(const Vector2 cellPos)
{
	if (cellMap.count(cellPos))
	{
		if (cellMap[cellPos]->getCellState() == CellStateEnum::Alive)
		{
			cellMap[cellPos]->setCellState(CellStateEnum::Dead);
		}
		else
		{
			cellMap[cellPos]->setCellState(CellStateEnum::Alive);
		}
	}
}

void SimulationManager::TogglePause()
{
	pauseSimulation = !pauseSimulation;
}

void SimulationManager::ToggleClearBoard()
{
	clearBoard = !clearBoard;
}

void SimulationManager::PerformStep()
{
	step = true;
	pauseSimulation = false;
}

void SimulationManager::OnStepTrue()
{
	if (step == true)
	{
		step = false;
		pauseSimulation = true;
	}
}

void SimulationManager::OnRestart()
{
	generationElapsed = 0;
	step = clearBoard;
	pauseSimulation = clearBoard;

	cellManager = CellManager(WIDTH, LENGTH, clearBoard ? CellStateEnum::Dead : CellStateEnum::NONE);
	cellMap = cellManager.getCellDict();
}

void SimulationManager::UpdateCells()
{
	generationElapsed += 1;
	cellManager.UpdateCells();
}

int SimulationManager::getWidth() const { return WIDTH; }

int SimulationManager::getTotalWidth() const { return totalWidth; }

int SimulationManager::getLength() const { return LENGTH; }

int SimulationManager::getTotalLength() const { return totalLength; }

int SimulationManager::getCellSize() const { return CELL_SIZE; }

int SimulationManager::getUiSpace() const { return UI_SPACE; }

sf::Color SimulationManager::getBgColor() const { return BG_COLOR; }

sf::RectangleShape SimulationManager::getCellBg() const { return cellBackground; }

bool SimulationManager::getPauseSimulation() const { return pauseSimulation; }

bool SimulationManager::getClearBoard() const { return clearBoard; }

int SimulationManager::getGenerationsElapsed() const { return generationElapsed; }

// ----- Private -----

void SimulationManager::SetupVertexBuffer()
{
	// Create colors.
	const sf::Color BORDER_COLOR(20, 20, 20);
	const sf::Color CELL_COLOR(230, 230, 230);

	// Calculate border size.
	const int BORDER_SIZE = roundf(CELL_SIZE * 0.1f);

	// Setup the vertex buffer for drawing all the cells.
	vertexArray = sf::VertexArray(sf::Quads, cellMap.size() * 8);

	int i = 0;
	sf::Vector2f point;
	for (auto it = cellMap.begin(); it != cellMap.end(); ++it)
	{
		// ------------ Draw Cell's Border ------------
		// Top left point.
		point = sf::Vector2f(it->first.X * CELL_SIZE, it->first.Y * CELL_SIZE);
		vertexArray[i].position = point;

		// Top right point.
		point = sf::Vector2f(it->first.X * CELL_SIZE + CELL_SIZE, it->first.Y * CELL_SIZE);
		vertexArray[i + 1].position = point;

		// Bottom right point.
		point = sf::Vector2f(it->first.X * CELL_SIZE + CELL_SIZE, it->first.Y * CELL_SIZE + CELL_SIZE);
		vertexArray[i + 2].position = point;

		// Bottom left point.
		point = sf::Vector2f(it->first.X * CELL_SIZE, it->first.Y * CELL_SIZE + CELL_SIZE);
		vertexArray[i + 3].position = point;

		// ------------ Draw Cell ------------
		point = sf::Vector2f(it->first.X * CELL_SIZE + BORDER_SIZE, it->first.Y * CELL_SIZE + BORDER_SIZE);
		vertexArray[i + 4].position = point;

		// Top right point.
		point = sf::Vector2f(it->first.X * CELL_SIZE + CELL_SIZE - BORDER_SIZE, it->first.Y * CELL_SIZE + BORDER_SIZE);
		vertexArray[i + 5].position = point;

		// Bottom right point.
		point = sf::Vector2f(it->first.X * CELL_SIZE + CELL_SIZE - BORDER_SIZE, it->first.Y * CELL_SIZE + CELL_SIZE - BORDER_SIZE);
		vertexArray[i + 6].position = point;

		// Bottom left point.
		point = sf::Vector2f(it->first.X * CELL_SIZE + BORDER_SIZE, it->first.Y * CELL_SIZE + CELL_SIZE - BORDER_SIZE);
		vertexArray[i + 7].position = point;

		// Color the first 4 cells black, and the remaining 4 cells white.
		for (int j = i; j < i + 8; j++)
		{
			vertexArray[j].color = j < i + 4 ? BORDER_COLOR : CELL_COLOR;
		}

		i += 8;
	}
}

sf::VertexArray SimulationManager::GetCellsForDraw()
{
	// Setup the vertex buffer for drawing all the alive cells.
	sf::VertexArray aliveVertexArray(sf::Quads);

	int vertexPoint = 0;
	for (const auto& data : cellMap)
	{
		if (data.second->getCellState() == CellStateEnum::Alive)
		{
			for (int i = 0; i < 8; i++)
			{
				aliveVertexArray.append(vertexArray[vertexPoint + i]);
			}
		}

		vertexPoint += 8;
	}

	return aliveVertexArray;
}