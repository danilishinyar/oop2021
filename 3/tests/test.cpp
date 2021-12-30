#include "gtest/gtest.h"
#include "../Characteristics.h"
#include <iostream>
#include "../Prowler.h"

TEST(Prowler_constructor, Constructor){
    Prowler prowler;
    EXPECT_EQ(120.f, prowler.get_max_hp());
    EXPECT_EQ(120.f, prowler.get_cur_hp());
    EXPECT_EQ(7.f, prowler.get_damage());
    EXPECT_EQ(1.f,prowler.get_level());
    EXPECT_EQ(0.f,prowler.get_exp());
    EXPECT_EQ(100.f,prowler.get_exp_level());
    EXPECT_EQ(0.f,prowler.get_hp_potions());
    EXPECT_EQ(0.f,prowler.get_speed_potions());
    EXPECT_EQ(20.f, prowler.get_speed());
}

TEST(Prowler_lvlup, Lvlup){
    Prowler prowler;
    prowler.increase_level(10);
    EXPECT_EQ(1.f,prowler.get_level());
    EXPECT_EQ(10.f,prowler.get_exp());
    EXPECT_EQ(100.f,prowler.get_exp_level());
    prowler.increase_level(100);
    EXPECT_EQ(2.f,prowler.get_level());
    EXPECT_EQ(110.f,prowler.get_exp());
    EXPECT_EQ(200.f,prowler.get_exp_level());
}


TEST(Prowler_equip_item, Items){
    Prowler prowler;
    Weapon sword("sword", "just sword", sf::Vector2f(0.f, 0.f));
    prowler.equip_item(&sword);
    //EXPECT_EQ(sword, prowler.get_weapon());
    EXPECT_EQ(10.5, prowler.get_damage());
    Potion hp_potion("hp_potion", "increases hp", sf::Vector2f(0.f, 0.f), 0);
    Potion speed_potion("speed_potion", "increases speed", sf::Vector2f(0.f, 0.f), 1);
    prowler.equip_item(&hp_potion);
    prowler.equip_item(&speed_potion);
    EXPECT_EQ(1.f, prowler.get_hp_potions());
    EXPECT_EQ(1.f, prowler.get_speed_potions());
}


TEST(Prowler_drink_potion, Potion){
    Prowler prowler;
    Potion hp_potion("hp_potion", "increases hp", sf::Vector2f(0.f, 0.f), 0);
    Potion speed_potion("speed_potion", "increases speed", sf::Vector2f(0.f, 0.f), 1);
    prowler.equip_item(&hp_potion);
    prowler.equip_item(&speed_potion);
    prowler.drink_potion(0);
    EXPECT_EQ(120.f, prowler.get_cur_hp());
    prowler.drink_potion(1);
    EXPECT_EQ(30.f, prowler.get_speed());
    EXPECT_EQ(0.f, prowler.get_hp_potions());
    EXPECT_EQ(0.f, prowler.get_speed_potions());
}


TEST(Prowler_take_damage, Combat){
    Prowler prowler;
    Weapon sword("sword", "just sword", sf::Vector2f(0.f, 0.f));
    Enemy enemy(sf::Vector2f(0.f, 0.f), 'z', "zombie", &sword);
    prowler.take_damage(enemy);
    EXPECT_EQ(105.f, prowler.get_cur_hp());
    prowler.take_damage(enemy);
    prowler.take_damage(enemy);
    prowler.take_damage(enemy);
    prowler.take_damage(enemy);
    prowler.take_damage(enemy);
    prowler.take_damage(enemy);
    prowler.take_damage(enemy);
    prowler.take_damage(enemy);
    EXPECT_EQ(0, prowler.is_alive());
}


TEST(Weapon_constructor, Items){
    Weapon sword("axe", "just axe", sf::Vector2f(0.f, 0.f));
    EXPECT_EQ(20.f, sword.get_damage());
    EXPECT_EQ("just axe", sword.get_description());
    EXPECT_EQ("axe", sword.get_name());
}


TEST(Potion_constructor, Items){
    Potion hp_potion("hp_potion", "increases hp", sf::Vector2f(0.f, 0.f), 0);
    Potion speed_potion("speed_potion", "increases speed", sf::Vector2f(0.f, 0.f), 1);
    EXPECT_EQ("hp_potion", hp_potion.get_name());
    EXPECT_EQ("speed_potion", speed_potion.get_name());
    EXPECT_EQ("increases hp", hp_potion.get_description());
    EXPECT_EQ("increases speed", speed_potion.get_description());
    EXPECT_EQ(100.f, hp_potion.get_param());
    EXPECT_EQ(10.f, speed_potion.get_param());
}



TEST(Enemy_constructor, Constructor){
    Weapon sword("sword", "just sword", sf::Vector2f(0.f, 0.f));
    Enemy enemy(sf::Vector2f(0.f, 0.f), 'z', "zombie", &sword);
    EXPECT_EQ(30.f, enemy.get_max_hp());
    EXPECT_EQ(30.f, enemy.get_cur_hp());
    EXPECT_EQ(15.f, enemy.get_damage());
    EXPECT_EQ(100.f, enemy.get_exp());
}


TEST(Enemy_take_damage, Combat){
    Weapon sword("sword", "just sword", sf::Vector2f(0.f, 0.f));
    Enemy enemy(sf::Vector2f(0.f, 0.f), 'z', "zombie", &sword);
    EXPECT_EQ(30.f, enemy.get_cur_hp());
    enemy.take_damage(10.f);
    EXPECT_EQ(20.f, enemy.get_cur_hp());
    enemy.take_damage(100000.f);
    EXPECT_EQ(0.f, enemy.get_cur_hp());
}


int main(int argc, char* argv[] ){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}