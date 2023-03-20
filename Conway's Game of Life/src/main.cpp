#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Cell.h"
#include "CellManager.h"

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

void PrintFPS(sf::Clock& clock, sf::Time& timeSinceLastUpdate)
{
	sf::Time deltaTime = clock.restart();
	timeSinceLastUpdate += deltaTime;

	while (timeSinceLastUpdate > UPDATE_INTERVAL)
	{
		timeSinceLastUpdate -= UPDATE_INTERVAL;
		std::cout << "FPS: " << static_cast<int>(1.0f / deltaTime.asSeconds()) << "\n";
	}
}

int main()
{
	// Set const variables.
	const int width = 40;
	const int length = 40;
	const int cellSize = 10;

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
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// Create window.
	sf::RenderWindow window(sf::VideoMode(960, 540), "Conway's Game of Life");

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
		DrawCells(&shapeList, &cellMap, &window);

		// FPS.
		PrintFPS(clock, timeSinceLastUpdate);

		// End the current frame.
		window.display();
	}

	return 0;
}