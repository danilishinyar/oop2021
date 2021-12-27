
#include "HUD.h"

HUD::HUD(Characteristics<std::string, float>* tb) {
    this->tb = tb;
    for(auto & i : *tb){
        this->text += i.title + ": ";
        this->text += std::to_string(i.value) + "\n";
    }
}

std::string HUD::get_text(Item* item) {
    this->text = "";
    for(auto & i : *tb){
        this->text += i.title + ": ";
        this->text += std::to_string(i.value) + "\n";
    }
    if(item != nullptr) {
        this->text += "\nitem: " + item->get_name() + "\n";
        this->text += "description: " + item->get_description() + "\n\n";
        for (auto &i: item->get_tb()) {
            this->text += i.title + ": ";
            this->text += std::to_string(i.value) + "\n";
        }
    }
    return this->text;
}