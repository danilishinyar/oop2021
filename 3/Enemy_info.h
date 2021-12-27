#ifndef LAB3_REFACTORED_ENEMY_INFO_H
#define LAB3_REFACTORED_ENEMY_INFO_H
#include "SFML/Graphics.hpp"

class Enemy_info {
private:
    sf::RectangleShape cur_health_bar;
    sf::RectangleShape max_health_bar;
public:
    Enemy_info():cur_health_bar(), max_health_bar() {};
    explicit Enemy_info(sf::Vector2f coords);
    //Enemy_info();
    sf::RectangleShape get_cur_hp() { return this->cur_health_bar; };
    sf::RectangleShape get_max_hp() { return this->max_health_bar; };

    void set_coords(sf::Vector2f coords){
        this->max_health_bar.setPosition(coords.x, coords.y - 20.f);
        this->cur_health_bar.setPosition(coords.x, coords.y - 20.f);
    };
    void set_width(float delta_width){
        this->cur_health_bar.setSize(sf::Vector2f(100.f * delta_width, this->cur_health_bar.getSize().y));
    };

};


#endif //LAB3_REFACTORED_ENEMY_INFO_H
