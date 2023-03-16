#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "Cell.h"
#include "CellManager.h"

int main()
{
	const int width = 50;
	const int length = 50;
	const int cellSize = 10;
	const sf::Color bgColor(150, 150, 150);

	std::vector<sf::RectangleShape> shapeList(width * length);
	auto const cellManager = CellManager(width, length, CellStateEnum::NONE);

	std::map<Vector2, Cell*> const cellMap = cellManager.getCellDict();
	if (cellMap.empty())
	{
		std::cout << "No cells found!";
	}

	int i = 0;
	for (auto it = cellMap.begin(); it != cellMap.end(); ++it)
	{
		shapeList[i].setSize(sf::Vector2f(cellSize, cellSize));
		shapeList[i].setPosition(sf::Vector2f(it->first.X * cellSize, it->first.Y * cellSize));

		shapeList[i].setOutlineColor(sf::Color::Black);

		i++;
	}

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time updateInterval = sf::seconds(1.0f / 60.0f); // 60 FPS

	sf::RenderWindow window(sf::VideoMode(960, 540), "Conway's Game of Life");

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

		// clear the window with black color
		window.clear(bgColor);

		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;
		while (timeSinceLastUpdate > updateInterval)
		{
			timeSinceLastUpdate -= updateInterval;
			std::cout << "FPS: " << static_cast<int>(1.0f / deltaTime.asSeconds()) << "\n";
		}

		cellManager.UpdateCells();

		i = 0;
		for (auto it = cellMap.begin(); it != cellMap.end(); ++it)
		{
			if (it->second->getCellState() == CellStateEnum::Alive)
			{
				shapeList[i].setFillColor(sf::Color(250, 250, 250));
				shapeList[i].setOutlineThickness(1);
			}
			else
			{
				shapeList[i].setFillColor(bgColor);
				shapeList[i].setOutlineThickness(0);
			}

			window.draw(shapeList[i]);

			i++;
		}

		// end the current frame
		window.display();
	}

	return 0;
}