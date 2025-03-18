#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Spaceship
{
private:

	sf::Texture texture;
	sf::Sprite ship;

public:

	Spaceship();
	sf::Vector2f getPosition();
	void setPosition(float x ,float y);
	sf::Sprite getShip();
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getLocalBounds();
	void setTexture(sf::Texture& texture);

};