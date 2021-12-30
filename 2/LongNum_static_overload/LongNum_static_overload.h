#ifndef LONGNUM_STATIC_LONGNUM_STATIC_OVERLOAD_H
#define LONGNUM_STATIC_LONGNUM_STATIC_OVERLOAD_H

#include <iostream>
#include <cstring>
#include <cmath>
#define MAX 10
/*
 * Длинное число хрантися в прямом коде (-11 = 911, 22 = 022)
 */
namespace Num_static_overload {
    class LongNum {
    private:
        int length;
        char dights[MAX];
    public:
        LongNum();
        explicit LongNum(long num);
        explicit LongNum(const char* num);
        LongNum(const LongNum &a);
        [[nodiscard]] const char* getDights() const{
            char* res = new char[length + 1];
            memcpy(res, dights, length + 1);
            return res;
        };
        [[nodiscard]] int getLength() const {
            return length;
        };
        [[nodiscard]] char* additional_code() const;
        void increase_10_times();
        void decrease_10_times();
        LongNum& operator=(const LongNum &a);
        LongNum operator+(const LongNum &a) const;
        LongNum operator-(const LongNum &a) const;
        friend std::ostream& operator<<(std::ostream &out, const LongNum& a);
        friend std::istream& operator>>(std::istream &in, LongNum& a);
    };
}

#endif //LONGNUM_STATIC_LONGNUM_STATIC_OVERLOAD_H
