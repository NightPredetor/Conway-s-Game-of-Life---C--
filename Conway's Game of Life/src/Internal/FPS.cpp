#include "Internal/FPS.h"
#include <iostream>

FPS::FPS()
{
	// Load font.
	if (!font.loadFromFile("Resources/Font/arial.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
		return;
	}

	// Set font and size.
	fpsText.setFont(font);
	fpsText.setCharacterSize(20);

	// Set color.
	fpsText.setFillColor(sf::Color::White);

	// Set outline.
	fpsText.setOutlineThickness(1);
	fpsText.setOutlineColor(sf::Color::Black);

	// Set position.
	SetFpsTextPosition(0, 0);

	clock = sf::Clock::Clock();
	previousTime = clock.getElapsedTime();
}

sf::Text FPS::getFpsText() const
{
	return fpsText;
}

void FPS::Update()
{
	// Get delta time.
	currentTime = clock.getElapsedTime();

	// Divide the deltaTime by 1.
	// Because this runs inside an update loop, which gets called each frame.
	float fps = 1.f / (currentTime.asSeconds() - previousTime.asSeconds());

	// Set last time for next calculation.
	previousTime = currentTime;

	SetFpsText(fps);
}

void FPS::SetFpsTextPosition(const float x, const float y)
{
	fpsText.setPosition(x, y);
}

void FPS::SetFpsText(const float fps)
{
	// Update FPS.
	fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
}
