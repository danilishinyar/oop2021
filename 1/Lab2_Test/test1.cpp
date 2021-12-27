#include "gtest/gtest.h"
#include "Cissoida.h"
#include <cmath>
#include <iostream>



TEST(CissoidaConstructor, DefaultConstructor){
    Line::Cissoida a1;
    ASSERT_EQ(1, a1.getA());
}


TEST(CissoidaConstructor, InitConstructor){
    Line::Cissoida a2(10);
    ASSERT_EQ(10, a2.getA());
}


TEST(CissoidaMethods, Setter){
    Line::Cissoida a1;
    ASSERT_EQ(1, a1.getA());
    a1.setA(15);
    ASSERT_EQ(15, a1.getA());
}


TEST(CissoidaMethods, Y_Coordinate){
    Line::Cissoida a1(3);
    const double err = 0.0001;
    ASSERT_ANY_THROW(a1.y_coordinate(-1));
    ASSERT_ANY_THROW(a1.y_coordinate(9));
    ASSERT_NEAR(0.447214, a1.y_coordinate(1), err);
    ASSERT_NEAR(3, a1.y_coordinate(3), err);
}

TEST(CissoidaMethods, PolarDistance){
    Line::Cissoida a1;
    const double err = 0.00001;
    ASSERT_NEAR(0, a1.polar_distance(0),err);
    ASSERT_NEAR(0, a1.polar_distance(M_PI),err);
    ASSERT_NEAR(1.4142135, a1.polar_distance(M_PI/4), err);
}

TEST(CissoidaMethods, AsymptoteCoefficient) {
    Line::Cissoida a1(3);
    ASSERT_EQ(6, a1.asymptote_coefficient());
    a1.setA(6);
    ASSERT_EQ(12, a1.asymptote_coefficient());
}


TEST(CissoidaMethods, CissoidaAsymptoteSectorArea) {
    Line::Cissoida a1(3);
    const double err = 0.00001;
    ASSERT_NEAR(84.823, a1.cissoida_asymptote_sector_area(), err);
    a1.setA(8);
    ASSERT_NEAR(603.18579, a1.cissoida_asymptote_sector_area(), err);
}



TEST(CissoidaMethods, Volume) {
    Line::Cissoida a1(3);
    const double err = 0.00001;
    ASSERT_NEAR(532.95864, a1.volume(), err);
}


TEST(CissoidaMethods, ParabolaCoefficient) {
    Line::Cissoida a1(3);
    ASSERT_EQ(-12, a1.parabola_coefficient());
    a1.setA(6);
    ASSERT_EQ(-24, a1.parabola_coefficient());
}


