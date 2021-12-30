
#ifndef LAB3_REFACTORED_LEVEL_H
#define LAB3_REFACTORED_LEVEL_H
#include "SFML/Graphics.hpp"
#include "Enemy.h"
#include "Item.h"
#include "texture_manager.h"

class Level {
private:
    std::vector<Enemy*> enemies;
    std::vector<std::vector<Tile>> map_tiles;
    std::string map_string;
    std::vector<Item*> items;
public:
    explicit Level(int n, Texture_manager& textures);
    Level() = default;
    Level(const Level& a);
    Level(Level&& a) noexcept;
    ~Level();
    int get_tile_type_by_coords(sf::Vector2f coords);
    void set_tile(Tile& tile);
    sf::Vector2f get_prowler_coords();
    std::vector<std::vector<Tile>>& get_map_tiles(){ return this->map_tiles; };
    std::vector<Enemy*>& get_enemies(){ return this->enemies; };
    std::vector<Item*>& get_items(){ return this->items; };

    __attribute__((unused)) Item* get_item_by_coords(sf::Vector2f coords);
};


#endif //LAB3_REFACTORED_LEVEL_H
