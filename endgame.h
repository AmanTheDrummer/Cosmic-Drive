#pragma once
#include <string>
#include "Points.h"
#include "state.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "ResourceManager.h"
using namespace std;

class endgame : public state
{
private:
	sf::Text Heading;
	sf::Text subHeading;
	sf::Text score;
	GameState nextState;
	sf::Font font;
	Points points;
	sf::Event inputEvent;
	int currentpoints;
	bool endOver;

public:
	endgame();
	void centerText(sf::Text& text, float x, float y);
	void HandleInput(sf::Event inputEvent) override;
	bool endState() override;
	void bgAnimation() override;
	void render(sf::RenderWindow& window);
	void update();
	GameState getNextState() const override;
};
