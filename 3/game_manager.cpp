#include "game_manager.h"

Game_manager::Game_manager(): window(sf::VideoMode(1500, 1000), "game"), textures(), prowler(this->textures.get_prowler_texture()), hud(&this->prowler.get_characteristics()){
    std::ifstream file;
    int i = 1;
    while(true){
        file.open("/Users/danilishinyar/OOP/lab3_refactored/conf/levels/" + std::to_string(i) + ".txt");
        if(file.is_open()){
            this->levels.emplace_back(i, this->textures);
            i++;
            file.close();
        }
        else
            break;
    }
    this->game_view = sf::View();
    this->game_view.setViewport(sf::FloatRect(0.f, 0.f, 0.6f, 1.f));
    this->hud_view = sf::View();
    this->hud_view.setViewport(sf::FloatRect(0.6f, 0.f, 0.8f, 1.f));
    this->UP = false;
    this->DOWN = false;
    this->LEFT = false;
    this->RIGHT = false;
    this->HIT = false;
    this->INTERACT = false;
    this->OPEN = false;
    this->NUM1 = false;
    this->NUM2 = false;
    this->cur_level = 0;
    this->prowler.set_coords(this->levels[this->cur_level].get_prowler_coords());

}

void Game_manager::render() {
    this->window.clear();
    this->window.setView(this->game_view);
    if(this->prowler.get_elapsed_time() > sf::seconds(1.f/10.f).asSeconds()) {
        if (this->prowler.get_frame().left == 16 * 4)
            this->prowler.get_frame().left -= 16 * 4;
        else
            this->prowler.get_frame().left += 16;
        this->prowler.get_rect().setTextureRect(this->prowler.get_frame());
        this->prowler.restart_clock();
    }
    for(auto & i : this->levels[this->cur_level].get_map_tiles())//map
        for(auto & j : i){
           this->window.draw(j.get_rect());
       }
    for(auto & i : this->levels[this->cur_level].get_enemies()) {//enemies
        this->window.draw(i->get_tile().get_rect());
        this->window.draw(i->get_info().get_max_hp());
        this->window.draw(i->get_info().get_cur_hp());
        if (i->get_tile().get_elapsed_time() > sf::seconds(1.f / 10.f).asSeconds()) {
            i->get_tile().animate();
            i->get_tile().restart_clock();
        }
    }
    for(auto & i : this->levels[this->cur_level].get_items()) {//item
        this->window.draw(i->get_tile().get_rect());
    }
    this->window.draw(prowler.get_rect());//player
    this->game_view.setCenter(this->prowler.get_coords());
    sf::Font font;
    this->window.setView(this->hud_view);
    if(!font.loadFromFile("/Users/danilishinyar/OOP/lab3_refactored/conf/OpenSans-Bold.ttf"))
        throw std::exception();
    sf::Text text(this->hud.get_text(this->player_near_item()),font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition({0.f, 0.f});
    this->window.draw(text);
    this->window.display();
}




void Game_manager::update_player(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (UP)
        if (this->levels[this->cur_level].get_tile_type_by_coords({this->prowler.get_rect().getPosition().x + 99.f, this->prowler.get_rect().getPosition().y - static_cast<float>(0.5)}) > 0
            && this->levels[this->cur_level].get_tile_type_by_coords({this->prowler.get_rect().getPosition().x, this->prowler.get_rect().getPosition().y - static_cast<float>(0.5)}) > 0)
            movement.y -= this->prowler.get_speed();
    if (DOWN)
        if (this->levels[this->cur_level].get_tile_type_by_coords({this->prowler.get_rect().getPosition().x + 99.f, this->prowler.get_rect().getPosition().y + 99.f + static_cast<float>(0.5)}) > 0
            && this->levels[this->cur_level].get_tile_type_by_coords({this->prowler.get_rect().getPosition().x, this->prowler.get_rect().getPosition().y + 99.f + static_cast<float>(0.5)}) > 0)
            movement.y += this->prowler.get_speed();
    if (LEFT)
        if (this->levels[this->cur_level].get_tile_type_by_coords({this->prowler.get_rect().getPosition().x - static_cast<float>(0.01), this->prowler.get_rect().getPosition().y}) > 0
            && this->levels[this->cur_level].get_tile_type_by_coords({this->prowler.get_rect().getPosition().x - static_cast<float>(0.01), this->prowler.get_rect().getPosition().y + 99.f}) > 0)
            movement.x -= this->prowler.get_speed();
    if (RIGHT)
        if (this->levels[this->cur_level].get_tile_type_by_coords({this->prowler.get_rect().getPosition().x + 99.f + static_cast<float>(0.5), this->prowler.get_rect().getPosition().y}) > 0
            && this->levels[this->cur_level].get_tile_type_by_coords({this->prowler.get_rect().getPosition().x + 99.f + static_cast<float>(0.5), this->prowler.get_rect().getPosition().y + 99.f}) > 0)
            movement.x += this->prowler.get_speed();
    if (HIT && !this->levels[this->cur_level].get_enemies().empty()) {
        for (int i = 0; i < this->levels[this->cur_level].get_enemies().size(); i++) {
            if (this->levels[this->cur_level].get_enemies()[i]->get_cur_hp() <= 0) {
                this->prowler.increase_level(this->levels[this->cur_level].get_enemies()[i]->get_exp());
                this->levels[this->cur_level].get_enemies()[i]->get_item()->get_tile().set_coords(this->levels[this->cur_level].get_enemies()[i]->get_coords());
                this->levels[this->cur_level].get_items().push_back(this->levels[this->cur_level].get_enemies()[i]->get_item());
                this->prowler.cancel_affect(this->levels[this->cur_level].get_enemies()[i]);
                this->levels[this->cur_level].get_enemies().erase(this->levels[this->cur_level].get_enemies().begin() + i);
                continue;
            }
            if (sqrt(pow(this->levels[this->cur_level].get_enemies()[i]->get_tile().get_rect().getPosition().x - this->prowler.get_rect().getPosition().x, 2) +
                     pow(this->levels[this->cur_level].get_enemies()[i]->get_tile().get_rect().getPosition().y - this->prowler.get_rect().getPosition().y, 2)) <= 200.f)
                this->levels[this->cur_level].get_enemies()[i]->take_damage(this->prowler.get_damage(this->levels[this->cur_level].get_enemies()[i]->get_sign()));

        }
        HIT = false;
    }
    if (INTERACT) {
        this->change_level();
        this->equip_item();

    }
    if(OPEN){
        this->open_door();
    }
    if(NUM1){
        this->prowler.drink_potion(0);
        NUM1 = false;
    }
    if(NUM2){
        this->prowler.drink_potion(1);
        NUM2 = false;
    }
    this->prowler.get_rect().move(movement * deltaTime.asSeconds());
    for(int i = 0; i < this->prowler.get_potions().size(); i++){
        if(this->prowler.get_potions()[i].check_is_expired()) {
            this->prowler.cancel_potion(i, 1);
            this->prowler.get_potions().erase(this->prowler.get_potions().begin() + i);
        }
    }
    if(LEFT) {
        this->prowler.get_frame().top = 3 * 16;
    }
    if(RIGHT) {
        this->prowler.get_frame().top = 16;
    }
    if(UP) {
        this->prowler.get_frame().top = 0;
    }
    if(DOWN) {
        this->prowler.get_frame().top = 2 * 16;
    }
    if(!(UP || RIGHT || LEFT || DOWN)){
        this->prowler.get_frame().top = 0;
    }
}

void Game_manager::update_enemy(sf::Time deltaTime) {
    for(auto & i : this->levels[this->cur_level].get_enemies()) {
        sf::Vector2f tmp = i->get_tile().get_rect().getPosition();
        if ((this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x + 100.f, i->get_tile().get_rect().getPosition().y}) > 0//up
             && this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x  , i->get_tile().get_rect().getPosition().y}) > 0)
            &&
            (this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x , i->get_tile().get_rect().getPosition().y + 100.f}) > 0//down
             && this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x + 100.f , i->get_tile().get_rect().getPosition().y + 100.f}) > 0)
            &&
            (this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x , i->get_tile().get_rect().getPosition().y}) > 0//left
             && this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x , i->get_tile().get_rect().getPosition().y + 100.f}) > 0)
            &&
            (this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x + 100.f , i->get_tile().get_rect().getPosition().y}) > 0//right
             && this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x + 100.f , i->get_tile().get_rect().getPosition().y + 100.f}) > 0))
            i->move(this->prowler.get_coords());

        else {
            bool up_left = this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x, i->get_tile().get_rect().getPosition().y}) == 0;//up_left

            bool down_left = this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x, i->get_tile().get_rect().getPosition().y + 100.f}) == 0;//down_left


            bool up_right = this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x + 100.f, i->get_tile().get_rect().getPosition().y}) == 0;//up_right


            bool down_right = this->levels[this->cur_level].get_tile_type_by_coords({i->get_tile().get_rect().getPosition().x + 100.f , i->get_tile().get_rect().getPosition().y + 100.f}) == 0;//down_right


            if(up_left) {
                tmp.y += 3.f;
                tmp.x += 3.f;
            }
            if(down_left) {
                tmp.y -= 3.f;
                tmp.x += 3.f;
            }
            if(up_right) {
                tmp.x -= 3.f;
                tmp.y += 3.f;
            }
            if(down_right) {
                tmp.x -= 3.f;
                tmp.y -= 3.f;
            }
            if(up_left && up_right){
                tmp.y += 3.f;
            }
            if(up_left && down_left){
                tmp.x += 3.f;
            }
            if(up_right && down_right){
                tmp.x -= 3.f;
            }
            if(down_left && down_right){
                tmp.y -= 3.f;
            }
            i->move(tmp);
        }
    }
    for(auto & i : this->levels[this->cur_level].get_enemies()) {
        this->prowler.take_affect(i);
        if (sqrt(pow(i->get_tile().get_rect().getPosition().x - this->prowler.get_rect().getPosition().x, 2) +
        pow(i->get_tile().get_rect().getPosition().y - this->prowler.get_rect().getPosition().y, 2)) <= 100.f) {
            sf::Time time = i->get_clock();
                if(time.asSeconds() >= sf::seconds(i->get_hit_time()).asSeconds()) {
                    this->prowler.take_damage(i);
                    i->restart_affect_clock();
                    i->restart_clock();
                    break;
                }
        }
    }

}

void Game_manager::change_level() {
    if(this->levels[this->cur_level].get_tile_type_by_coords(this->prowler.get_coords()) == 4){
        if(INTERACT) {
            this->cur_level++;
            INTERACT = false;
        }
    }
    if(this->levels[this->cur_level].get_tile_type_by_coords(this->prowler.get_coords()) == 5){
        if(INTERACT) {
            this->cur_level--;
            INTERACT = false;
        }
    }
}

void Game_manager::equip_item() {
    for(int i = 0; i < this->levels[this->cur_level].get_items().size(); ++i){
        if (sqrt(pow(this->levels[this->cur_level].get_items()[i]->get_tile().get_rect().getPosition().x - this->prowler.get_rect().getPosition().x, 2) +
                 pow(this->levels[this->cur_level].get_items()[i]->get_tile().get_rect().getPosition().y - this->prowler.get_rect().getPosition().y, 2)) <= 100.f){
            if(INTERACT && !dynamic_cast<Door*>(*(this->levels[this->cur_level].get_items().begin() + i))) {
                Item* tmp = this->prowler.equip_item(this->levels[this->cur_level].get_items()[i]);
                this->levels[this->cur_level].get_items().erase(this->levels[this->cur_level].get_items().begin() + i);
                if(tmp) {
                    this->levels[this->cur_level].get_items().push_back(tmp);
                    tmp->get_tile().set_coords(this->prowler.get_coords());
                }
            }
        }
    }
}

void Game_manager::choose_event() {
    sf::Event event{};
    while(this->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                handle_input(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handle_input(event.key.code, false);
            default:
                continue;
        }
    }
}

void Game_manager::handle_input(sf::Keyboard::Key key, bool is_pressed) {
    if(key == sf::Keyboard::W)
        this->UP = is_pressed;
    if(key == sf::Keyboard::A)
        this->LEFT = is_pressed;
    if(key == sf::Keyboard::S)
        this->DOWN = is_pressed;
    if(key == sf::Keyboard::D)
        this->RIGHT = is_pressed;
    if(key == sf::Keyboard::H)
        this->HIT = is_pressed;
    if(key == sf::Keyboard::I)
        this->INTERACT = is_pressed;
    if(key == sf::Keyboard::O)
        this->OPEN = is_pressed;
    if(key == sf::Keyboard::Num1)
        this->NUM1 = is_pressed;
    if(key == sf::Keyboard::Num2)
        this->NUM2 = is_pressed;
}

void Game_manager::run() {
    sf::Time time = sf::seconds(1.f / 60.f);
    while(this->window.isOpen() && this->prowler.is_alive()) {
        choose_event();
        update_enemy(time);
        update_player(time);
        render();
    }
}


Item* Game_manager::player_near_item() {
    for(auto & i : this->levels[this->cur_level].get_items()){
        if (sqrt(pow(i->get_tile().get_rect().getPosition().x - this->prowler.get_rect().getPosition().x, 2) +
                 pow(i->get_tile().get_rect().getPosition().y - this->prowler.get_rect().getPosition().y, 2)) <= 100.f)
        return i;
    }
    return nullptr;
}

void Game_manager::open_door() {
    for(int i = 0; i < this->levels[this->cur_level].get_items().size(); ++i){
        if (sqrt(pow(this->levels[this->cur_level].get_items()[i]->get_tile().get_rect().getPosition().x - this->prowler.get_rect().getPosition().x, 2) +
                 pow(this->levels[this->cur_level].get_items()[i]->get_tile().get_rect().getPosition().y - this->prowler.get_rect().getPosition().y, 2)) <= 100.f){
            if(OPEN && dynamic_cast<Door*>(*(this->levels[this->cur_level].get_items().begin() + i))) {
                sf::Vector2f f = sf::Vector2f(this->levels[this->cur_level].get_items()[i]->get_tile().get_coords().x/100, this->levels[this->cur_level].get_items()[i]->get_tile().get_coords().y/100);
                this->levels[this->cur_level].get_items().erase(this->levels[this->cur_level].get_items().begin() + i);
                Tile sq = Tile(f, sf::Color::Green, 1, textures.get_floor_texture());
                this->levels[this->cur_level].set_tile(sq);
                this->prowler.decrease_lockpicks();
            }
        }
    }
}