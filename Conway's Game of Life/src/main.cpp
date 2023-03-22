#include <SFML/Graphics.hpp>
#include <iostream>

#include "Cell.h"
#include "CellManager.h"
#include "Internal/FPS.h"

const sf::Time UPDATE_INTERVAL = sf::seconds(1.0f / 60.0f); // 60 FPS
const sf::Color BG_COLOR(150, 150, 150); // Set background color.

void SetupCellShapes(std::vector<sf::RectangleShape>& shapeList, std::map<Vector2, Cell*> const* cellMap, const int width, const int length, const int cellSize)
{
	shapeList = std::vector<sf::RectangleShape>(width * length);

	int i = 0;
	for (auto it = cellMap->begin(); it != cellMap->end(); ++it)
	{
		shapeList[i].setSize(sf::Vector2f(cellSize, cellSize));
		shapeList[i].setPosition(sf::Vector2f(it->first.X * cellSize, it->first.Y * cellSize));

		shapeList[i].setFillColor(sf::Color(250, 250, 250));
		shapeList[i].setOutlineColor(sf::Color::Black);

		shapeList[i].setOutlineThickness(1);

		i++;
	}
}

void DrawCells(std::vector<sf::RectangleShape> const* shapeList, std::map<Vector2, Cell*> const* cellMap, sf::RenderWindow* window)
{
	int i = 0;
	for (auto it = cellMap->begin(); it != cellMap->end(); ++it)
	{
		if (it->second->getCellState() == CellStateEnum::Alive)
		{
			window->draw(shapeList->at(i));
		}

		i++;
	}
}

int main()
{
	// Set const variables.
	const int width = 100;
	const int length = 100;
	const int cellSize = 5;

	// Create a background for the cell area.
	sf::RectangleShape frameShape(sf::Vector2f(width * cellSize, length * cellSize));
	frameShape.setFillColor(BG_COLOR);

	// Create CellManager.
	auto const cellManager = CellManager(width, length, CellStateEnum::NONE);

	// Get cell dictionary.
	std::map<Vector2, Cell*> const cellMap = cellManager.getCellDict();
	if (cellMap.empty())
	{
		std::cout << "No cells found!";
		return -1;
	}

	// Setup the shape list.
	std::vector<sf::RectangleShape> shapeList;
	SetupCellShapes(shapeList, &cellMap, width, length, cellSize);

	// Setup clock for FPS.
	FPS fpsHandler;

	// Create window.
	sf::RenderWindow window(sf::VideoMode(960, 540), "Conway's Game of Life");
	window.setFramerateLimit(60);

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

		// Clear the window with black color.
		window.clear(sf::Color::Black);

		// Render cell area.
		window.draw(frameShape);

		// Cell logic.
		cellManager.UpdateCells();
		DrawCells(&shapeList, &cellMap, &window);

		// FPS.
		fpsHandler.Update();
		window.draw(fpsHandler.getFpsText());

		// End the current frame.
		window.display();
	}

	return 0;
}