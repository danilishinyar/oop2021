#include "Enemy_info.h"


Enemy_info::Enemy_info(sf::Vector2f coords) {
    this->cur_health_bar = sf::RectangleShape(sf::Vector2f(100, 10));
    this->max_health_bar = sf::RectangleShape(sf::Vector2f(100, 10));
    this->cur_health_bar.setFillColor(sf::Color::Red);
    this->max_health_bar.setFillColor(sf::Color::Black);
    this->max_health_bar.setPosition(coords.x, coords.y - 20.f);
    this->cur_health_bar.setPosition(coords.x, coords.y - 20.f);
}
