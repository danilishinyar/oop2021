#include "Item.h"

std::string Weapon::get_hud_text() {
std::string s = this->get_name() + "\n";
s += this->get_description();
return s;
}

std::string Potion::get_hud_text() {
std::string s = this->get_name() + "\n";
s += this->get_description();
return s;
}

std::string Armor::get_hud_text() {
    std::string s = this->get_name() + "\n";
    s += this->get_description();
    return s;
}

std::string Door::get_hud_text() {
    return "door\nlocked";
}

float Potion::get_param() {
    if(this->type == 0)
        return this->get_tb().get_val("hp");
    if(this->type == 1)
        return this->get_tb().get_val("speed");
    return 0.f;
};
void Potion::set_param(float a) {
    if(this->type == 0)
        return this->get_tb().set("hp", a);
    if(this->type == 1)
        return this->get_tb().set("speed", a);
};