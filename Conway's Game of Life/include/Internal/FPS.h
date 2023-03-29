#pragma once

#include <SFML/Graphics.hpp>

class FPS
{
public:
	FPS();
	sf::Text getFpsText() const;

private:
	sf::Font font;
	sf::Text fpsText;
	sf::Clock clock;

	sf::Time currentTime;
	sf::Time previousTime;

	void SetFpsText(const float fps);

public:
	void Update();
	void SetFpsTextPosition(const float x, const float y);
};