#include "menu.h"

namespace Menu {

    void menu(Line::Cissoida &x) {
        void (*fptr[])(Line::Cissoida &x) = {nullptr, MenuGetA, MenuSetA, MenuY_coordinate, MenuPolar_distance,
                                             MenuAsymptote_coefficient, MenuCissoida_asymptote_sector_area, MenuVolume,
                                             MenuParabola_coefficient};
        int rc = 1;
        while (rc) {
            rc = dialog(rc);
            fptr[rc](x);
        }
    }


    int dialog(int rc) {
        const char *msgs[] = {"0. Quit", "1. Get A", "2. Set A", "3. Y coordinate", "4. Polar distance",
                              "5. Asymptote coefficient", "6. Asymptote sector area", "7. Volume",
                              "8. Parabola coefficient"};
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

    void MenuGetA(Line::Cissoida &x) {
        std::cout << "Value of a:";
        std::cout << x.getA() << std::endl;
    }

    void MenuSetA(Line::Cissoida &x) {
        double m;
        std::cout << "Enter new value of a:";
        getNum(m);
        x.setA(m);
    }

    void MenuY_coordinate(Line::Cissoida &x) {
        double m;
        std::cout << "Enter x coordinate:";
        getNum(m);
        try {
            std::cout << "Y Coordinate: " << x.y_coordinate(m) << std::endl;
        }
        catch (std::runtime_error &e){
            std::cout << e.what() << std::endl;
        }
    }

    void MenuPolar_distance(Line::Cissoida &x) {
        double m;
        std::cout << "Enter angle:";
        getNum(m);
        std::cout << x.polar_distance(m) << std::endl;
    }

    void MenuAsymptote_coefficient(Line::Cissoida &x) {
        std::cout << "Asymptote coefficient:" << x.asymptote_coefficient() << std::endl;
    }

    void MenuCissoida_asymptote_sector_area(Line::Cissoida &x) {
        std::cout << "Cissoida Asymptote Sector area:" << x.cissoida_asymptote_sector_area() << std::endl;
    }

    void MenuVolume(Line::Cissoida &x) {
        std::cout << "Volume: " << x.volume() <<  std::endl;
    }

    void MenuParabola_coefficient(Line::Cissoida &x) {
        std::cout << "Parabola coefficient:" << x.parabola_coefficient() << std::endl;
    }


}
