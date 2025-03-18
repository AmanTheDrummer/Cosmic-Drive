#include "Points.h"
using namespace std;

Points::Points()
{
    this->pointsText.setCharacterSize(14);
    this->pointsText.setFillColor(sf::Color::White);
    this->pointsText.setPosition(15.f, 400.f);
    this->pointsText.setFont(font);

    this->HighScoreText.setCharacterSize(14);
    this->HighScoreText.setFillColor(sf::Color::White);
    this->HighScoreText.setPosition(15.f, 420.f);
    this->HighScoreText.setFont(font);

    font.loadFromFile("assets/8-BIT WONDER.ttf");

}

void Points::disppoints()
{

    // Update points based on elapsed time
    point += 0.05f;

    // Update points text
    pointsString = "Points " + to_string(static_cast<int>(point));
    pointsText.setString(pointsString);

    // Read high score from file
    int highscore = checkHighScore();

    // Display high score on the screen
    string highScoreString = "High Score " + to_string(highscore);
    HighScoreText.setString(highScoreString);

}

void Points::savepoints()
{
    std::ofstream outputFile("gamepoints.txt", std::ios::out); // Open file for writing (append mode)

    if (outputFile.is_open()) {
        outputFile << static_cast<int>(point) << std::endl; // Write score to the file
        outputFile.close(); // Close the file
    }
    else {
        //cout << "Failed to open points.txt for writing\n";
    }
}

int Points::checkHighScore() {
    int highscore = 0;
    int score = 0;
    int newHighScore = 0;

    // Read high score from file
    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile >> highscore;
        highScoreFile.close();
    }

    // Read score from gamepoints.txt
    std::ifstream scoreFile("gamepoints.txt");
    if (scoreFile.is_open()) {
        scoreFile >> score;
        scoreFile.close();
    }

    // Update high score if necessary
    if (score > highscore) {
        newHighScore = score;
        // Write new high score to file, overwriting the old one
        std::ofstream updateHighScoreFile("highscore.txt", std::ios::out | std::ios::trunc);
        if (updateHighScoreFile.is_open()) {
            updateHighScoreFile << newHighScore;
            updateHighScoreFile.close();
        }
    }
    else {
        newHighScore = highscore;
    }

    return newHighScore;
    return highscore;
}

int Points::checkCurrentScore()
{
    int currentscore = 0, score;
    std::fstream inputFile("gamepoints.txt");

        if (inputFile.is_open())
        {
            while (inputFile >> score)
            {
                currentscore = score;
            }
            inputFile.close();
        }
        else {
            //std::cerr << "Failed to open points.txt for reading\n";
        }

        return currentscore;
}

sf::Text Points::getPoints()
{
    return pointsText;
}

sf::Text Points::getHighScore()
{
    return HighScoreText;
}

sf::Font Points::getFont()
{
    return font;
}
void Points::setFont(sf::Font Font)
{
    font = Font;
    pointsText.setFont(font);
    HighScoreText.setFont(font);
}
