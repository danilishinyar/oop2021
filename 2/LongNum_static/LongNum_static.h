#ifndef LONGNUM_STATIC_LONGNUM_STATIC_H
#define LONGNUM_STATIC_LONGNUM_STATIC_H

#include <iostream>
#include <cstring>
#include <cmath>
#define MAX 10

namespace Num_static {
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
        LongNum& equal(const LongNum &a);
        LongNum add(const LongNum &a);
        LongNum subtract(const LongNum &a);
        std::ostream& output(std::ostream &out) const;
        std::istream& input(std::istream &in);
    };
}

#endif //LONGNUM_STATIC_LONGNUM_STATIC_H
