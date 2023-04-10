#include "ButtonManager.h"

ButtonManager::ButtonManager(const int width, const int cellSize) : width(width), cellSize(cellSize)
{
	// Load font.
	font.loadFromFile("Resources/Font/arial.ttf");
}

void ButtonManager::SetupPauseButton(sf::RectangleShape& btn, sf::Text& label)
{
	// Create pause button.
	btn = sf::RectangleShape(sf::Vector2f(100, 50));
	btn.setPosition(width * cellSize + 50, 50);
	btn.setFillColor(sf::Color::White);

	// Create pause label.
	label = sf::Text("Pause", font);
	label.setCharacterSize(20);
	label.setFillColor(sf::Color::Black);
	label.setPosition(width * cellSize + (50 + 20), 50 + 10);
}

void ButtonManager::SetupStepButton(sf::RectangleShape& btn, sf::Text& label)
{
	// Create step button.
	btn = sf::RectangleShape(sf::Vector2f(20, 50));
	btn.setPosition(width * cellSize + 145, 50);
	btn.setFillColor(sf::Color::White);

	// Create step label.
	label = sf::Text("+", font);
	label.setCharacterSize(20);
	label.setFillColor(sf::Color::Black);
	label.setPosition(width * cellSize + 150, 60);
}

void ButtonManager::SetupRestartButton(sf::RectangleShape& btn, sf::Text& label)
{
	// Create restart button.
	btn = sf::RectangleShape(sf::Vector2f(100, 50));
	btn.setPosition(width * cellSize + 20, 125);
	btn.setFillColor(sf::Color::White);

	// Create restart label.
	label = sf::Text("Restart", font);
	label.setCharacterSize(20);
	label.setFillColor(sf::Color::Black);
	label.setPosition(width * cellSize + (20 + 15), 125 + 10);
}

void ButtonManager::SetupClearButton(sf::RectangleShape& btn, sf::Text& label)
{
	// Create clear button.
	btn = sf::RectangleShape(sf::Vector2f(60, 35));
	btn.setPosition(width * cellSize + 130, 130);
	btn.setFillColor(sf::Color::White);

	// Create clear label.
	label = sf::Text("Clear:\nFalse", font);
	label.setCharacterSize(15);
	label.setFillColor(sf::Color::Black);
	label.setPosition(width * cellSize + 140, 130);
}

void ButtonManager::SetupGenerationLabel(sf::Text& label)
{
	// Create generation label.
	label = sf::Text();
	label.setFont(font);
	label.setCharacterSize(20);
	label.setFillColor(sf::Color::White);
	label.setPosition(width * cellSize + 40, 200 + 10);
}

void ButtonManager::UpdatePauseBtn(sf::RectangleShape& btn, sf::Text& label, const bool isSimulationPaused, const int offset)
{
	if (isSimulationPaused)
	{
		btn.setPosition(offset + (25 + 10), 50);

		label.setString("Unpause");
		label.setPosition(offset + (35 + 10), 50 + 10);
	}
	else
	{
		btn.setPosition(offset + 50, 50);

		label.setString("Pause");
		label.setPosition(offset + (50 + 20), 50 + 10);
	}
}