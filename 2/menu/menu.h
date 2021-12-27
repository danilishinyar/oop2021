#ifndef LONGNUM_MENU_MENU_H
#define LONGNUM_MENU_MENU_H

#include<iostream>
#include "LongNum.h"

namespace Menu {
    using namespace Num;
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



    void getLongNum(LongNum &a);
    void menu(LongNum &a);
    int dialog(int);
    void MenuGet(LongNum &a);
    void MenuAdditionalCode(LongNum &a);
    void MenuIncrease10times(LongNum &a);
    void MenuDecrease10times(LongNum &a);
    void MenuAdd(LongNum &a);
    void MenuSubtract(LongNum &a);
    void MenuEqual(LongNum &a);
}

#endif //LONGNUM_MENU_MENU_H
