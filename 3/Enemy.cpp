#include "Enemy.h"

Enemy::Enemy(sf::Vector2f coords, char sign, const std::string& name, Item* item, sf::Texture* texture): info(coords), tb("enemies/" +  name), name(name), item(item),
sign(sign), tile(coords, sf::Color(100, 100, 100), 2, texture){}


Enemy::Enemy(const Enemy& a){
    this->item = a.item->clone();
    this->tile = a.tile;
    this->tb = a.tb;
    this->clock = a.clock;
    this->name = a.name;
    this->info = a.info;
    this->sign = a.sign;
}


Enemy::Enemy(Enemy&& a)  noexcept {
    this->tile = a.tile;
    this->tb = a.tb;
    this->clock = a.clock;
    this->name = a.name;
    this->info = a.info;
    this->item = a.item;
    this->sign = a.sign;
    a.item = nullptr;
}


Enemy& Enemy::operator=(const Enemy& a) {
    if(this == &a)
        return *this;
    this->tile = a.tile;
    this->tb = a.tb;
    this->clock = a.clock;
    this->name = a.name;
    this->info = a.info;
    this->item = a.item;
    this->sign = a.sign;
    delete this->item;
    this->item = a.item->clone();
    return *this;
}


Enemy& Enemy::operator=(Enemy&& a)  noexcept {
    if(this == &a)
        return *this;
    this->tile = a.tile;
    this->tb = a.tb;
    this->clock = a.clock;
    this->name = a.name;
    this->info = a.info;
    this->item = a.item;
    this->item = a.item;
    this->sign = a.sign;
    a.item = nullptr;
    return *this;
}


void Enemy::move(sf::Vector2f player_coords) {
    sf::Vector2f dir;
    dir.x = - this->tile.get_rect().getPosition().x + player_coords.x;
    dir.y = - this->tile.get_rect().getPosition().y + player_coords.y;
    float hyp = sqrt( dir.x * dir.x + dir.y * dir.y );
    dir.x /= hyp;
    dir.y /= hyp;
    this->tile.get_rect().setPosition(this->tile.get_rect().getPosition().x
                                      + dir.x * this->get_speed(), this->tile.get_rect().getPosition().y + dir.y * this->get_speed());
    this->info.set_coords(sf::Vector2f (this->tile.get_rect().getPosition().x, this->tile.get_rect().getPosition().y - 20.f));
}


void Enemy::take_damage(float damage) {
    if(this->get_cur_hp() >= damage) {
        this->set_hp(this->get_cur_hp() - damage);
        this->get_info().set_width(this->get_cur_hp() / this->get_max_hp());
    }
    else{
        this->set_hp(0.f);
        this->get_info().set_width(0.f);
    }
}


