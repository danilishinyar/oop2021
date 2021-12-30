
#ifndef LAB3_REFACTORED_GAME_MANAGER_H
#define LAB3_REFACTORED_GAME_MANAGER_H
#include "SFML/Graphics.hpp"
#include "Prowler.h"
#include "level.h"
#include "time.h"
#include "HUD.h"
#include "texture_manager.h"

class Game_manager {
private:
    Texture_manager textures;
    sf::Clock clock1;
    //prowler
    Prowler prowler;
    //levels
    std::vector<Level> levels;
    //cur level
    int cur_level;
    //game window
    sf::RenderWindow window;
    sf::View game_view;
    sf::View hud_view;
    //keys
    HUD hud;
    bool UP;
    bool DOWN;
    bool LEFT;
    bool RIGHT;
    bool HIT;
    bool INTERACT;
    bool OPEN;
    bool NUM1;
    bool NUM2;
    void handle_input(sf::Keyboard::Key key, bool is_pressed);
public:
    Game_manager();
    ~Game_manager() = default;
    Item* player_near_item();
    void choose_event();//chooses what to do (close/press/release key)
    void update_player(sf::Time deltaTime);//updating movement and etc
    void update_enemy(sf::Time deltaTime);//updating movement and etc
    void render();//prints all stuff
    void run();
    void change_level();
    void equip_item();
    void open_door();
};


#endif //LAB3_REFACTORED_GAME_MANAGER_H
