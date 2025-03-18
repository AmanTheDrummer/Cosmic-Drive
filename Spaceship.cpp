#include "Spaceship.h"
#include "ResourceManager.h"

Spaceship::Spaceship()
{
	auto it = textureMap.find("spaceship3.png");
	if (it != textureMap.end())
	{
		texture = it->second;
		ship.setTexture(texture);
	}
	else
	{
		std::cerr << "Texture 'spaceship3.png' not found in the resource map!" << std::endl;
	}

	ship.setPosition(400, 490);
	//ship.setPosition(sf::Vector2f(400, 375));
}

sf::Vector2f Spaceship::getPosition()
{
	return ship.getPosition();
}

void Spaceship::setPosition(float x ,float y)
{
	ship.setPosition(x, y);
}

sf::Sprite Spaceship::getShip()
{
	return ship;
}

sf::FloatRect Spaceship::getGlobalBounds()
{
	return ship.getGlobalBounds();
}

sf::FloatRect Spaceship::getLocalBounds()
{
	return ship.getLocalBounds();
}

void Spaceship::setTexture(sf::Texture& texture)
{
	ship.setTexture(texture);
}

