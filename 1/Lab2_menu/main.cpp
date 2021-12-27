#include <iostream>
#include "menu.h"



int main(){
    double a;
    std::cout << "Enter a:" << std::endl;
    Menu::getNum(a);
    Line::Cissoida x(a);
    Menu::menu(x);
    return 0;
}