//
// Created by sebas on 07/07/2025.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "game_sprite_manager.h"

// Classe principale du jeu
class Game {

    sf::RenderWindow window_;
    GameSpriteManager sprite_manager_;
    sf::Clock clock_;
    sf::Font font_;
    sf::Text info_text_;
    sf::Text instructions_text_;


public:
    Game();
    void Run();

private:
    void SetupText();void HandleMousePressed(const sf::Event::MouseButtonPressed*mousePressed);
    void HandleKeyPress(sf::Keyboard::Key key);

    void HandleEvents();
    void Update();
    void Render();

};

#endif
