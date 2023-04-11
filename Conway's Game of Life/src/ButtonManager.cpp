#include "ButtonManager.h"

// ----- Public -----

ButtonManager::ButtonManager(const int width, const int cellSize) : width(width), cellSize(cellSize)
{
	// Load font.
	font.loadFromFile("Resources/Font/arial.ttf");

	SetupPauseButton();
	SetupStepButton();
	SetupRestartButton();
	SetupClearButton();
	SetupGenerationLabel();
}

sf::RectangleShape ButtonManager::getPauseBtn() const { return pauseBtn; }

sf::Text ButtonManager::getPauseLabel() const { return pauseLabel; }

sf::RectangleShape ButtonManager::getStepBtn() const { return stepBtn; }

sf::Text ButtonManager::getStepLabel() const { return stepLabel; }

sf::RectangleShape ButtonManager::getRestartBtn() const { return restartBtn; }

sf::Text ButtonManager::getRestartLabel() const { return restartLabel; }

sf::RectangleShape ButtonManager::getClearCheckboxBtn() const { return clearCheckboxBtn; }

sf::Text ButtonManager::getClearCheckboxLabel() const { return clearCheckboxLabel; }

sf::Text ButtonManager::getGenerationLabel() const { return generationLabel; }

void ButtonManager::UpdatePauseBtn(const bool isSimulationPaused)
{
	if (isSimulationPaused)
	{
		pauseBtn.setPosition(width * cellSize + (25 + 10), 50);

		pauseLabel.setString("Unpause");
		pauseLabel.setPosition(width * cellSize + (35 + 10), 50 + 10);
	}
	else
	{
		pauseBtn.setPosition(width * cellSize + 50, 50);

		pauseLabel.setString("Pause");
		pauseLabel.setPosition(width * cellSize + (50 + 20), 50 + 10);
	}
}

void ButtonManager::UpdateCheckboxLabel(const bool clearBoard)
{
	std::string result = clearBoard ? "True" : "False";
	clearCheckboxLabel.setString("Clear:\n" + result);
}

void ButtonManager::UpdateGenerationLabel(const int generationElapsed)
{
	generationLabel.setString("Generations:\n" + std::to_string(generationElapsed));
}

// ----- Private -----

void ButtonManager::SetupPauseButton()
{
	// Create pause button.
	pauseBtn = sf::RectangleShape(sf::Vector2f(100, 50));
	pauseBtn.setPosition(width * cellSize + 50, 50);
	pauseBtn.setFillColor(sf::Color::White);

	// Create pause label.
	pauseLabel = sf::Text("Pause", font);
	pauseLabel.setCharacterSize(20);
	pauseLabel.setFillColor(sf::Color::Black);
	pauseLabel.setPosition(width * cellSize + (50 + 20), 50 + 10);
}

void ButtonManager::SetupStepButton()
{
	// Create step button.
	stepBtn = sf::RectangleShape(sf::Vector2f(20, 50));
	stepBtn.setPosition(width * cellSize + 145, 50);
	stepBtn.setFillColor(sf::Color::White);

	// Create step label.
	stepLabel = sf::Text("+", font);
	stepLabel.setCharacterSize(20);
	stepLabel.setFillColor(sf::Color::Black);
	stepLabel.setPosition(width * cellSize + 150, 60);
}

void ButtonManager::SetupRestartButton()
{
	// Create restart button.
	restartBtn = sf::RectangleShape(sf::Vector2f(100, 50));
	restartBtn.setPosition(width * cellSize + 20, 125);
	restartBtn.setFillColor(sf::Color::White);

	// Create restart label.
	restartLabel = sf::Text("Restart", font);
	restartLabel.setCharacterSize(20);
	restartLabel.setFillColor(sf::Color::Black);
	restartLabel.setPosition(width * cellSize + (20 + 15), 125 + 10);
}

void ButtonManager::SetupClearButton()
{
	// Create clear button.
	clearCheckboxBtn = sf::RectangleShape(sf::Vector2f(60, 35));
	clearCheckboxBtn.setPosition(width * cellSize + 130, 130);
	clearCheckboxBtn.setFillColor(sf::Color::White);

	// Create clear label.
	clearCheckboxLabel = sf::Text("Clear:\nFalse", font);
	clearCheckboxLabel.setCharacterSize(15);
	clearCheckboxLabel.setFillColor(sf::Color::Black);
	clearCheckboxLabel.setPosition(width * cellSize + 140, 130);
}

void ButtonManager::SetupGenerationLabel()
{
	// Create generation label.
	generationLabel = sf::Text();
	generationLabel.setFont(font);
	generationLabel.setCharacterSize(20);
	generationLabel.setFillColor(sf::Color::White);
	generationLabel.setPosition(width * cellSize + 40, 200 + 10);
}