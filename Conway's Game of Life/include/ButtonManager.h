#pragma once
#include <SFML/Graphics.hpp>

class ButtonManager
{
public:
	ButtonManager(const int width, const int cellSize);
	void SetupPauseButton(sf::RectangleShape& btn, sf::Text& label);
	void SetupStepButton(sf::RectangleShape& btn, sf::Text& label);
	void SetupRestartButton(sf::RectangleShape& btn, sf::Text& label);
	void SetupClearButton(sf::RectangleShape& btn, sf::Text& label);
	void SetupGenerationLabel(sf::Text& label);

	void UpdatePauseBtn(sf::RectangleShape& btn, sf::Text& label, const bool isSimulationPaused, const int offset);

private:
	sf::Font font;

	float width;
	float cellSize;
};