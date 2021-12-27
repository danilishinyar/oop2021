#include <iostream>
#include "menu.h"

using namespace Menu;
int main(){
    LongNum a;
    std::cout << "Enter value:";
    getLongNum(a);
    menu(a);
    return 0;
}