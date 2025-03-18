#include "menu.h"
#include "ResourceManager.h"

menu::menu()
{
	menuOver = false;
	font.loadFromFile("assets/8-BIT WONDER.ttf");

	Heading.setString("COSMIC DRIVE");
	Heading.setCharacterSize(36);
	Heading.setFillColor(sf::Color::White);
	Heading.setFont(font);

	subHeading.setString("Press ENTER to start");
	subHeading.setCharacterSize(26);
	subHeading.setFillColor(sf::Color::White);
	subHeading.setFont(font);

	Exit.setString("Press ESC to exit");
	Exit.setCharacterSize(26);
	Exit.setFillColor(sf::Color::White);;
	Exit.setFont(font);

	Options.setString("Press S for Settings");
	Options.setCharacterSize(26);
	Options.setFillColor(sf::Color::White);;
	Options.setFont(font);

	centerText(Heading, 400.f, 175.f);
	centerText(subHeading, 400.f, 250.f);
	centerText(Exit, 400, 285);
	centerText(Options, 400.f, 320.f);
}

void menu::centerText(sf::Text& text, float x, float y)
{
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(x, y);
}

void menu::HandleInput(sf::Event inputEvent)
{
	if (inputEvent.type == sf::Event::KeyPressed)
	{
		switch (inputEvent.key.code)
		{
		case sf::Keyboard::Enter:
			nextState = GameState::Playing;
			playSoundEffect("Button click sfx.mp3");
			menuOver = true;
			break;

		case sf::Keyboard::Escape:
			nextState = GameState::Exit;
			playSoundEffect("Button click sfx.mp3");
			menuOver = true;
			break;

		case sf::Keyboard::S:
			nextState = GameState::Options;
			playSoundEffect("Button click sfx.mp3");
			menuOver = true;
			break;

		default:
			nextState = GameState::None;
			break;
		}
	}
}


bool menu::endState()
{
	return menuOver;
}

void menu::update()
{
	HandleInput(inputEvent);
}

void menu::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	window.draw(bgSprite1);
	window.draw(bgSprite2);
	window.draw(Heading);
	window.draw(subHeading);
	window.draw(Exit);
	window.draw(Options);
	window.display();
}

state::GameState menu::getNextState() const
{
	return nextState;
}
