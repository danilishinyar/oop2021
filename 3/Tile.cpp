#include "Tile.h"


Tile::Tile(sf::Vector2f coords, sf::Color color, int type, sf::Texture* texture) {
    this->is_animated = false;
    this->rect = sf::RectangleShape(sf::Vector2f(100, 100));
    if(texture) {
        this->rect.setTexture(texture);
        if(texture->getSize().x != texture->getSize().y) {
            this->frame = sf::IntRect(0, 0, this->rect.getTexture()->getSize().x/(this->rect.getTexture()->getSize().x/this->rect.getTexture()->getSize().y), texture->getSize().y);
            this->rect.setTextureRect(this->frame);
            this->is_animated = true;
        }
    }
    else {
        this->rect.setFillColor(color);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(1);
    }
    this->rect.setPosition(coords.x * 100, coords.y * 100);
    this->coords.x *= 100;
    this->coords.y *= 100;
    this->type = type;
    this->clock = sf::Clock();
}

Tile::Tile(){
    this->coords = {0.f, 0.f};
    this->rect = sf::RectangleShape(sf::Vector2f(100, 100));
    this->rect.setFillColor(sf::Color::Green);
    this->type = 0;
    this->clock = sf::Clock();
}

void Tile::animate() {
        if (this->is_animated) {
                if (this->frame.left == this->rect.getTexture()->getSize().x - this->rect.getTexture()->getSize().y) {
                    this->frame.left -= this->rect.getTexture()->getSize().x - this->rect.getTexture()->getSize().y;
                }
                else
                    this->frame.left += this->rect.getTexture()->getSize().x /
                                        (this->rect.getTexture()->getSize().x / this->rect.getTexture()->getSize().y);
                this->rect.setTextureRect(this->frame);
        }
}
