#include "Menu.h"
#include "PCB.h"
using namespace Prog3_D;


int main(){
    Prog3_D::PCB a = PCB();
    Menu::menu(a);
    return 0;
}