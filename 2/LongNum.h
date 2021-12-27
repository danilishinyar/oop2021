#ifndef LONGNUM_LONGNUM_H
#define LONGNUM_LONGNUM_H

#include<iostream>
#include <cstring>
#include <cmath>


namespace Num {

    class LongNum {
    private:
        int length;
        char* digits;
    public:
        LongNum() noexcept;
        LongNum(long num);
        LongNum(const char* num);
        LongNum(const LongNum &a) noexcept;
        LongNum(LongNum &&a) noexcept;
        ~LongNum() noexcept;
        [[nodiscard]] char* getDigits() const noexcept;
        [[nodiscard]] int getLength() const noexcept{
            return length;
        };
        [[nodiscard]] char* additional_code() const;
        void increase_10_times();
        void decrease_10_times() noexcept;
        LongNum& operator=(LongNum &&a) noexcept;
        LongNum operator+(const LongNum &a) const;
        LongNum operator-(const LongNum &a) const;
        LongNum& operator=(const LongNum &a);
        static char* back_from_additional(char* res, int length_r);
        static char* rm_zeroes(char* res, int &length_r);
        static char* char_sum_pos(LongNum &a, const LongNum &b, int length_r);
        static char* char_sum_neg(LongNum &a, const LongNum &b, int length_r);
        static char* char_subtract(const char* n, const char* p, int length_p, int length_n, int length_r);
        friend std::ostream& operator<<(std::ostream &out, const LongNum &a);
        friend std::istream& operator>>(std::istream &in, LongNum &a);
    };
}

#endif //LONGNUM_LONGNUM_H