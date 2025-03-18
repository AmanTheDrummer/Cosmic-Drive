#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "statestack.h"
#include "state.h"
#include "game.h"
#include "menu.h"
#include "options.h"
#include "endgame.h"
#include "ResourceManager.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "Game");
    loadfiles();

    // Load background texture
    sf::Texture bgTexture;
    auto bgIt = textureMap.find("spacebackground.png");
    if (bgIt != textureMap.end())
    {
        bgTexture = bgIt->second;
    }
    else
    {
        std::cerr << "Texture 'spacebackground.png' not found in the resource map!" << std::endl;
    }
    sf::Sprite bgSprite(bgTexture);

    window.setFramerateLimit(60);
    statestack states;
    states.pushState(make_shared<menu>());
    playmusic();

    while (window.isOpen())
    {
        sf::Event events;
        auto currentstate = states.getCurrentState();

        // Poll and pass events to the current state's HandleInput function
        while (window.pollEvent(events))
        {
            if (events.type == sf::Event::Closed)
            {
                window.close();
            }

            if (currentstate)
            {
                currentstate->HandleInput(events); // Pass event to state
            }
        }

        // Update and transition between states
        currentstate->update();

        if (currentstate->endState())
        {
            switch (currentstate->getNextState())
            {
            case state::GameState::Exit:
                window.close();
                break;

            case state::GameState::Playing:
                states.popState();
                states.pushState(make_shared<game>());
                break;

            case state::GameState::Menu:
                states.popState();
                states.pushState(make_shared<menu>());
                break;

            case state::GameState::End:
                states.popState();
                states.pushState(make_shared<endgame>());
                break;

            case state::GameState::Options:
                states.popState();
                states.pushState(make_shared<options>());
                break;

            default:
                break;
            }
        }

        // Render the current state
        window.clear();
        window.draw(bgSprite);
        currentstate->render(window);
    }

    system("pause");
    return 0;
}
