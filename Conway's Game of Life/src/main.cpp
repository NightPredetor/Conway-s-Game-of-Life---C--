#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "Cell.h"
#include "CellManager.h"
#include "Internal/FPS.h"

void SetupCellShapes(sf::VertexArray& vertexArray, std::map<Vector2, Cell*> const* cellMap, const int cellSize)
{
	// Setup the vertex buffer for drawing all the cells.
	vertexArray = sf::VertexArray(sf::Quads, cellMap->size() * 8);

	int i = 0;
	sf::Vector2f point;

	// Calculate border size.
	const int BORDER_SIZE = roundf(cellSize * 0.05f);

	for (auto it = cellMap->begin(); it != cellMap->end(); ++it)
	{
		// ------------ Draw Cell's Border ------------
		// Top left point.
		point = sf::Vector2f(it->first.X * cellSize, it->first.Y * cellSize);
		vertexArray[i].position = point;

		// Top right point.
		point = sf::Vector2f(it->first.X * cellSize + cellSize, it->first.Y * cellSize);
		vertexArray[i + 1].position = point;

		// Bottom right point.
		point = sf::Vector2f(it->first.X * cellSize + cellSize, it->first.Y * cellSize + cellSize);
		vertexArray[i + 2].position = point;

		// Bottom left point.
		point = sf::Vector2f(it->first.X * cellSize, it->first.Y * cellSize + cellSize);
		vertexArray[i + 3].position = point;

		// ------------ Draw Cell ------------
		point = sf::Vector2f(it->first.X * cellSize + BORDER_SIZE, it->first.Y * cellSize + BORDER_SIZE);
		vertexArray[i + 4].position = point;

		// Top right point.
		point = sf::Vector2f(it->first.X * cellSize + cellSize - BORDER_SIZE, it->first.Y * cellSize + BORDER_SIZE);
		vertexArray[i + 5].position = point;

		// Bottom right point.
		point = sf::Vector2f(it->first.X * cellSize + cellSize - BORDER_SIZE, it->first.Y * cellSize + cellSize - BORDER_SIZE);
		vertexArray[i + 6].position = point;

		// Bottom left point.
		point = sf::Vector2f(it->first.X * cellSize + BORDER_SIZE, it->first.Y * cellSize + cellSize - BORDER_SIZE);
		vertexArray[i + 7].position = point;

		// Color the first 4 cells black, and the remaining 4 cells white.
		for (int j = i; j < i + 8; j++)
		{
			vertexArray[j].color = j < i + 4 ? sf::Color::Black : sf::Color::White;
		}

		i += 8;
	}
}

sf::VertexArray GetCellsForDraw(sf::VertexArray const* vertexArray, std::map<Vector2, Cell*> const* cellMap)
{
	// Setup the vertex buffer for drawing all the alive cells.
	sf::VertexArray aliveVertexArray(sf::Quads);

	int vertexPoint = 0;
	for (const auto& data : *cellMap)
	{
		if (data.second->getCellState() == CellStateEnum::Alive)
		{
			for (int i = 0; i < 8; i++)
			{
				aliveVertexArray.append((*vertexArray)[vertexPoint + i]);
			}
		}

		vertexPoint += 8;
	}

	return aliveVertexArray;
}

int main()
{
	// Set const variables.
	const int WIDTH = 100;
	const int LENGTH = 100;
	const int CELL_SIZE = 10;
	const sf::Color BG_COLOR(150, 150, 150);

	// Create CellManager.
	auto const cellManager = CellManager(WIDTH, LENGTH, CellStateEnum::NONE);

	// Get cell dictionary.
	std::map<Vector2, Cell*> const cellMap = cellManager.getCellDict();
	if (cellMap.empty())
	{
		std::cout << "No cells found!";
		return -1;
	}

	// Setup vertex buffer.
	sf::VertexArray vertexArray;
	SetupCellShapes(vertexArray, &cellMap, CELL_SIZE);

	// Setup clock for FPS.
	FPS fpsHandler;
	fpsHandler.SetFpsTextPosition(0, 0);

	// Create window.
	sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, LENGTH * CELL_SIZE), "Conway's Game of Life");
	window.setFramerateLimit(60);
	window.hasFocus();

	// SFML loop.
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Clear the window with BG color.
		window.clear(BG_COLOR);

		// Cell logic.
		cellManager.UpdateCells();
		window.draw(GetCellsForDraw(&vertexArray, &cellMap));

		// FPS.
		fpsHandler.Update();
		window.draw(fpsHandler.getFpsText());

		// End the current frame.
		window.display();
	}

	return 0;
}