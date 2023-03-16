#include <SFML/Graphics.hpp>
#include <CellManager.h>
#include <ConwayCell.h>
#include <iostream>

int main()
{
	CellManager<ConwayCell> cellManager(10, 10, CellStateEnum::Alive);

	sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");

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
		window.clear(sf::Color::Black);

		cellManager.UpdateCells();

		std::map<Vector2, ConwayCell*> cellMap = cellManager.getCellDict();

		if (cellMap.empty())
		{
			std::cout << "WTF!";
		}

		for (auto it = cellMap.begin(); it != cellMap.end(); ++it)
		{
			//std::cout << it->first << ", " << it->second;
			sf::RectangleShape rectangle(sf::Vector2f(it->first.X + 50, it->first.Y + 50));
			rectangle.setSize(sf::Vector2f(50.f, 50.f));

			if (it->second->getCellState() == CellStateEnum::Alive)
			{
				rectangle.setFillColor(sf::Color(250, 150, 100));
			}
			else
			{
				rectangle.setFillColor(sf::Color(250, 250, 250));
			}

			window.draw(rectangle);
		}

		// end the current frame
		window.display();
	}

	return 0;
}