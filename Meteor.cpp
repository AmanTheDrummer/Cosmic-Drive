#include "Meteor.h"
#include "ResourceManager.h"

Meteor::Meteor()
{
    // Load the texture from the global map
    auto it = textureMap.find("meteor2-1.png");
    if (it != textureMap.end())
    {
        texture = it->second;
        meteor.setTexture(texture);
    }
    else
    {
        std::cerr << "Texture 'meteor2-1.png' not found in the resource map!" << std::endl;
    }
}


sf::Sprite Meteor::getMeteor()
{
	return meteor;
}

sf::Vector2f Meteor::getPosition()
{
	return meteor.getPosition();
}

void Meteor::setPosition(float x, float y)
{
	meteor.setPosition(x, y);
}

sf::FloatRect Meteor::getGlobalBounds()
{
	return meteor.getGlobalBounds();
}

void Meteor::move(float dx, float dy)
{
	meteor.move(dx, 5*dy);
}
