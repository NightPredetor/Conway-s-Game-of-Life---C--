#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "Cell.h"
#include "CellManager.h"
#include "Internal/FPS.h"
#include "ButtonManager.h"

void SetupCellShapes(sf::VertexArray& vertexArray, std::map<Vector2, Cell*> const* cellMap, const int cellSize)
{
	// Create colors.
	const sf::Color BORDER_COLOR(20, 20, 20);
	const sf::Color CELL_COLOR(230, 230, 230);

	// Calculate border size.
	const int BORDER_SIZE = roundf(cellSize * 0.1f);

	// Setup the vertex buffer for drawing all the cells.
	vertexArray = sf::VertexArray(sf::Quads, cellMap->size() * 8);

	int i = 0;
	sf::Vector2f point;
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
			vertexArray[j].color = j < i + 4 ? BORDER_COLOR : CELL_COLOR;
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
	const int UI_SPACE = 200;
	const sf::Color BG_COLOR(150, 150, 150);

	bool step = false;
	bool clearBoard = false;
	bool pauseSimulation = false;
	int generationElapsed = 0;

	// Create CellManager.
	auto cellManager = CellManager(WIDTH, LENGTH, CellStateEnum::NONE);

	// Get cell dictionary.
	std::map<Vector2, Cell*> cellMap = cellManager.getCellDict();
	if (cellMap.empty())
	{
		std::cout << "No cells found!";
		return -1;
	}

	// Setup vertex buffer.
	sf::VertexArray vertexArray;
	SetupCellShapes(vertexArray, &cellMap, CELL_SIZE);

	// Cell Background rect.
	sf::RectangleShape cellBackground(sf::Vector2f(WIDTH * CELL_SIZE, LENGTH * CELL_SIZE));
	cellBackground.setFillColor(BG_COLOR);

	// Setup clock for FPS.
	FPS fpsHandler;
	fpsHandler.SetFpsTextPosition(WIDTH * CELL_SIZE + 60, 10);

	ButtonManager buttonManager(WIDTH, CELL_SIZE);

	// Setup pause button.
	sf::RectangleShape pauseBtn;
	sf::Text pauseLabel;
	buttonManager.SetupPauseButton(pauseBtn, pauseLabel);

	// Setup step button.
	sf::RectangleShape stepBtn;
	sf::Text stepLabel;
	buttonManager.SetupStepButton(stepBtn, stepLabel);

	// Setup restart button.
	sf::RectangleShape restartBtn;
	sf::Text restartLabel;
	buttonManager.SetupRestartButton(restartBtn, restartLabel);

	// Setup clear button.
	sf::RectangleShape clearCheckboxBtn;
	sf::Text clearCheckboxLabel;
	buttonManager.SetupClearButton(clearCheckboxBtn, clearCheckboxLabel);

	// Create generation label.
	sf::Text generationLabel;
	buttonManager.SetupGenerationLabel(generationLabel);

	// Create window.
	sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE + UI_SPACE, LENGTH * CELL_SIZE), "Conway's Game of Life", sf::Style::Close);
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
			else if (event.type == sf::Event::MouseButtonPressed &&
					 event.mouseButton.button == sf::Mouse::Left)
			{
				// Cell area logic.
				if (event.mouseButton.x < WIDTH * CELL_SIZE)
				{
					int xPos = event.mouseButton.x / CELL_SIZE;
					int yPos = event.mouseButton.y / CELL_SIZE;
					Vector2 cellPos(xPos, yPos);

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
				// UI logic.
				else
				{
					if (pauseBtn.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						pauseSimulation = !pauseSimulation;
						buttonManager.UpdatePauseBtn(pauseBtn, pauseLabel, pauseSimulation, WIDTH * CELL_SIZE);
					}
					else if (pauseSimulation == true && stepBtn.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						step = true;
						pauseSimulation = false;
					}
					else if (restartBtn.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						generationElapsed = 0;
						step = clearBoard;
						pauseSimulation = clearBoard;
						generationLabel.setString("Generations:\n" + std::to_string(generationElapsed));
						buttonManager.UpdatePauseBtn(pauseBtn, pauseLabel, pauseSimulation, WIDTH * CELL_SIZE);

						cellManager = CellManager(WIDTH, LENGTH, clearBoard ? CellStateEnum::Dead : CellStateEnum::NONE);
						cellMap = cellManager.getCellDict();
					}
					else if (clearCheckboxBtn.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						clearBoard = !clearBoard;
						std::string result = clearBoard ? "True" : "False";
						clearCheckboxLabel.setString("Clear:\n" + result);
					}
				}
			}
		}

		// Clear the window.
		window.clear(sf::Color::Black);

		// Draw cell BG.
		window.draw(cellBackground);

		if (pauseSimulation == false)
		{
			generationElapsed += 1;
			generationLabel.setString("Generations:\n" + std::to_string(generationElapsed));

			// Cell state logic.
			cellManager.UpdateCells();
		}
		else
		{
			window.draw(stepBtn);
			window.draw(stepLabel);
		}

		// Cell draw logic.
		window.draw(GetCellsForDraw(&vertexArray, &cellMap));

		// Draw UI.
		window.draw(pauseBtn);
		window.draw(pauseLabel);
		window.draw(restartBtn);
		window.draw(restartLabel);
		window.draw(clearCheckboxBtn);
		window.draw(clearCheckboxLabel);
		window.draw(generationLabel);

		// FPS.
		fpsHandler.Update();
		window.draw(fpsHandler.getFpsText());

		// End the current frame.
		window.display();

		if (step == true)
		{
			step = false;
			pauseSimulation = true;
		}
	}

	return 0;
}