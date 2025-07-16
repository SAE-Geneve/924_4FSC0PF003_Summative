#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>


constexpr int kNumTextures = 36;

class TextureManager {

  std::vector<sf::Texture> textures_;
  std::random_device rd_;
  std::mt19937 gen_;

public:
  void LoadTextures(const std::string path) {

    std::filesystem::directory_iterator all_files(path);
    for (auto file_path : all_files)
    {
      std::cout << "Texture : " << file_path << std::endl;
      textures_.emplace_back(file_path);
    }

    std::cout << "Loaded " << textures_.size() << " textures" << std::endl;

  }

  sf::Texture& GetRandomTexture() {

    std::cout << "Loaded " << textures_.size() << " textures" << std::endl;

    if (textures_.empty()) {
      std::cout << "what ???" << std::endl;
    }else {
      std::uniform_int_distribution<> texture_idx_dist_ = std::uniform_int_distribution<>(0, textures_.size() - 1);
      return textures_[texture_idx_dist_(gen_)];
    }

  }

};
#endif //TEXTURE_MANAGER_H
