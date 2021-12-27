#ifndef LAB3_REFACTORED_PROWLER_H
#define LAB3_REFACTORED_PROWLER_H
#include <typeinfo>
#include "Characteristics.h"
#include "SFML/Graphics.hpp"
#include "Item.h"
#include "Enemy.h"
#include "HUD.h"



class Prowler{
private:
    Characteristics<std::string, float> tb;
    Weapon* weapon;
    Armor* helmet;
    Armor* chest;
    Armor* legs;
    Armor* feet;
    std::vector<Potion> potions;
    sf::RectangleShape rect;
    char sign;
    sf::Texture* texture;
    sf::IntRect frame;
    sf::Clock clock;
public:
    Prowler(sf::Texture* texture);
    Prowler() = default;
    //Accessors
    sf::RectangleShape& get_rect(){ return this->rect; };
    Characteristics<std::string, float>& get_characteristics() { return this->tb; }
    float get_cur_hp(){ return this->tb.get_val("cur_hp"); };
    float get_max_hp(){ return this->tb.get_val("max_hp"); };
    float get_speed(){ return this->tb.get_val("speed"); };
    float get_lucky(){ return this->tb.get_val("lucky"); };
    float get_damage(char sign);
    int get_level(){ return static_cast<int>(this->tb.get_val("level")); };
    float get_exp(){ return this->tb.get_val("exp"); };
    int get_exp_level(){  return static_cast<int>(this->tb.get_val("exp_level")); };
    float get_defence_helmet(){
        if(this->helmet)
            return this->helmet->get_defence();
        else
            return 0.f;
    };
    float get_defence_chest(){
        if(this->chest)
            return this->chest->get_defence();
        else
            return 0.f;
    };
    float get_defence_legs(){
        if(this->legs)
            return this->legs->get_defence();
        else
            return 0.f;
    };
    float get_defence_feet(){
        if(this->feet)
            return this->feet->get_defence();
        else
            return 0.f;
    };
    sf::Vector2f get_coords(){ return this->rect.getPosition(); };
    char get_sign() const{ return this->sign; };
    std::vector<Potion>& get_potions(){ return this->potions; };
    float get_hp_potions() { return this->tb.get_val("hp_potions"); };
    float get_speed_potions() { return this->tb.get_val("speed_potions"); };
    float get_defence() { return this->tb.get_val("defence"); };
    float get_lockpicks() { return this->tb.get_val("lockpicks"); };
    sf::IntRect& get_frame() { return this->frame; };
    Weapon* get_weapon() { return this->weapon; };

    //Modifiers

    void set_cur_hp(float cur_hp){ this->tb.set("cur_hp", cur_hp); };
    void set_damage(float damage){ this->tb.set("damage", damage); };
    void set_speed(float speed){ this->tb.set("speed", speed); };
    void set_lucky(float lucky){ this->tb.set("lucky", lucky); };
    void set_defence(float def){ this->tb.set("defence", def); };
    void set_weapon(Weapon* weapon1);
    void default_damage(){ this->set_damage(this->get_damage('\0') - this->weapon->get_damage() * 1.2 * this->get_level()); };
    void increase_hp_potions(){ this->tb.set("hp_potions", this->get_hp_potions()+1); };
    void decrease_hp_potions(){
        if(this->get_hp_potions() != 0.f) {
            this->tb.set("hp_potions", this->get_hp_potions() - 1);
        }
    };
    void increase_speed_potions(){ this->tb.set("speed_potions", this->get_speed_potions()+1); };
    void decrease_speed_potions(){
        if(this->get_speed_potions() != 0.f) {
            this->tb.set("speed_potions", this->get_speed_potions() - 1);
        }
    };
    void set_armor_head(Armor* armor);
    void set_armor_chest(Armor* armor);
    void set_armor_legs(Armor* armor);
    void set_armor_feet(Armor* armor);
    void increase_exp(float exp){ this->tb.set("exp", this->tb.get_val("exp") + exp); };
    void increase_level(float exp){
        this->increase_exp(exp);
        if(this->get_exp() >= static_cast<float>(this->get_exp_level())) {
            this->tb.set("exp_level", this->tb.get_val("exp_level") * 2);
            this->tb.set("level", this->tb.get_val("level") + 1);
            this->tb.set("damage", this->tb.get_val("damage") * static_cast<float>(1.2));
        }
    };
    void set_coords(sf::Vector2f coords1){ this->rect.setPosition(coords1); };

    //Funcs

    Item* equip_item(Item* item);
    void drink_potion(int type);
    void cancel_potion(int i, int type){
        if(type == 0){
            this->set_cur_hp(this->get_cur_hp() - this->potions[i].get_param());
        }
        if(type == 1){
            this->set_speed(this->get_speed() - this->potions[i].get_param());
        }
    }
    void take_damage(Enemy* enemy);
    void take_affect(Enemy* enemy);
    void cancel_affect(Enemy* enemy);
    bool is_alive(){ return this->get_cur_hp() > 0; };
    void calculate_total_defence();
    void generate_damage();
    ~Prowler(){
        delete weapon;
        delete helmet;
        delete chest;
        delete legs;
        delete feet;
    };
    float get_elapsed_time() { return this->clock.getElapsedTime().asSeconds() ;};
    void restart_clock() { this->clock.restart(); }
    void decrease_lockpicks() {
        if(this->get_lockpicks() > 0)
            this->tb.set("lockpicks", this->get_lockpicks() - 1);
    };
    void increase_lockpicks(){
        this->tb.set("lockpicks", this->get_lockpicks() + 1);
    }
};



#endif //LAB3_REFACTORED_PROWLER_H

