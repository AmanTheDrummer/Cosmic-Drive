#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "state.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "ResourceManager.h"
using namespace std;

class options : public state
{
public:

	//Class to select one of the many options.
	enum class OptionType
	{
		MusicVolume, DifficultyLevel, TotalOptions
	};

	enum class DiffLevel
	{
		Easy, Medium, Hard
	};

	options();
	void HandleInput(sf::Event inputEvent) override;
	void centerText(sf::Text& text, float x, float y);
	bool endState() override;
	void update() override;
	void render(sf::RenderWindow& window) override;
	GameState getNextState() const override;
	DiffLevel getDifficulty() const;
	void setDifficulty(DiffLevel newDifficulty);
	void saveSettings(options::DiffLevel currentDifficulty);
	DiffLevel loadSettings();
	

private:
	OptionType selectedOption;
	sf::Text Music;
	sf::Text MusicVolume;
	sf::Text Difficulty;
	sf::Text DifficultyLevel;
	sf::Text Exit;
	sf::Font font;
	sf::Event inputEvent;
	bool optionsOver;
	GameState nextState;
	float bgMusicVolume;
	DiffLevel currentDifficulty = DiffLevel::Medium;
	int MusicVol; //to display volume
};