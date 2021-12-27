#ifndef LAB3_REFACTORED_ITEM_H
#define LAB3_REFACTORED_ITEM_H

#include "Characteristics.h"
#include "Tile.h"

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
    Item(std::string name, std::string description, sf::Vector2f coords, const std::string& appendix):  name(std::move(name)), description(std::move(description)), tile(coords, sf::Color::Black, 7), tb(appendix + name){};
    /*!
     * @return название предмета
     */
    std::string get_name(){ return this->name; };
    /*!
     * @return описание предмета
     */
    std::string get_description(){ return this->description; };
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
    Weapon(const std::string name, std::string description, sf::Vector2f coords): Item(name, std::move(description), coords, "weapon/"){
        this->get_tile().get_rect().setFillColor(sf::Color::Magenta);
        this->get_tile().set_type(8);
    };
    /*!
    * \brief Генерирует наносимый урон
    * @return урон
    */
    float get_damage() { return this->get_tb().get_val("damage"); };
    /*!
    * @return текст с характеристиками и описанием предмета
    */
    std::string get_hud_text() override;
    /*!
    * \brief Клонирует объект
    */
    Weapon* clone() override{ return new Weapon(*this); };
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
    Armor(const std::string name, std::string description, sf::Vector2f coords, int type): Item(name, std::move(description), coords, "armor/"), type(type){
        this->type = static_cast<int>(this->get_tb().get_val("type"));
        this->get_tile().get_rect().setFillColor(sf::Color::Yellow);
        this->get_tile().set_type(9);
    };
    /*!
    * \brief Генерирует сопротивление к атаке противника
    * @return сопротивление к атаке
    */
    float get_defence() { return this->get_tb().get_val("defence"); };
    /*!
    * @return тип оружия
    */
    int get_type() const{ return this->type; };
};




class Potion: public Item{
private:
    int type; ///Тип зелья
    int state; ///Состояние зелья
    sf::Clock clock; /// Часы отсчета времени действия зелья
public:
    Potion(): Item(), type(0), state(1) {}; /// Конструктор по умолчанию
    /*!
    \brief Конструктор Potion
    \param name Назавание зелья
    \param description Описание зелья
    \param coords Координаты зелья на карте
    \param type Тип зелья
    */
    Potion(const std::string name, std::string description, sf::Vector2f coords, int type): Item(name, std::move(description), coords, "potions/"), type(type), state(1) {
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
    void cancel_potion();
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
};



#endif //LAB3_REFACTORED_ITEM_H