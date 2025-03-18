#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

class state
{
public:

	enum class GameState
	{ None, Menu, Playing, End, Exit, Options };

	sf::Sprite bgSprite1;
	sf::Sprite bgSprite2;
    sf::Texture bgTexture;
	sf::Event inputEvent;
	float bgPosition1Y;
	float bgPosition2Y;
	float scrollSpeed;

	state();
	virtual void bgAnimation();
	virtual void update();
	virtual void HandleInput(sf::Event inputEvent);
	virtual void render(sf::RenderWindow& window);
	virtual bool endState();
	virtual GameState getNextState() const = 0;
	virtual ~state();
};