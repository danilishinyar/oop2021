#include "Cissoida.h"
namespace Line{

    Cissoida::Cissoida(double a1) {
        a = a1;
    }

    void Cissoida::setA(double a1) {
        a = a1;
    }

    double Cissoida::getA() const{
        return a;
    }

    double Cissoida::y_coordinate(double x) const {
        if ((x * a < 0)  || std::abs(x) > std::abs(a))
            throw std::runtime_error("invalid x");
        if (x * a >= 0){
            double r = pow(x, 3) / (2 * a - x);
            return sqrt(r);
        }
    }

    double Cissoida::polar_distance(double angle) const {
        return 2 * a * pow(sin(angle), 2) / cos(angle);
    }

    double Cissoida::asymptote_coefficient() const {
        return 2 * a;
    }

    double  Cissoida::cissoida_asymptote_sector_area() const {
        return 3 * pow(a, 2) * M_PI;
    }

    double Cissoida::volume() const {
        return 2 * pow(M_PI, 2) * pow(a, 3);
    }

    double Cissoida::parabola_coefficient() const {
        return -4 * a;
    }

}
