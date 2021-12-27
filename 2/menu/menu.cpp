#include "menu.h"

namespace Menu {

    void getLongNum(LongNum &a){
        while(true){
            std::cin >> a;
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
                std::cout << "incorrect input" << std::endl << "try again" << std::endl;
            } else
                return;
        }
    }




    void menu(LongNum &a) {
        void (*fptr[])(LongNum &a) = {nullptr, MenuGet, MenuAdditionalCode, MenuIncrease10times,
                                      MenuDecrease10times, MenuAdd, MenuSubtract, MenuEqual};
        int rc = 1;
        while (rc) {
            rc = dialog(rc);
            fptr[rc](a);
        }
    }


    int dialog(int rc) {
        const char *msgs[] = {"0. Quit", "1. Get Num", "2. Additional code", "3. Increase 10 times",
                              "4. Decrease 10 times", "5. Add", "6. Subtract", "7. Equal"};
        const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
        const char *errmsg = "";
        int i;
        do {
            std::cout << errmsg << std::endl;
            errmsg = "You are wrong. Repeat, please!";
            for (i = 0; i < NMsgs; ++i)
                puts(msgs[i]);
            std::cout << "Make your choice: ";
            getNum(rc);
        } while (rc < 0 || rc >= NMsgs);
        return rc;
    }

    void MenuGet(LongNum &a) {
        std::cout << a;
    }

    void MenuAdditionalCode(LongNum &a) {
        int x = a.getLength();
        char *res = a.additional_code();
        for (int i = 0; i < x + 1; ++i)
            std::cout << res[i];
        std::cout << std::endl;
        delete[] res;
    }

    void MenuIncrease10times(LongNum &a) {
        try {
            a.increase_10_times();
        }
        catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << a;
    }

    void MenuDecrease10times(LongNum &a) {//add 0 check
        a.decrease_10_times();
        std::cout << a;
    }

    void MenuAdd(LongNum &a) {
        std::cout << "Enter another value:";
        LongNum b;
        try {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            std::cin >> b;
        }
        catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
        try {
            a = a + b;
        }
        catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << a;
    }

    void MenuSubtract(LongNum &a) {
        std::cout << "Enter another value:";
        LongNum b;
        try {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            std::cin >> b;
        }
        catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
        try {
            a = a - b;
        }
        catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << a;
    }

    void MenuEqual(LongNum &a) {
        std::cout << "Enter another value:";
        LongNum b;
        try {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            std::cin >> b;
        }
        catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
        a = b;
        std::cout << a;
    }
}

