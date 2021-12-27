//
// Created by yaroslav on 22.09.2021.
//

#ifndef LAB2_OOP_MENU_H
#define LAB2_OOP_MENU_H

#include<iostream>
#include "Cissoida.h"

namespace Menu {

    template<class T>
    void getNum(T &a) {
        while (true) {
            if(std::cin.eof())
                throw std::runtime_error("EOF");
            std::cin >> a;
            if (!std::cin.good()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                std::cout << "incorrect input" << std::endl << "try again" << std::endl;
            } else
                return;
        }
    }


    void menu(Line::Cissoida &x);
    int dialog(int);
    void MenuGetA(Line::Cissoida &x);
    void MenuSetA(Line::Cissoida &x);
    void MenuY_coordinate(Line::Cissoida &x);
    void MenuPolar_distance(Line::Cissoida &x);
    void MenuAsymptote_coefficient(Line::Cissoida &x);
    void MenuCissoida_asymptote_sector_area(Line::Cissoida &x);
    void MenuVolume(Line::Cissoida &x);
    void MenuParabola_coefficient(Line::Cissoida &x);


}
#endif //LAB2_OOP_MENU_H
