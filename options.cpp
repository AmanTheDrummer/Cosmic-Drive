#include "options.h"

options::options()
{
	optionsOver = false;
	selectedOption = OptionType::MusicVolume;
    MusicVol = static_cast<int>(bgMusicVolume = getMusicVol());
    currentDifficulty = loadSettings();
	font.loadFromFile("assets/8-BIT WONDER.ttf");

	Music.setString("Music Volume");
	Music.setCharacterSize(26);
	Music.setFillColor(sf::Color::White);
	Music.setFont(font);

	Difficulty.setString("Difficulty Level");
	Difficulty.setCharacterSize(26);
	Difficulty.setFillColor(sf::Color::White);
	Difficulty.setFont(font);

	MusicVolume.setString(std::to_string(MusicVol));
	MusicVolume.setCharacterSize(26);
	MusicVolume.setFillColor(sf::Color::White);
	MusicVolume.setFont(font);

    // Set DifficultyLevel text to reflect currentDifficulty
    switch (currentDifficulty) {
    case DiffLevel::Easy:
        DifficultyLevel.setString("Easy");
        break;
    case DiffLevel::Medium:
        DifficultyLevel.setString("Medium");
        break;
    case DiffLevel::Hard:
        DifficultyLevel.setString("Hard");
        break;
    }
    DifficultyLevel.setCharacterSize(26);
    DifficultyLevel.setFillColor(sf::Color::White);
    DifficultyLevel.setFont(font);

	Exit.setString("Press ESC to return to Menu");
	Exit.setCharacterSize(26);
	Exit.setFillColor(sf::Color::White);
	Exit.setFont(font);

	centerText(Exit, 400.f, 175.f);
	centerText(MusicVolume, 700.f, 285.f);
	centerText(Music, 200, 285);
	centerText(DifficultyLevel, 700.f, 320.f);
	centerText(Difficulty, 233, 320);
}

void options::HandleInput(sf::Event inputEvent)
{
    if (inputEvent.type == sf::Event::KeyPressed)
    {
        switch (inputEvent.key.code)
        {
        case sf::Keyboard::Escape:
            nextState = GameState::Menu;
            playSoundEffect("Button click sfx.mp3");
            optionsOver = true;
            break;

        case sf::Keyboard::Up:
            // Move up the menu
            selectedOption = static_cast<OptionType>(
                (static_cast<int>(selectedOption) - 1 + static_cast<int>(OptionType::TotalOptions)) %
                static_cast<int>(OptionType::TotalOptions));
            break;

        case sf::Keyboard::Down:
            // Move down the menu
            selectedOption = static_cast<OptionType>(
                (static_cast<int>(selectedOption) + 1) %
                static_cast<int>(OptionType::TotalOptions));
            break;

        case sf::Keyboard::Left:
            if (selectedOption == OptionType::MusicVolume && bgMusicVolume > 0)
            {
                // Decrease music volume
                bgMusicVolume -= 1;
                setMusicVol(bgMusicVolume);
                MusicVol = static_cast<int>(bgMusicVolume = getMusicVol());
                MusicVolume.setString(std::to_string(MusicVol));
            }
            break;

        case sf::Keyboard::Right:
            if (selectedOption == OptionType::MusicVolume)
            {
                // Increase music volume
                if (bgMusicVolume < 100) // Assuming 100 is the max volume
                {
                    bgMusicVolume += 1;
                    setMusicVol(bgMusicVolume);
                    MusicVol = static_cast<int>(bgMusicVolume = getMusicVol());
                    MusicVolume.setString(std::to_string(MusicVol));
                }
            }
            else if (selectedOption == OptionType::DifficultyLevel)
            {
                playSoundEffect("Button click sfx.mp3");

                // Cycle through difficulty levels
                if (currentDifficulty == DiffLevel::Medium)
                {
                    currentDifficulty = DiffLevel::Hard;
                    DifficultyLevel.setString("Hard");
                    setDifficulty(DiffLevel::Hard);
                }
                else if (currentDifficulty == DiffLevel::Hard)
                {
                    currentDifficulty = DiffLevel::Easy;
                    DifficultyLevel.setString("Easy");
                    setDifficulty(DiffLevel::Easy);
                }
                else
                {
                    currentDifficulty = DiffLevel::Medium;
                    DifficultyLevel.setString("Medium");
                    setDifficulty(DiffLevel::Medium);
                }

                saveSettings(currentDifficulty);  // Save updated difficulty to file
            }
            break;

        default:
            nextState = GameState::None;
            break;
        }
    }
}

void options::centerText(sf::Text& text, float x, float y)
{
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(x, y);
}

bool options::endState()
{
	return optionsOver;
}

void options::update()
{
	HandleInput(inputEvent);
}

void options::render(sf::RenderWindow& window)
{
    // Highlight the selected option
    Music.setFillColor(selectedOption == OptionType::MusicVolume ? sf::Color::Yellow : sf::Color::White);
    MusicVolume.setFillColor(selectedOption == OptionType::MusicVolume ? sf::Color::Yellow : sf::Color::White);
    Difficulty.setFillColor(selectedOption == OptionType::DifficultyLevel ? sf::Color::Yellow : sf::Color::White);
    DifficultyLevel.setFillColor(selectedOption == OptionType::DifficultyLevel ? sf::Color::Yellow : sf::Color::White);

    // Clear the window
    window.clear(sf::Color::Black);

    // Draw all components
    window.draw(bgSprite1);
    window.draw(bgSprite2);
    window.draw(Music);
    window.draw(MusicVolume);
    window.draw(Difficulty);
    window.draw(DifficultyLevel);
    window.draw(Exit);

    // Display the rendered frame
    window.display();
}


state::GameState options::getNextState() const
{
	return nextState;
}

options::DiffLevel options::getDifficulty() const
{
    return currentDifficulty;
}

void options::saveSettings(options::DiffLevel currentDifficulty)
{
    std::ofstream outFile("assets/difficulty.txt", std::ios::trunc);  // Open the file for writing (overwrite)
    if (outFile.is_open())
    {
        switch (currentDifficulty)
        {
        case options::DiffLevel::Easy:
            outFile << "Easy" << std::endl;
            break;
        case options::DiffLevel::Medium:
            outFile << "Medium" << std::endl;
            break;
        case options::DiffLevel::Hard:
            outFile << "Hard" << std::endl;
            break;
        }
        outFile.close();  // Close the file
    }
    else
    {
        std::cerr << "Unable to open settings file for saving!" << std::endl;
    }
}


options::DiffLevel options::loadSettings()
{
    std::ifstream inFile("assets/difficulty.txt");
    std::string difficulty;
    if (inFile.is_open())
    {
        std::getline(inFile, difficulty);
        inFile.close();

        if (difficulty == "Easy")
        {
            setDifficulty(DiffLevel::Easy);
            return options::DiffLevel::Easy;
        }
        else if (difficulty == "Medium")
        {
            setDifficulty(DiffLevel::Medium);
            return options::DiffLevel::Medium;
        }
        else if (difficulty == "Hard")
        {
            setDifficulty(DiffLevel::Hard);
            return options::DiffLevel::Hard;
        }
    }
    else
    {
        std::cerr << "Unable to open settings file for loading!" << std::endl;
    }

    // Default to Medium
    setDifficulty(DiffLevel::Medium);
    return options::DiffLevel::Medium;
}


void options::setDifficulty(DiffLevel newDifficulty)
{
    currentDifficulty = newDifficulty;

    // Update the DifficultyLevel text to reflect the new difficulty
    switch (currentDifficulty) {
    case DiffLevel::Easy:
        DifficultyLevel.setString("Easy");
        break;
    case DiffLevel::Medium:
        DifficultyLevel.setString("Medium");
        break;
    case DiffLevel::Hard:
        DifficultyLevel.setString("Hard");
        break;
    }

    // Optionally, save the new difficulty to the file
    saveSettings(currentDifficulty);
}

