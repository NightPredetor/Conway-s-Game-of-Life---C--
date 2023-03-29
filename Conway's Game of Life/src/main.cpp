#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.h"
#include "CellManager.h"
#include "Internal/FPS.h"

void SetupCellShapes(sf::VertexArray& vertexArray, std::map<Vector2, Cell*> const* cellMap, const int cellSize)
{
	// Setup the vertex buffer for drawing all the cells.
	vertexArray = sf::VertexArray(sf::Quads, cellMap->size() * 4);

	int i = 0;
	sf::Vector2f point;
	for (auto it = cellMap->begin(); it != cellMap->end(); ++it)
	{
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

		i += 4;
	}
}

sf::VertexArray DrawCells(sf::VertexArray const* vertexArray, std::map<Vector2, Cell*> const* cellMap)
{
	int alive = 0;
	for (auto it = cellMap->begin(); it != cellMap->end(); ++it)
	{
		if (it->second->getCellState() == CellStateEnum::Alive)
		{
			alive++;
		}
	}

	// Setup the vertex buffer for drawing all the alive cells.
	sf::VertexArray aliveVertexArray(sf::Quads, alive * 4);

	int vertexPoint = 0;
	int aliveVertexPoint = 0;
	for (auto it = cellMap->begin(); it != cellMap->end(); ++it)
	{		
		if (it->second->getCellState() == CellStateEnum::Alive)
		{
			for (int i = 0; i < 4; i++)
			{
				aliveVertexArray[aliveVertexPoint + i] = (*vertexArray)[vertexPoint + i];
			}

			aliveVertexPoint += 4;
		}

		vertexPoint += 4;
	}

	return aliveVertexArray;
}

int main()
{
	// Set const variables.
	const int WIDTH = 200;
	const int LENGTH = 200;
	const int CELL_SIZE = 5;
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
		window.draw(DrawCells(&vertexArray, &cellMap));

		// FPS.
		fpsHandler.Update();
		window.draw(fpsHandler.getFpsText());

		// End the current frame.
		window.display();
	}

	return 0;
}