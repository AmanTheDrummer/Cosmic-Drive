#include "state.h"
#include "ResourceManager.h"

state::state()
{
    scrollSpeed = 1.0f;

    // Load the background texture from the resource map
    auto bgTextureIt = textureMap.find("spacebackground.png");
    if (bgTextureIt != textureMap.end())
    {
        bgTexture = bgTextureIt->second;
        bgSprite1.setTexture(bgTexture);
        bgSprite2.setTexture(bgTexture);
    }
    else
    {
        std::cerr << "Texture 'spacebackground.png' not found in the resource map!" << std::endl;
        // Handle the error, possibly using a default texture or exiting
    }

    bgPosition1Y = 0.0f;
    bgPosition2Y = -static_cast<float>(bgTexture.getSize().y); // Position the second sprite above the first one
}

void state::bgAnimation()
{
    // Move both backgrounds down
    bgPosition1Y += scrollSpeed;
    bgPosition2Y += scrollSpeed;

    // Check if bgSprite1 has scrolled out of view
    if (bgPosition1Y > bgTexture.getSize().y)
    {
        // Move bgSprite1 above bgSprite2 to create seamless loop
        bgPosition1Y = bgPosition2Y - static_cast<float>(bgTexture.getSize().y);
    }

    // Check if bgSprite2 has scrolled out of view
    if (bgPosition2Y > bgTexture.getSize().y)
    {
        // Move bgSprite2 above bgSprite1 to create seamless loop
        bgPosition2Y = bgPosition1Y - static_cast<float>(bgTexture.getSize().y);
    }

    // Update sprite positions
    bgSprite1.setPosition(0.0f, bgPosition1Y);
    bgSprite2.setPosition(0.0f, bgPosition2Y);
}

void state::update()
{
}

void state::HandleInput(sf::Event inputEvent)
{
}

void state::render(sf::RenderWindow& window)
{
	window.draw(bgSprite1);
    window.draw(bgSprite2);
}

bool state::endState()
{
	return true;
}

state::~state()
{
}
