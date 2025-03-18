#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Meteor
{
private:

	sf::Texture texture;
	sf::Sprite meteor;
	
public:

	Meteor();
	sf::Sprite getMeteor();
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	sf::FloatRect getGlobalBounds();
	void move(float dx, float dy);

};