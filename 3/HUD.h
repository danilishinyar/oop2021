#ifndef LAB3_REFACTORED_HUD_H
#define LAB3_REFACTORED_HUD_H
#include "SFML/Graphics.hpp"
#include "Characteristics.h"
#include "Item.h"
class HUD {
private:
    std::string text;
    Characteristics<std::string, float>* tb;
public:
    explicit HUD(Characteristics<std::string, float>* tb);
    HUD();
    std::string get_text(Item* item);

};


#endif //LAB3_REFACTORED_HUD_H
