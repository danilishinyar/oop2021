#ifndef LIB_LIBRARY_H
#define LIB_LIBRARY_H

#include <iostream>
#include <cmath>

namespace Line{
    //Циссоида Диокла определятся следующим образом: в декартовой системе координат на оси OX выбирается точка A, на ОА как на диаметре строится окружность С и проводится через A касательная UV.
    //Через O проводится произвольная прямая OF, пересекающая UV в точке F и пересекающая (вторично) окружность в точке E.
    //На данной прямой от F по направлению к О откладывается отрезок FM, равный хорде OE.
    //Линия, описываемая точкой M при вращении OF около O, дает искомую кривую.
    class Cissoida{
    private:
        //длина отрезка ОА
        double a;
    public:
        //конструктор
        explicit Cissoida(double a1 = 1);
        //сеттер
        void setA(double a1);
        //геттер
        double getA() const;
        //Вернуть координату y в декартовой системе координат, принадлежащую циссоиде в зависимости от x.
        double y_coordinate(double x) const;
        //Вернуть расстояние до центра в полярной системе координат в зависимости от угла.
        double polar_distance(double angle) const;
        //Вернуть коэффициент в уравнении асимптоты UV.
        double asymptote_coefficient() const;
        //Вернуть площадь полосы между циссоидой и ее асимптотой.
        double cissoida_asymptote_sector_area() const;
        //Вернуть объем тела, полученной вращением полосы из пункта 6 вокруг асимптоты UV.
        double volume() const;
        //Вернуть коэффициенты в уравнении параболы такой, что основания перпендикуляров, опущенных из вершины параболы на ее касательные, образуют данную циссоиду.
        double parabola_coefficient() const;
    };
}
#endif //LIB_LIBRARY_H
