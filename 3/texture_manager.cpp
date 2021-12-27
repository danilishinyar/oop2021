#include "texture_manager.h"

Texture_manager::Texture_manager() {
    std::string path = "/Users/danilishinyar/OOP/lab3_refactored/conf/textures";
    for (const auto & entry : std::__fs::filesystem::directory_iterator(path)) {
        auto *tmp = new sf::Texture();
        std::string tmp_path = entry.path();
        tmp->loadFromFile(tmp_path);
        this->textures.insert({tmp_path.substr(tmp_path.find_last_of("/\\") + 1),
                              tmp});
    }
}


Texture_manager::~Texture_manager() {
    auto it = this->textures.begin();
    while(it != this->textures.end()){
        delete it->second;
        it++;
    }
}

sf::Texture* Texture_manager::get_floor_texture() {
    int i = 1 + (rand() % static_cast<int>(4));
    return this->textures["floor_" + std::to_string(i) + ".png"];
}

sf::Texture* Texture_manager::get_wall_texture() {
    int i = 1 + (rand() % static_cast<int>(2));
    return this->textures["wall_" + std::to_string(i) + ".png"];
}

sf::Texture *Texture_manager::get_prowler_texture() {
    return this->textures["prowler.png"];
}

sf::Texture *Texture_manager::get_potion_texture(int type) {
    return this->textures["potion_" + std::to_string(type) + ".png"];
}

sf::Texture *Texture_manager::get_texture_by_string(std::string name) {
    return this->textures[name + ".png"];
}


