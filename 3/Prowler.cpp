#include "Prowler.h"

Prowler::Prowler(sf::Texture* texture): tb("prowler"){
    this->weapon = nullptr;
    this->helmet = nullptr;
    this->chest = nullptr;
    this->legs = nullptr;
    this->feet = nullptr;
    this->rect = sf::RectangleShape(sf::Vector2f(100, 100));
    this->texture = texture;
    this->rect.setTexture(this->texture);
    this->frame = sf::IntRect(0, 0, 16, 16);
    this->rect.setTextureRect(this->frame);
    this->sign = '@';
    this->clock = sf::Clock();
}


void Prowler::set_armor_head(Armor* armor){
    this->helmet = armor;
}

void Prowler::set_armor_chest(Armor* armor){
    this->chest = armor;
}

void Prowler::set_armor_legs(Armor* armor){
    this->legs = armor;
}

void Prowler::set_armor_feet(Armor* armor){
    this->feet = armor;
}


void Prowler::take_damage(Enemy* enemy) {
    this->set_cur_hp(this->get_cur_hp() - enemy->get_damage() * (1 - this->get_defence()/100));
}

void Prowler::set_weapon(Weapon* weapon1) {
    this->weapon = weapon1;
}

void Prowler::generate_damage() {
    this->set_damage(this->weapon->get_damage() * static_cast<float>(this->get_level() * 1.2) + this->get_damage('\0'));
}

void Prowler::calculate_total_defence() {
    this->set_defence(static_cast<float>(this->get_defence_helmet() * 0.5
    + this->get_defence_chest() * 0.7
    + this->get_defence_legs() * 0.3
    + this->get_defence_feet() * 0.2));
}

Item* Prowler::equip_item(Item* item){
    if(dynamic_cast<Artifact*>(item)){
        auto *tmp_a = dynamic_cast<Artifact*>(item);
        tmp_a->activate(this->get_characteristics(),item->get_tb());
    }
    if(dynamic_cast<Weapon*>(item)) {
        if(this->weapon != nullptr) {
            if(dynamic_cast<Artifact*>(this->weapon)) {
                auto* tmp_w = this->weapon;
                dynamic_cast<Artifact*>(this->weapon)->deactivate(this->get_characteristics(), this->weapon->get_tb());
                this->default_damage();
                this->set_weapon(dynamic_cast<Weapon*>(item));
                this->generate_damage();
                return tmp_w;
            }
            else {
                auto* tmp_w = this->weapon;
                this->default_damage();
                this->set_weapon(dynamic_cast<Weapon*>(item));
                this->generate_damage();
                return tmp_w;
            }
        }
        else {
            this->set_weapon(dynamic_cast<Weapon*>(item));
            this->generate_damage();
        }
    }
    if(typeid(*item) == typeid(Potion)){
        auto* tmp = dynamic_cast<Potion *>(item);
        this->potions.push_back(*tmp);
        if(tmp->get_type() == 0)
            this->increase_hp_potions();
        if(tmp->get_type() == 1)
            this->increase_speed_potions();
    }
    if(dynamic_cast<Armor*>(item)){
        switch (dynamic_cast<Armor*>(item)->get_type()){
            case 1: {
                if(this->helmet != nullptr) {
                    if(dynamic_cast<Artifact*>(this->helmet)) {
                        auto* tmp_a = this->helmet;
                        dynamic_cast<Artifact*>(this->helmet)->deactivate(this->get_characteristics(), this->helmet->get_tb());
                        this->set_armor_head(dynamic_cast<Armor*>(item));
                        this->calculate_total_defence();
                        return tmp_a;
                    }
                    else {
                        auto* tmp_a = this->helmet;
                        this->set_armor_head(dynamic_cast<Armor*>(item));
                        this->calculate_total_defence();
                        return tmp_a;
                    }
                }
                else {
                    this->set_armor_head(dynamic_cast<Armor*>(item));
                    this->calculate_total_defence();
                }
                break;
            }
            case 2:
                if(this->chest != nullptr) {
                    if(dynamic_cast<Artifact*>(this->chest)) {
                        auto* tmp_a = this->chest;
                        dynamic_cast<Artifact *>(this->chest)->deactivate(this->get_characteristics(), this->chest->get_tb());
                        this->set_armor_head(dynamic_cast<Armor*>(item));
                        this->calculate_total_defence();
                        return tmp_a;
                    }
                    else {
                        auto* tmp_a = this->chest;
                        this->set_armor_head(dynamic_cast<Armor*>(item));
                        this->calculate_total_defence();
                        return tmp_a;
                    }
                }
                else {
                    this->set_armor_chest(dynamic_cast<Armor*>(item));
                    this->calculate_total_defence();
                }
                break;
            case 3:
                if(this->legs != nullptr) {
                    if(dynamic_cast<Artifact*>(this->legs)) {
                        auto* tmp_a = this->legs;
                        dynamic_cast<Artifact*>(this->legs)->deactivate(this->get_characteristics(), this->legs->get_tb());
                        this->set_armor_head(dynamic_cast<Armor*>(item));
                        this->calculate_total_defence();
                        return tmp_a;
                    }
                    else {
                        auto* tmp_a = this->legs;
                        this->set_armor_head(dynamic_cast<Armor*>(item));
                        this->calculate_total_defence();
                        return tmp_a;
                    }
                }
                else {
                    this->set_armor_legs(dynamic_cast<Armor*>(item));
                    this->calculate_total_defence();
                }
                break;
            case 4:
                if(this->feet != nullptr) {
                    if(dynamic_cast<Artifact*>(this->feet)) {
                        auto* tmp_a = this->feet;
                        dynamic_cast<Artifact *>(this->feet)->deactivate(this->get_characteristics(), this->feet->get_tb());
                        this->set_armor_head(dynamic_cast<Armor*>(item));
                        this->calculate_total_defence();
                        return tmp_a;
                    }
                    else {
                        auto tmp_a = this->feet;
                        this->set_armor_head(dynamic_cast<Armor*>(item));
                        this->calculate_total_defence();
                        return tmp_a;
                    }
                }
                else {
                    this->set_armor_feet(dynamic_cast<Armor*>(item));
                    this->calculate_total_defence();
                }
                break;
        }
    }
    if(dynamic_cast<Lockpick*>(item)){
        this->increase_lockpicks();
    }
    return nullptr;
}

void Prowler::drink_potion(int type) {
    if(type == 0){
        this->decrease_hp_potions();
        for(auto & potion : this->potions){
            if(potion.get_type() == 0) {
                if (this->get_cur_hp() + potion.get_param() < this->get_max_hp())
                    this->set_cur_hp(this->get_cur_hp() + potion.get_param());
                else
                    this->set_cur_hp(this->get_max_hp());
                potion.change_state();
            }
        }
    }
    if(type == 1){
        this->decrease_speed_potions();
        for(auto & potion : this->potions){
            if(potion.get_type() == 1) {
                potion.restart_clock();
                potion.change_state();
                this->set_speed(this->get_speed() + potion.get_param());
            }
        }
    }
}


void Prowler::take_affect(Enemy* enemy) {
    if(typeid(*enemy) == typeid(Enemy_insect)){
        auto* tmp = dynamic_cast<Enemy_insect *>(enemy);
        if(tmp->check_is_expired())
            this->set_cur_hp(this->get_cur_hp() - enemy->get_damage());
        else
            tmp->set_affect_state(false);
    }
    if(typeid(*enemy) == typeid(Enemy_ice)){
        auto* tmp = dynamic_cast<Enemy_ice *>(enemy);
        if(tmp->check_is_expired()) {
            if(tmp->has_worked()) {
                tmp->change_worked();
                this->set_speed(this->get_speed() - tmp->get_affect_speed());
            }
        }
        else {
            tmp->set_affect_state(false);
            if(tmp->is_cancelled() && !tmp->has_worked()) {
                this->set_speed(this->get_speed() + tmp->get_affect_speed());
                tmp->set_cancel(true);
            }
        }
    }
}

float Prowler::get_damage(char sign_) {
    auto* tmp_w = dynamic_cast<Enchanted_weapon*>(this->weapon);
    if(tmp_w) {
        if (tmp_w->get_buf_type() == sign_) {
            return this->get_characteristics().get_val("damage") + tmp_w->get_buf_damage();
        }
        if (tmp_w->get_debuf_type() == sign_)
            return this->get_characteristics().get_val("damage") - tmp_w->get_debuf_damage();
    }
    return this->get_characteristics().get_val("damage");
}


void Prowler::cancel_affect(Enemy *enemy) {
    if(typeid(*enemy) == typeid(Enemy_ice)){
        auto* tmp = dynamic_cast<Enemy_ice *>(enemy);
        this->set_speed(this->get_speed() + tmp->get_affect_speed());
        tmp->set_cancel(true);
    }
}


