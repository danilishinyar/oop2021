#include "level.h"

Level::Level(int n, Texture_manager& textures) {
    std::ifstream file;
    std::string line;
    file.open("/Users/danilishinyar/OOP/lab3_refactored/conf/levels/" + std::to_string(n) + ".txt");
    int j = 0;
    if(file.is_open()){
        while(getline(file, line)){
            this->map_string += line;
            std::vector<Tile> v;
            for(int i = 0; i < line.size(); ++i){
                switch(line[i]){
                    case '#': {//wall
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color::Black, 0, textures.get_wall_texture());
                        v.push_back(sq);
                        break;
                    }
                    case '.':{//void
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color::Green, 1, textures.get_floor_texture());
                        v.push_back(sq);
                        break;
                    }
                    case '@':{//void
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color::Green, 1, textures.get_floor_texture());
                        v.push_back(sq);
                        break;
                    }
                    case 'z':{//enemy
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color(0, 255, 0), 1, textures.get_floor_texture());
                        auto* sword = new Weapon("sword", "", sf::Vector2f(static_cast<float>(i), static_cast<float>(j)),
                                                 textures.get_texture_by_string("sword"));
                        auto* zombie = new Enemy_human(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), 'z', "zombie", sword, textures.get_texture_by_string("zombie"));
                        this->enemies.push_back(zombie);
                        v.push_back(sq);
                        break;
                    }
                    case 'f':{//enemy insect
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color(0, 255, 0), 1, textures.get_floor_texture());
                        auto* axe = new E_A_weapon("e_a_axe", "more damage on\ninsects\nless on zombies", sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), 'f', 'z', textures.get_texture_by_string("e_a_axe"));
                        auto* fly = new Enemy_insect(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), 'f', "fly", axe, textures.get_texture_by_string("fly"));
                        this->enemies.push_back(fly);
                        v.push_back(sq);
                        break;
                    }
                    case 'g':{//golem
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color(0, 255, 0), 1, textures.get_floor_texture());
                        auto* chest = new Artifact_armor("artifact_chest", "just chest", sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), 2, textures.get_texture_by_string("artifact_chest"));
                        auto* ice_golem = new Enemy_ice(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), 'f', "ice_golem", chest, textures.get_texture_by_string("ice_golem"));
                        this->enemies.push_back(ice_golem);
                        v.push_back(sq);
                        break;
                    }
                    case 'h':{//hp_potion
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color(0, 255, 0), 1, textures.get_floor_texture());
                        auto* potion = new Potion("hp_potion", "increases hp", sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), 0, textures.get_potion_texture(0));
                        this->items.push_back(dynamic_cast<Item*>(potion));
                        v.push_back(sq);
                        break;
                    }
                    case 's':{//speed_potion
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color(0, 255, 0), 1, textures.get_floor_texture());
                        auto* potion = new Potion("speed_potion", "increases speed", sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), 1, textures.get_potion_texture(1));
                        this->items.push_back(dynamic_cast<Item*>(potion));
                        v.push_back(sq);
                        break;
                    }
                    case 'i':{//in
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color::Cyan, 4, textures.get_texture_by_string("stairs_up"));
                        v.push_back(sq);
                        break;
                    }
                    case 'o':{//out
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color::Transparent, 5,
                                textures.get_texture_by_string("stairs_down"));
                        v.push_back(sq);
                        break;
                    }
                    case 'd':{//door
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color::Black, 0, textures.get_wall_texture());
                        auto* door = new Door(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), textures.get_texture_by_string("door"));
                        this->items.push_back(dynamic_cast<Item*>(door));
                        v.push_back(sq);
                        break;
                    }
                    case 'l':{//door
                        Tile sq(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), sf::Color::Green, 1, textures.get_floor_texture());
                        auto* lockpick = new Lockpick(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)), textures.get_texture_by_string("lockpick"));
                        this->items.push_back(dynamic_cast<Item*>(lockpick));
                        v.push_back(sq);
                        break;
                    }
                    default:
                        continue;
                }
            }
            this->map_tiles.push_back(v);
            j++;
        }
    }
}



int Level::get_tile_type_by_coords(sf::Vector2f coords) {
    int a = static_cast<int>(coords.x) / 100;
    int b = static_cast<int>(coords.y) / 100;
    return this->map_tiles[b][a].get_type();
}



sf::Vector2f Level::get_prowler_coords() {
    for(int i = 0; i < this->map_tiles.size(); i++)
        for(int j = 0; j < this->map_tiles[i].size(); j++)
            if(this->map_string[i * this->map_tiles.size() + j] == '@')
                return {static_cast<float>(j) * 100.f, static_cast<float>(i) * 100.f};
    return sf::Vector2f{0.f, 0.f};
}

Item* Level::get_item_by_coords(sf::Vector2f coords) {
    for(auto &i: this->items){
        int a = static_cast<int>(i->get_tile().get_coords().x) / 100;
        int b = static_cast<int>(i->get_tile().get_coords().y) / 100;
        if(static_cast<int>(coords.x) / 100 == a && static_cast<int>(coords.y) / 100 == b)
            return i;
    }
    return nullptr;
}

Level::Level(Level&& a) noexcept{
    this->map_tiles = a.map_tiles;
    this->map_string = a.map_string;
    for(auto &i: a.items){
        Item* tmp = i->clone();
        this->items.push_back(tmp);
    }
    for(auto &i: a.items)
        delete i;
    a.items.clear();
    for(auto &i: a.enemies){
        Enemy* tmp = i->clone();
        this->enemies.push_back(tmp);
    }
    for(auto &i: a.enemies)
        delete i;
    a.enemies.clear();
}

Level::~Level(){
    for(auto & item : this->items) {
        auto tmp = item;
        delete tmp;
    }
    this->items.clear();
    for(auto & enemy : this->enemies) {
        auto tmp = enemy;
        delete tmp;
    }
    this->enemies.clear();
}

Level::Level(const Level& a){
    for(auto &i: a.enemies){
        Enemy* tmp = i->clone();
        this->enemies.push_back(tmp);
    }
    this->map_tiles = a.map_tiles;
    this->map_string = a.map_string;
    for(auto &i: a.items){
        Item* tmp = i->clone();
        this->items.push_back(tmp);
    }
}

void Level::set_tile(Tile& tile) {
    for(int i = 0; i < this->map_tiles.size(); i++)
        for(int j = 0; j < this->map_tiles[i].size(); j++) {

            if (this->map_tiles[i][j].get_coords() == tile.get_coords()) {
                this->map_tiles[i][j] = tile;
            }
        }
}
