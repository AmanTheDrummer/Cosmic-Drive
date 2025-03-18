#pragma once
#include <map>
#include <vector>
#include <filesystem>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

namespace fs = std::filesystem;

//Global Variables
extern sf::Music bgMusic;
extern sf::Sound selectSound;
extern sf::SoundBuffer selectBuffer;
extern std::map<std::string, sf::Texture> textureMap;
extern std::map<std::string, sf::SoundBuffer> soundBufferMap;
extern float globalMusicVol;

//Functions
std::vector<fs::path> findfiles(const std::string& directory, const std::string& ext);
void loadfiles();
void playmusic();
void playSoundEffect(const std::string& soundKey);
float getMusicVol();
void setMusicVol(float volume);
