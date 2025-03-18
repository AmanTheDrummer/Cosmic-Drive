#pragma once
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;

class Points
{
private:
	float point = 0.0f;
	std::string pointsString;
	sf::Text pointsText;
	sf::Text HighScoreText;
	sf::Font font;

public:
	Points();

	void disppoints();
	void savepoints();
	int checkHighScore();
	int checkCurrentScore();
	sf::Text getPoints();
	sf::Text getHighScore();
	sf::Font getFont();
	void setFont(sf::Font Font);
};
