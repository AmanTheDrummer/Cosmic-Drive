#pragma once
#include <vector>
#include <string>
#include "state.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "ResourceManager.h"
using namespace std;

class menu : public state
{
public:

	menu();
	void centerText(sf::Text& text, float x, float y);
	void HandleInput(sf::Event inputEvent) override;
	bool endState() override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	GameState getNextState() const override;

private:
	sf::Text Heading;
	sf::Text subHeading;
	sf::Text Options;
	sf::Text Exit;
	sf::Font font;
	sf::Event inputEvent;
	bool menuOver;
	GameState nextState;

};