//
// Created by sebas on 07/07/2025.
//

#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H
#include <random>
#include "game_sprite.h"
#include "texture_manager.h"


// Gestionnaire de sprites
class GameSpriteManager {
private:
    std::vector<std::unique_ptr<GameSprite>> sprites_;
    std::random_device rd_;
    std::mt19937 gen_;
    std::uniform_int_distribution<> type_dist_;
    std::uniform_real_distribution<float> pos_dist_;

    sf::Vector2u window_size_;

    TextureManager texture_manager_;

    void AddSprite(sf::Vector2f position);

public:
    explicit GameSpriteManager(sf::Vector2u winSize);

    void AddSpriteAtRandomPosition();
    void AddSpriteAtMouse(sf::Vector2f mousePos);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window) const;

    [[nodiscard]] size_t GetActiveSpritesCount() const;

    void ClearAllSprites();

};

#endif //SPRITE_MANAGER_H