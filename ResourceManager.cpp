#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

sf::Music bgMusic;
sf::Sound selectSound;
sf::SoundBuffer selectBuffer;
std::map<std::string, sf::Texture> textureMap;
std::map<std::string, sf::SoundBuffer> soundBufferMap;
float globalMusicVol = 50.0;

//function to find the assets from a file directory
std::vector<fs::path> findfiles(const std::string& directory, const std::string& ext)
{
    //vector that contains file paths.
    std::vector<fs::path> files;

    for (const auto& entry : fs::recursive_directory_iterator(directory))
    {
        if (entry.path().extension() == ext)
        {
            files.push_back(entry.path());
        }
    }
    return files;
}

void loadfiles()
{
    // Texture files
    std::vector<fs::path> textureFiles = findfiles("assets", ".png");

    for (const auto& texturefile : textureFiles)
    {
        sf::Texture texture;
        if (texture.loadFromFile(texturefile.string()))
        {
            std::string key = texturefile.filename().string();
            textureMap[key] = std::move(texture);
            std::cout << "Loaded texture: " << key << std::endl;
        }
        else
        {
            std::cerr << "Failed to load texture: " << texturefile.string() << std::endl;
        }
    }

    // Sound files
    std::vector<fs::path> soundFiles = findfiles("assets", ".mp3");

    for (const auto& soundfile : soundFiles)
    {
        sf::SoundBuffer soundBuffer;
        if (soundBuffer.loadFromFile(soundfile.string()))
        {
            std::string key = soundfile.filename().string(); // Use filename as the key
            soundBufferMap[key] = std::move(soundBuffer);
            std::cout << "Loaded sound: " << key << std::endl;
        }
        else
        {
            std::cerr << "Failed to load sound: " << soundfile.string() << std::endl;
        }
    }
}


void playmusic()
{
    if (!bgMusic.openFromFile("assets/Eliminate - Waste My Time.mp3"))
    {
        std::cerr << "Bg Music Failed to load!" << std::endl;
    }
    bgMusic.play();
    bgMusic.setLoop(true);
}

float getMusicVol()
{
    return globalMusicVol;
}

void setMusicVol(float volume)
{
    // Clamp the volume between 0 and 100
    globalMusicVol = std::clamp(volume, 0.0f, 100.0f);

    // Update the music volume in real-time
    bgMusic.setVolume(globalMusicVol);
}

void playSoundEffect(const std::string& soundKey)
{
    // Check if the sound exists in the soundBufferMap
    auto it = soundBufferMap.find(soundKey);
    if (it != soundBufferMap.end())
    {
        // Set the buffer for the sound object
        selectSound.setBuffer(it->second);

        // Play the sound
        selectSound.setVolume(35);
        selectSound.play();
    }
    else
    {
        std::cerr << "Sound effect '" << soundKey << "' not found in soundBufferMap!" << std::endl;
    }
}


