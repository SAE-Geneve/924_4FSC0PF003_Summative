//
// Created by sebas on 07/07/2025.
//

#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H
#include <random>
#include <SFML/Graphics.hpp>

// Classe Sprite personnalisée
class GameSprite {
    sf::Vector2f position_;
    float alpha_;
    float fade_speed_;
    bool is_active_;
    sf::Color base_color_;
    sf::Color current_color_;
    float scale_;

    sf::Texture texture_;

    // Générateur de nombres aléatoires
    std::random_device rd_;
    std::mt19937 gen_;
    std::uniform_int_distribution<> color_dist_;
    std::uniform_real_distribution<float> fade_dist_;
    std::uniform_real_distribution<float> scale_dist_;

public:
    explicit GameSprite(sf::Vector2f pos, const sf::Texture& texture);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    [[nodiscard]] bool is_active() const ;
    [[nodiscard]] sf::Vector2f position() const;
    [[nodiscard]] float alpha() const;

};

#endif //GAME_SPRITE_H
