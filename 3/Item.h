#ifndef LAB3_REFACTORED_ITEM_H
#define LAB3_REFACTORED_ITEM_H

#include <utility>

#include "Characteristics.h"
#include "Tile.h"
#include "Artifact.h"

/*!
 * \brief Родительский класс для предмета
 */
class Item {
private:
    Characteristics<std::string, float> tb; /// Таблица характеристик
    std::string name; /// Название предмета
    std::string description; /// Описание предмета
    Tile tile; /// Клетка для отображения на карте
public:
    Item():tb(), tile(Tile()) {}; /// Конструктор по умолчанию
    /*!
    \brief Конструктор Item'а
    \param name Назавание предмета
    \param description Описание предмета
    \param coords Координаты предмета на карте
    \param appendix Название папки с конфигурационными файлами
    */
    Item(std::string name, std::string description, sf::Vector2f coords, const std::string& appendix, sf::Texture* texture):  name(std::move(name)), description(std::move(description)), tile(coords, sf::Color::Black, 7,
                                                                                                                                                                         texture), tb(appendix + name){};
    Item(std::string name, std::string description, sf::Vector2f coords, sf::Texture* texture):  name(std::move(name)), description(std::move(description)), tile(coords, sf::Color::Black, 7,
                                                                                                                                                                  texture), tb(){};
    /*!
     * @return название предмета
     */
    std::string& get_name(){ return this->name; };
    /*!
     * @return описание предмета
     */
    std::string& get_description(){ return this->description; };
    /*!
     * @return таблицу характеристик
     */
    Characteristics<std::string, float>& get_tb(){ return this->tb; };
    /*!
     * @return клетку, отображаемую на игровой карте
     */
    Tile& get_tile() { return this->tile; };
    /*!
     * @return текст с характеристиками и описанием предмета
     */
    virtual std::string get_hud_text(){ return this->name; };
    /*!
     * \brief Клонирует объект
     */
    virtual Item* clone() = 0;
    virtual ~Item() = default;;
};



/*!
	\brief Дочерний класс Item'а

	Оружие
*/
class Weapon: public Item{
public:
    Weapon(): Item() {}; /// Конструктор по умолчанию
    /*!
    \brief Конструктор Weapon
    \param name Назавание оружия
    \param description Описание оружия
    \param coords Координаты оружия на карте
    */
    Weapon(const std::string& name, std::string description, sf::Vector2f coords, sf::Texture* texture): Item(name, std::move(description), coords, "weapon/",
                                                                                                              texture){
        if(!texture)
            this->get_tile().get_rect().setFillColor(sf::Color::Magenta);
        this->get_tile().set_type(8);
    };
    /*!
    * \brief Генерирует наносимый урон
    * @return урон
    */
    float get_damage() { return this->get_tb().get_val("damage_"); };
    /*!
    * @return текст с характеристиками и описанием предмета
    */
    std::string get_hud_text() override;
    /*!
    * \brief Клонирует объект
    */
    Weapon* clone() override{ return new Weapon(*this); };
    ~Weapon() override = default;
};

class Armor: public Item{
private:
    int type;/// Тип брони
public:
    Armor(): Item(), type(0) {};///Конструтор по умолчанию
    /*!
    \brief Конструктор Armor
    \param name Назавание брони
    \param description Описание брони
    \param coords Координаты брони на карте
    \param type Тип брони
    */
    Armor(const std::string& name, std::string description, sf::Vector2f coords, int type, sf::Texture* texture): Item(name, std::move(description), coords, "armor/",
                                                                                                                       texture
                                                                                                                  ), type(type){
        if(!texture)
            this->get_tile().get_rect().setFillColor(sf::Color::Yellow);
        this->get_tile().set_type(9);
    };
    /*!
    * \brief Генерирует сопротивление к атаке противника
    * @return сопротивление к атаке
    */
    float get_defence() {
        if(this->type == 0)
            return 0.f;
        else
            return this->get_tb().get_val("defence_");
    };
    /*!
    * @return тип брони
    */
    std::string get_hud_text() override;
    int get_type() const{ return this->type; };
    Armor* clone() override{ return new Armor(*this); };
    ~Armor() override = default;
};




class Potion: public Item{
private:
    int type; ///Тип зелья
    int state; ///Состояние зелья
    sf::Clock clock; /// Часы отсчета времени действия зелья
public:
    Potion(): Item(), type(0), state(0) {}; /// Конструктор по умолчанию
    /*!
    \brief Конструктор Potion
    \param name Назавание зелья
    \param description Описание зелья
    \param coords Координаты зелья на карте
    \param type Тип зелья
    */
    Potion(const std::string& name, std::string description, sf::Vector2f coords, int type, sf::Texture* texture): Item(name, std::move(description), coords, "potions/", texture), type(type), state(1) {
        if(!texture)
            this->get_tile().get_rect().setFillColor(sf::Color::Red);
        this->get_tile().set_type(10);
    };
    /*!
    * @brief Меняет состояние зелья на выпитое
    */
    void change_state(){this->state = 0;};
    /*!
    * @return тип зелья
    */
    int get_type() const{ return this->type; };
    /*!
    * @return время действия
    */
    float get_time() { return this->get_tb().get_val("time"); };
    /*!
    * @return 1 если время действия зелья истекло
    */
    bool check_is_expired(){ return this->clock.getElapsedTime().asSeconds() >= this->get_time() && this->get_time() != 0.f && this->state == 0; }
    /*!
    * @return величину параметра, на который действует зелье
    */
    float get_param();
    /*!
    * @brief Меняет величину параметра, на который действует зелье
    */
    void set_param(float a);
    /*!
    * @brief Сбрасывает часы отсчета действия зелья
    */
    void restart_clock() { this->clock.restart(); };
    /*!
    * @return текст с описанием и характеристиками зелья
    */
    std::string get_hud_text() override;
    /*!
    * @return клон объекта
    */
    Potion* clone() override{ return new Potion(*this); };
    ~Potion() override = default;
};


class Artifact_armor: public Armor, public Artifact{
public:
    Artifact_armor(const std::string& name, std::string description, sf::Vector2f coords, int type, sf::Texture* texture): Armor(name, std::move(description), coords, type, texture) {};

    Artifact_armor* clone() override{ return new Artifact_armor(*this); }
};


class Artifact_weapon: public virtual Weapon, public Artifact{
public:
    Artifact_weapon(const std::string& name, std::string description, sf::Vector2f coords, sf::Texture* texture): Weapon(name, std::move(description), coords, texture) {};
    Artifact_weapon* clone() override{ return new Artifact_weapon(*this); }
};


class Enchanted_weapon: public virtual Weapon{
private:
    char buf_enemy_type;
    char debuf_enemy_type;
public:
    Enchanted_weapon(const std::string& name, std::string description, sf::Vector2f coords, char buf, char debuf, sf::Texture* texture): Weapon(name, std::move(description), coords, texture),
    buf_enemy_type(buf), debuf_enemy_type(debuf) {};
    char get_buf_type() const{ return this->buf_enemy_type; };
    char get_debuf_type() const{ return this->debuf_enemy_type; };
    float get_buf_damage(){ return this->get_tb().get_val("buf_damage"); };
    float get_debuf_damage(){ return this->get_tb().get_val("debuf_damage"); };
    Enchanted_weapon* clone() override{ return new Enchanted_weapon(*this); };
};

class E_A_weapon: public virtual Enchanted_weapon, public virtual Artifact_weapon{
public:
    E_A_weapon(const std::string& name, const std::string& description, sf::Vector2f coords, char buf, char debuf, sf::Texture* texture): Weapon(name, description, coords, texture),
                                                                                                            Artifact_weapon(name, description, coords, texture),
                                                                                                            Enchanted_weapon( name, description, coords, buf, debuf, texture){};
    E_A_weapon* clone() override{ return new E_A_weapon(*this); };
};



class Door: public Item{
public:
    Door(sf::Vector2f coords, sf::Texture* texture): Item("door", "locked", coords, texture){};
    std::string get_hud_text() override;
    Door* clone() override{ return new Door(*this); };
};


class Lockpick: public Item{
public:
    Lockpick(sf::Vector2f coords, sf::Texture* texture): Item("lockpick", "you can open door\nwith me", coords, texture){};
    Lockpick* clone() override{ return new Lockpick(*this); };
};

#endif //LAB3_REFACTORED_ITEM_H