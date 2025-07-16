
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

Game::Game() : window_(sf::VideoMode({1200, 800}), "Jeu de Sprites SFML", sf::Style::Close),
         sprite_manager_(window_.getSize()),
         info_text_(font_),
         instructions_text_(font_){

    window_.setFramerateLimit(60);

    // Chargement de la police (optionnel - utilise la police par défaut si échec)
    if (!font_.openFromFile("_assets/fonts/arial.ttf")) {
        std::cout << "Police arial.ttf non trouvée, utilisation de la police par défaut" << std::endl;
    }

    std::cout << "=== JEU DE SPRITES SFML ===" << std::endl;
    std::cout << "Contrôles :" << std::endl;
    std::cout << "- ESPACE : Ajouter un sprite à une position aléatoire" << std::endl;
    std::cout << "- CLIC GAUCHE : Ajouter un sprite à la position de la souris" << std::endl;
    std::cout << "- C : Effacer tous les sprites" << std::endl;
    std::cout << "- ÉCHAP : Quitter le jeu" << std::endl;
    std::cout << "================================" << std::endl;

}

void Game::Run(){

    SetupText();

    while (window_.isOpen()) {
        HandleEvents();
        Update();
        Render();
    }
}

void Game::SetupText(){
    // Texte d'informations
    info_text_.setFont(font_);
    info_text_.setCharacterSize(20);
    info_text_.setFillColor(sf::Color::White);
    info_text_.setPosition({10, 10});

    // Texte d'instructions
    instructions_text_.setFont(font_);
    instructions_text_.setCharacterSize(16);
    instructions_text_.setFillColor(sf::Color::Yellow);
    instructions_text_.setPosition({10, static_cast<float>(window_.getSize().y - 80)});
    instructions_text_.setString(
        "ESPACE: Sprite aléatoire | CLIC GAUCHE: Sprite à la souris | C: Effacer | ÉCHAP: Quitter");
}

void Game::HandleMousePressed(const sf::Event::MouseButtonPressed *mousePressed) {
    if (mousePressed->button == sf::Mouse::Button::Left) {
        sprite_manager_.AddSpriteAtMouse({
            static_cast<float>(mousePressed->position.x),
            static_cast<float>(mousePressed->position.y)
        });
    }
}

void Game::HandleEvents(){
    while (const std::optional event = window_.pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            window_.close();
        }

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            HandleKeyPress(keyPressed->code);
        }

        if (const auto *mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            HandleMousePressed(mousePressed);
        }
    }
}

void Game::HandleKeyPress(const sf::Keyboard::Key key){
    switch (key) {
        case sf::Keyboard::Key::Space:
            sprite_manager_.AddSpriteAtRandomPosition();
            break;

        case sf::Keyboard::Key::C:
            sprite_manager_.ClearAllSprites();
            std::cout << "Tous les sprites ont été effacés !" << std::endl;
            break;

        case sf::Keyboard::Key::Escape:
            window_.close();
            break;

        default:
            break;
    }
}

void Game::Update(){
    const float deltaTime = clock_.restart().asSeconds();
    sprite_manager_.Update(deltaTime);
}

void Game::Render(){
    window_.clear(sf::Color(30, 30, 50)); // Fond bleu foncé

    // Dessiner les sprites
    sprite_manager_.Draw(window_);

    // Dessiner l'interface
    window_.draw(info_text_);
    window_.draw(instructions_text_);

    window_.display();
}



