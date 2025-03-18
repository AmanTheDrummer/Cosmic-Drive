#include "endgame.h"

endgame::endgame()
{
	endOver = false;
	scrollSpeed = 1.0f;
	font.loadFromFile("assets/8-BIT WONDER.ttf");
	currentpoints = points.checkCurrentScore();
	string currentpointsString = std::to_string(currentpoints);

	Heading.setString("GAME OVER");
	Heading.setCharacterSize(26);
	Heading.setFillColor(sf::Color::White);
	Heading.setFont(font);

	subHeading.setString("Press ENTER to return to Menu");
	subHeading.setCharacterSize(26);
	subHeading.setFillColor(sf::Color::White);
	subHeading.setFont(font);

	score.setString(currentpointsString);
	score.setCharacterSize(26);
	score.setFillColor(sf::Color::Yellow);
	score.setFont(font);

	centerText(Heading, 400.f, 225.f);
	centerText(subHeading, 400.f, 250.f);
	centerText(score, 400.f, 285.f);
}

void endgame::centerText(sf::Text& text, float x, float y)
{
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(x, y);
}

void endgame::HandleInput(sf::Event inputEvent)
{
	if (inputEvent.type == sf::Event::KeyPressed)
	{
		if (inputEvent.key.code == sf::Keyboard::Enter)
		{
			playSoundEffect("Button click sfx.mp3");
			nextState = GameState::Menu;
			endOver = true;
		}
		else
		{
			nextState = GameState::None;
		}
	}
}

bool endgame::endState()
{
    return endOver;
}

void endgame::bgAnimation()
{
	if (scrollSpeed > 0.0f)
	{
		// Gradually reduce the scroll speed to a halt
		scrollSpeed = std::max(scrollSpeed - 0.005f, 0.0f);
	}

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

void endgame::update()
{
	bgAnimation();
	HandleInput(inputEvent);
}

void endgame::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	window.draw(bgSprite1);
	window.draw(bgSprite2);
	window.draw(Heading);
	window.draw(subHeading);
	window.draw(score);
	window.display();
}

state::GameState endgame::getNextState() const
{
	return nextState;
}
