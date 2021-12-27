#ifndef LAB3_REFACTORED_TILE_H
#define LAB3_REFACTORED_TILE_H
#include "SFML/Graphics.hpp"

class Tile {
private:
    sf::Vector2f coords;
    sf::RectangleShape rect;
    int type;//0-field 1-wall 2-enemy
    sf::IntRect frame;
    bool is_animated;
    sf::Clock clock;
public:
    Tile(sf::Vector2f coords, sf::Color color, int type, sf::Texture* texture);
    Tile();//default field tile constructor
    //getters
    sf::Vector2f get_coords(){ return this->rect.getPosition(); };
    sf::RectangleShape& get_rect(){ return this->rect; };
    int get_type() const{ return this->type; };
    bool get_animated() { return this->is_animated; };
    //setters
    void set_coords(sf::Vector2f coords1){ this->rect.setPosition(coords1); };
    void set_type(int i){ this->type = i; };
    void animate();
    float get_elapsed_time() { return this->clock.getElapsedTime().asSeconds() ;};
    void restart_clock() { this->clock.restart(); }
};


#endif //LAB3_REFACTORED_TILE_H
