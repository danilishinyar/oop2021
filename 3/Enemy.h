
#ifndef LAB3_REFACTORED_ENEMY_H
#define LAB3_REFACTORED_ENEMY_H
#include "Characteristics.h"
#include "Tile.h"
#include "Enemy_info.h"
#include "cmath"
#include "Item.h"

class Enemy {
private:
    Characteristics<std::string, float> tb;
    Tile tile;
    Enemy_info info;
    sf::Clock clock;
    std::string name;
    Item* item;
    char sign;
public:
    explicit Enemy(sf::Vector2f coords, char sign, const std::string& name, Item* item, sf::Texture* texture);
    void move(sf::Vector2f player_coords);
    Enemy(): tile(), tb(), info(), clock(), item(nullptr), sign() {};
    virtual ~Enemy() = default;
    Enemy(const Enemy& a);
    Enemy(Enemy&& a) noexcept;
    Enemy& operator=(const Enemy& a);
    Enemy& operator=(Enemy&& a) noexcept;
    Characteristics<std::string, float>& get_tb() { return this->tb; };
    float get_speed() { return this->tb.get_val("speed"); };
    float get_cur_hp() { return this->tb.get_val("cur_hp"); };
    float get_max_hp() { return this->tb.get_val("max_hp"); };
    float get_damage() { return this->tb.get_val("damage"); };
    float get_exp() { return  this->tb.get_val("exp"); }
    float get_hit_time() { return this->tb.get_val("hit_time"); };
    char get_sign() const { return this->sign; };
    std::string get_name() { return this->name; };
    Item* get_item() { return this->item; };
    Tile& get_tile() { return this->tile; };
    Enemy_info& get_info() { return this->info; };
    sf::Time get_clock() { return this->clock.getElapsedTime(); };
    sf::Vector2f get_coords() { return this->get_tile().get_coords(); };
    void restart_clock() { this->clock.restart(); };
    void set_hp(float hp) { this->tb.set("cur_hp", hp); };
    void set_speed(float speed) { this->tb.set("speed", speed); };
    void set_damage(float damage) { this->tb.set("damage", damage); };
    virtual void restart_affect_clock() = 0;
    virtual float get_affect_time() = 0;
    virtual bool check_is_expired() = 0;
    virtual void set_affect_state(bool a) = 0;
    void take_damage(float damage);
    virtual Enemy* clone() = 0;
};


class Enemy_human: public Enemy{
public:
    Enemy_human(sf::Vector2f coords, char sign, std::string name, Item* item, sf::Texture* texture):Enemy(coords, sign, name, item, texture){};
    Enemy_human* clone() override { return new Enemy_human(*this); };
    void restart_affect_clock() override {};
    float get_affect_time() override { return  0.f; };
    bool check_is_expired() override { return true; };
    void set_affect_state(bool a) override {};
    ~Enemy_human() override = default;
};


class Enemy_insect: public Enemy{//damage for 2 sec
private:
    sf::Clock affect_clock;
    bool affect_state;
public:
    Enemy_insect(sf::Vector2f coords, char sign, std::string name, Item* item, sf::Texture* texture):Enemy(coords, sign, name, item, texture){
      this->affect_state = false;
    };
    void set_affect_state(bool a) override { this->affect_state = a;}
    void restart_affect_clock() override { this->affect_clock.restart(); this->set_affect_state(true); };
    float get_affect_time() override { return this->get_tb().get_val("affect_time"); };
    bool check_is_expired() override { return affect_clock.getElapsedTime().asSeconds() <= this->get_affect_time() &&
                                              this->affect_state; };
    Enemy_insect* clone() override { return new Enemy_insect(*this); };
    ~Enemy_insect() override = default;
};


class Enemy_ice: public Enemy{//speed to 5
private:
    sf::Clock affect_clock;
    bool affect_state;
    bool worked_state;
    bool cancel_state;
public:
    Enemy_ice(sf::Vector2f coords, char sign, std::string name, Item* item, sf::Texture* texture):Enemy(coords, sign, name, item, texture){
        this->affect_state = false;
        this->worked_state = false;
        this->cancel_state = false;
    };
    void set_affect_state(bool a) override { this->affect_state = a;};
    void restart_affect_clock() override { this->affect_clock.restart(); this->set_affect_state(true); };
    float get_affect_time() override { return this->get_tb().get_val("affect_time"); };
    bool check_is_expired() override { return affect_clock.getElapsedTime().asSeconds() <= this->get_affect_time() &&
                                              this->affect_state; };
    void change_worked() {this->worked_state = true;};
    bool has_worked() const {return !worked_state;};
    bool is_cancelled() const {return !cancel_state;};
    void set_cancel(bool a){this->cancel_state = a;};
    float  get_affect_speed(){ return this->get_tb().get_val("affect_speed"); };
    Enemy_ice* clone() override { return new Enemy_ice(*this); };
    ~Enemy_ice() override = default;
};

#endif //LAB3_REFACTORED_ENEMY_H