#ifndef LAB3_REFACTORED_TEXTURE_MANAGER_H
#define LAB3_REFACTORED_TEXTURE_MANAGER_H
#include "SFML/Graphics.hpp"
#include "map"
#include "string"
#include <random>
#include <filesystem>

class Texture_manager {
private:
    std::map<std::string, sf::Texture*> textures;
public:
    Texture_manager();
    ~Texture_manager();
    Texture_manager(const Texture_manager& a);
    Texture_manager(Texture_manager&& a);
    sf::Texture* get_floor_texture();
    sf::Texture* get_wall_texture();
    sf::Texture* get_enemy_texture(char sign);
    sf::Texture* get_texture_by_string(std::string name);
    sf::Texture* get_prowler_texture();
    sf::Texture* get_potion_texture(int type);
};


#endif //LAB3_REFACTORED_TEXTURE_MANAGER_H
