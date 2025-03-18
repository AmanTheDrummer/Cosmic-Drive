#include "game.h"
#include "ResourceManager.h"

game::game()
{
	gameOver = false;
	spawntimermax = 450.f;
	spawntimer = spawntimermax;
	maxmeteors = 35;
	speedIncRate = 1.5f;
	seconds = 0.f;
	targetPos = ship.getPosition();
	easingProgress = 0.5f;
	scrollSpeed = 0.f;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Load textures from ResourceManager
	auto rightshipIt = textureMap.find("rightship.png");
	if (rightshipIt != textureMap.end())
	{
		rightship = rightshipIt->second;
	}
	else
	{
		std::cerr << "Texture 'rightship.png' not found in the resource map!" << std::endl;
	}

	auto leftshipIt = textureMap.find("leftship.png");
	if (leftshipIt != textureMap.end())
	{
		leftship = leftshipIt->second;
	}
	else
	{
		std::cerr << "Texture 'leftship.png' not found in the resource map!" << std::endl;
	}

	auto defTextureIt = textureMap.find("spaceship3.png");
	if (defTextureIt != textureMap.end())
	{
		defTexture = defTextureIt->second;
	}
	else
	{
		std::cerr << "Texture 'spaceship3.png' not found in the resource map!" << std::endl;
	}
}

void game::bgAnimation()
{
	if (scrollSpeed < 50.f)
	{
		if (scrollSpeed <= 1.0f)
		{
			scrollSpeed += 0.1f;
		}
		else if (scrollSpeed > 1.0f)
		{
			scrollSpeed += 0.002f;
		}
	}
	
	// Move both backgrounds down
	bgPosition1Y += scrollSpeed;
	bgPosition2Y += scrollSpeed;

	// Check if bgSprite1 has scrolled out of view
	if (bgPosition1Y > bgTexture.getSize().y)
	{
		// Move bgSprite1 above bgSprite2 to create a seamless loop
		bgPosition1Y = bgPosition2Y - static_cast<float>(bgTexture.getSize().y);
	}

	// Check if bgSprite2 has scrolled out of view
	if (bgPosition2Y > bgTexture.getSize().y)
	{
		// Move bgSprite2 above bgSprite1 to create a seamless loop
		bgPosition2Y = bgPosition1Y - static_cast<float>(bgTexture.getSize().y);
	}

	// Update sprite positions
	bgSprite1.setPosition(0.0f, bgPosition1Y);
	bgSprite2.setPosition(0.0f, bgPosition2Y);
}

void game::AdjustDifficulty()
{
	switch (currentDifficulty) // Use the selected difficulty
	{
	case options::DiffLevel::Easy:
		spawntimermax = 600.f; // Slow spawn rate
		break;
	case options::DiffLevel::Medium:
		spawntimermax = 450.f; // Moderate spawn rate
		break;
	case options::DiffLevel::Hard:
		spawntimermax = 300.f; // Fast spawn rate
		break;
	}
}

void game::loadDifficulty()
{
	currentDifficulty = optionsInstance.getDifficulty();
	AdjustDifficulty();
}

void game::updateShipPos()
{
	sf::Vector2f currentPos = ship.getPosition();
	if (currentPos.y > 375)
	{
		float rate = 1.0f;
		currentPos.y -= rate;  // Move up
		rate = rate / 4;
		if (currentPos.y < 375)
			currentPos.y = 375;  // Clamp to target
		ship.setPosition(currentPos.x, currentPos.y);
	}
}

void game::HandleInput()
{
	sf::Vector2f newpos = ship.getPosition();

	// Handle continuous input for movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		ship.setTexture(rightship);
		newpos.x += 7.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		ship.setTexture(leftship);
		newpos.x -= 7.f;
	}
	else ship.setTexture(defTexture);

	// Boundary logic
	if (newpos.x < -20)
	{
		newpos.x = -20; // Prevent moving beyond the left boundary
	}
	if (newpos.x + ship.getLocalBounds().width > 820)
	{
		newpos.x = 820 - ship.getLocalBounds().width; // Prevent moving beyond the right boundary
	}

	targetPos = newpos;

}

void game::SpawnMeteors()
{
	//Randomly assigns a position on the x-axis to spawn meteor
	meteor.setPosition(
		static_cast<float>(rand() % static_cast<int>(
			800 - meteor.getGlobalBounds().width)), 0.f);

	meteors.push_back(meteor);
}

bool game::endState()
{
	if (CheckCollision())
	{
		if (!gameOver)
		{
			points.savepoints();
			nextState = GameState::End;
			gameOver = true;
		}
	}
	return gameOver;
}

void game::MoveMeteors()
{
	sf::Time elapsedTime = clock.restart();
	float seconds = elapsedTime.asSeconds(); // Convert elapsed time to seconds

	if (spawntimer >= spawntimermax && static_cast<float>(meteors.size()) < maxmeteors)
	{
		SpawnMeteors(); // Spawn meteors if spawn-timer is less than or equal to max spawn-time.
		spawntimer = 0.0f;
	}
	else
	{
		spawntimer += 100.f * seconds;
	}

	for (size_t i = 0; i < meteors.size(); i++)  // Changed 'int' to 'size_t'
	{
		// Move meteors downwards
		float meteorSpeed = 1.0f + speedIncRate * seconds;
		meteors[i].move(0.f, meteorSpeed);

		if (meteors[i].getPosition().y > 500)
		{
			// Spawn meteors from above if they go below screen boundaries
			float posX = static_cast<float>(rand() % static_cast<int>(800 - meteors[i].getGlobalBounds().width));
			float posY = -meteors[i].getGlobalBounds().height; // Start just above the screen
			meteors[i].setPosition(posX, posY);
		}
	}

	// Increment speed increment rate only once per frame
	speedIncRate += 1.001f * seconds;
}


void game::Interpolation()
{
	// Get the current position of the spaceship
	sf::Vector2f currentPos = ship.getPosition();

	// Calculate the new position using eased progress
	sf::Vector2f newPos = sf::Vector2f(
		easeOut(currentPos.x, targetPos.x, easingProgress),
		currentPos.y
	);

	// Set the new position of the spaceship
	ship.setPosition(newPos.x, newPos.y);

	// Update easing progress
	easingProgress += 0.01f;  // Adjust increment as needed

	// Clamp easingProgress to 1.0 to prevent overshooting
	if (easingProgress > 1.0f)
	{
		easingProgress = 1.0f;
	}
}


void game::RenderMeteors(sf::RenderWindow& window)
{
	for (auto& m : meteors)
	{
		window.draw(m.getMeteor());
	}
}

bool game::CheckCollision()
{
	// Get the global bounds of the ship sprite
	sf::FloatRect shipBounds = ship.getGlobalBounds();

	// Calculate the center of the ship sprite
	float ship_centerX = shipBounds.left + shipBounds.width / 2.f;
	float ship_centerY = shipBounds.top + shipBounds.height / 2.f;
	sf::Vector2f shipCenter(ship_centerX, ship_centerY);

	// Loop through each meteor to check for collisions
	for (auto& m : meteors)
	{
		// Get the global bounds of the meteor sprite
		sf::FloatRect meteorBounds = m.getGlobalBounds();

		// Calculate the center of the meteor sprite
		float meteor_centerX = meteorBounds.left + meteorBounds.width / 2.f;
		float meteor_centerY = meteorBounds.top + meteorBounds.height / 2.f;
		sf::Vector2f meteorCenter(meteor_centerX, meteor_centerY);

		// Calculate distance between the centers
		float dx = meteorCenter.x - shipCenter.x;
		float dy = meteorCenter.y - shipCenter.y;
		float distance = std::sqrt(dx * dx + dy * dy);

		// Check if the distance is less than the sum of the radii (collision detection)
		float shipRadius = shipBounds.width / 2.f; // Assuming the ship is roughly circular
		float meteorRadius = meteorBounds.width / 2.f; // Assuming the meteor is roughly circular

		if (distance < (shipRadius + meteorRadius))
		{
			// Collision detected
			return true;
		}
	}

	// No collision detected
	return false;
}

void game::gamepoints()
{
	points.disppoints();
	points.checkHighScore();
}

float game::easeOut(float start, float end, float progress)
{
	// Calculate the difference between start and end values
	float difference = end - start;

	// Apply the quadratic ease out function to the progress
	float easedProgress = 1.f - static_cast<float>(std::pow(1.f - progress, 2));

	// Use LERP to interpolate between start and end values based on eased progress
	return start + difference * easedProgress;
}

void game::update()
{
	bgAnimation();
	loadDifficulty();
	updateShipPos();
	MoveMeteors();
	HandleInput();
	Interpolation();
	endState();
	gamepoints();
}

void game::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	window.draw(bgSprite1);
	window.draw(bgSprite2);
	window.draw(ship.getShip());
	RenderMeteors(window);
	window.draw(points.getPoints());
	window.draw(points.getHighScore());

	window.display();
}

state::GameState game::getNextState() const 
{
	return nextState;
}

