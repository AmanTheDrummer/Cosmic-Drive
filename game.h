#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include "state.h"
#include "Spaceship.h"
#include "Meteor.h"
#include "Points.h"
#include "options.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
using namespace std;

class game : public state
{

private:

	sf::Clock clock;
	float spawntimer;
	float seconds;
	float speedIncRate;
	float spawntimermax;
	int maxmeteors;
	sf::Vector2f targetPos;
	float easingProgress;
	bool gameOver;
	sf::Texture defTexture;
	sf::Texture rightship;
	sf::Texture leftship;
	GameState nextState;
	options::DiffLevel currentDifficulty;
	options optionsInstance;

public:

	Spaceship ship;
	Meteor meteor;
	vector <Meteor> meteors;
	Points points;

	game();
	void bgAnimation() override;
	void AdjustDifficulty();
	void loadDifficulty();
	void updateShipPos();
	bool endState() override;
	void HandleInput();
	void Interpolation();
	void SpawnMeteors();
	void MoveMeteors();
	bool CheckCollision();
	void gamepoints();
	float easeOut(float start, float end, float progress);
	void RenderMeteors(sf::RenderWindow& window);
	void update() override;
	void render(sf::RenderWindow& window) override;
	GameState getNextState() const override;

};
