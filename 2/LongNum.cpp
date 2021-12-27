#include "LongNum.h"



namespace Num {
    LongNum::LongNum() noexcept{
        length = 1;
        digits = new char[3];
        digits[0] = '0';
        digits[1] = '0';
        digits[2] = '\0';
    }

    LongNum::LongNum(long num) {
        if (num == 0) {
            *this = LongNum();
            return;
        }
        length = 0;
        long n = std::abs(num);
        while (n > 0) {
            length++;
            n = n / 10;
        }
        long num1 = num;
        try {
            digits = new char[length + 2];
        }
        catch (std::bad_alloc &e) {
            throw std::runtime_error("Allocation failed");
        }
        if (num1 >= 0)
            digits[0] = '0';
        else
            digits[0] = '9';
        num1 = std::abs(num);
        for (int i = 1; i < length + 1; ++i) {
            digits[i] =  (num1 / static_cast<long>(pow(10, length - i)) + 48);
            double k = pow(10, length - i);
            num1 = num1 % static_cast<long>(k);
        }
        digits[length + 1] = '\0';
    }

    LongNum::LongNum(const char *num) {
        int j = 0;
        while(num[j] != '\0'){
            if(!(num[j] == '-' || (num[j] <= '9' && num[j] >= '0')))
                throw std::runtime_error("invalid input");
            j++;
        }
        if (num[0] == '-' && num[1] == '0') {
            *this = LongNum();
            return;
        }
        if (num[0] == '-') {
            length = 0;
            while (num[length] != '\0')
                length++;
            length--;
            try {
                digits = new char[length + 2];
            }
            catch (std::bad_alloc &e) {
                throw std::runtime_error("Allocation failed");
            }
            std::memcpy(digits, num, length + 1);
            digits[0] = '9';
        } else {
            length = 0;
            while (num[length] != '\0')
                length++;
            try {
                digits = new char[length + 2];
            }

            catch (std::bad_alloc &e) {
                throw std::runtime_error("Allocation failed");
            }
            for (int i = 1; i < length + 1; ++i)
                digits[i] = num[i-1];
            digits[0] = '0';
            digits[length + 1] = '\0';
        }
        this->digits = rm_zeroes(this->digits, length);
    }

    LongNum::LongNum(const LongNum &a) noexcept {
        length = a.length;
        digits = new char[a.length + 2];
        memcpy(digits, a.digits, a.length + 2);
    }


    LongNum::~LongNum() noexcept{
        delete[] digits;
    }

    char* LongNum::getDigits() const noexcept{
        char* res = new char[length + 2];
        for(int i = 0; i < length + 1; ++i)
            res[i] = digits[i];
        res[length+1] = '\0';
        return res;
    }

    char* LongNum::additional_code() const {
        char *res;
        res = new char[length + 2];
        res[0] = digits[0];
        if (digits[0] == '9') {
            for (int i = 1; i < length + 1; ++i)
                res[i] = 9 - digits[i] + 2 * 48;
            int k = 1;
            for (int i = 0; i < length; ++i) {
                res[length] = res[length] + k;
                k = 0;
                if (res[length - i] > '9') {
                    k = 1;
                    res[length - i] = '0';
                    res[length - i - 1] = res[length - i - 1] + k;
                    k = 0;
                }
            }
        } else {
            for (int i = 0; i < length + 1; ++i)
                res[i] = digits[i];
        }
        res[length + 1] = '\0';
        return res;
    }

    void LongNum::increase_10_times() {
        length++;
        char *res;
        try {
            res = new char[length + 2];
        }
        catch (std::bad_alloc &e) {
            throw std::runtime_error("Allocation failed");
        }
        for (int i = 0; i < length; ++i)
            res[i] = digits[i];
        res[length] = '0';
        res[length + 1] = '\0';
        delete[] digits;
        digits = res;
    }

    void LongNum::decrease_10_times() noexcept {
        if(length > 1) {
            length--;
            char *res = new char[length + 2];
            for (int i = 0; i < length + 1; ++i)
                res[i] = digits[i];
            res[length + 1] = '\0';
            delete[] digits;
            digits = res;
        }
        else
            *this = LongNum();
    }

    LongNum &LongNum::operator=(const LongNum &a)  {
        if(this == &a)
            return *this;
        length = a.length;
        delete[] digits;
        digits = new char[a.length + 2];
        memcpy(digits, a.digits, a.length + 1);
        digits[length + 1] = '\0';
        return *this;
    }

    LongNum::LongNum(LongNum &&a) noexcept{
        length = a.length;
        digits = a.digits;
        a.digits = nullptr;
    }



    LongNum& LongNum::operator=(LongNum &&a) noexcept {
        if(this == &a)
            return *this;
        delete[] digits;
        length = a.length;
        digits = a.digits;
        a.length = 0;
        a.digits = nullptr;
        return *this;
    }

    char* LongNum::back_from_additional(char* res, int length_r){
        if (res[0] == '9') {//back from additional
            res[length_r] = res[length_r] - 1;
            int i = length_r;
            while (res[i] < '0' && i > 0) {
                res[i] = '9';
                i--;
                res[i] = res[i] - 1;
            }
            for (int j = 1; j < length_r + 1; ++j)
                res[j] = '9' - res[j] + 48;
        }
        return res;
    }

    char* LongNum::rm_zeroes(char* res, int &length_r) {
        int c = 0;
        while (res[c] == '0' && c <= length_r)
            c++;
        if (res[1] == '0') {
            if (c != length_r + 1) {
                int i = 1;
                int l = length_r;
                while (res[i] == '0') {
                    length_r--;
                    i++;
                }
                char *res1 = new char[length_r + 2];
                res1[0] = res[0];
                i = 1;
                int j = 1;
                int f = 0;
                while (i <= l) {
                    if (res[i] != '0' || f == 1) {
                        res1[j] = res[i];
                        j++;
                        f = 1;
                    }

                    i++;
                }
                res1[length_r + 1] = '\0';
                delete[] res;
                res = res1;
            } else {
                if (c == length_r + 1) {
                    char *res1 = new char[3];
                    res1[0] = '0';
                    res1[1] = '0';
                    res1[2] = '\0';
                    delete[] res;
                    length_r = 1;
                    res = res1;
                }
            }
        }
        return res;
    }

    char* LongNum::char_sum_pos(LongNum &a, const LongNum &b, int length_r){
        char* res = new char[length_r + 2];
        //full res with '0'
        for (int i = 0; i < length_r + 1; ++i)
            res[i] = '0';
        res[length_r + 1] = '\0';
        int k = 0;
        for (int i = 0; i < length_r + 1; ++i) {
            if (b.length - i >= 0 && a.length - i >= 0) {//to the end of smaller num
                res[length_r - i] = b.digits[b.length - i] + a.digits[a.length - i] + k - 48;
                k = 0;
                if (res[length_r - i] > '9') {
                    k = 1;
                    res[length_r - i] = res[length_r - i] - 10;
                }
            } else {
                if (a.length > b.length)
                    res[length_r - i] = a.digits[a.length - i] + k;
                else
                    res[length_r - i] = b.digits[b.length - i] + k;
                if (res[length_r - i] > '9') {
                    k = 1;
                    res[length_r - i] = res[length_r - i] - 10;
                }
            }
        }
        return res;
    }


    char* LongNum::char_sum_neg(LongNum &a, const LongNum &b, int length_r) {
        char* res = new char[length_r + 2];
        //full res with '0'
        for (int i = 0; i < length_r + 1; ++i)
            res[i] = '0';
        res[length_r + 1] = '\0';
        //res[0] = '0';
        int k = 0;
        for (int i = 0; i < length_r + 1; ++i) {
            if (a.length - i > 0 && b.length - i > 0) {//to the end of smaller num
                res[length_r - i] = a.digits[a.length - i] + b.digits[b.length - i] + k - 48;
                k = 0;
                if (res[length_r - i] > '9') {
                    k = 1;
                    res[length_r - i] = res[length_r - i] - 10;
                }
            } else {
                if (b.length - i > a.length - i) {
                    res[length_r - i] = b.digits[b.length - i] + k;
                    k = 0;
                } else if (b.length - i == a.length - i) {
                    res[length_r - i] = 9 + 48 + k;
                    k = 0;
                } else {
                    res[length_r - i] = a.digits[a.length - i] + k;
                    k = 0;
                }
                if (res[length_r - i] > '9') {
                    k = 1;
                    if (res[0] > '9')
                        res[0] = res[0] - 9;
                    else
                        res[length_r - i] = res[length_r - i] - 10;
                }
            }
        }
        return res;
    }


    char* LongNum::char_subtract(const char* n, const char* p, int length_p, int length_n, int length_r) {
        char* res = new char[length_r + 2];
        //full res with '0'
        for (int i = 0; i < length_r + 1; ++i)
            res[i] = '0';
        res[length_r + 1] = '\0';
        int k = 0;
        for (int i = 0; i < length_r + 1; ++i) {
            if (length_p - i >= 0 && length_n - i >= 0) {//to the end of smaller num
                res[length_r - i] = p[length_p - i] + n[length_n - i] + k - 48;
                k = 0;
                if (res[length_r - i] > '9') {
                    k = 1;
                    res[length_r - i] = res[length_r - i] - 10;
                }
            } else {
                if (length_p > length_n)
                    res[length_r - i] = p[length_p - i] + k + 9;
                else
                    res[length_r - i] = n[length_n - i] + k;
                if (res[length_r - i] > '9') {
                    k = 1;
                    res[length_r - i] = res[length_r - i] - 10;
                }
            }
        }
        return res;
    }

    LongNum LongNum::operator+(const LongNum &a) const {
        char *res = nullptr;
        int length_r = std::max(a.length, this->length);
        //sum of positive
        if (a.digits[0] == '0' && this->digits[0] == '0') {
            LongNum b = *this;
            res = char_sum_pos(b, a, length_r);
            //overflow (1 + 999 for eg)
            if (res[0] > '0') {
                length_r++;
                char *res1 = new char[length_r + 2];
                std::memcpy(res1, res, length_r);
                for (int i = length_r; i > 0; --i)
                    res1[i] = res1[i - 1];
                res1[0] = '0';
                res1[length_r + 1] = '\0';
                delete[] res;
                res = res1;
            }
        }
        //sum of negative (9.111 + 9.222)
        if (a.digits[0] == '9' && this->digits[0] == '9') {
            LongNum b = *this;
            res = char_sum_neg(b, a, length_r);
            //overflow (-1 + -999 for eg)
            if (res[0] > '0' && res[0] != '9') {
                length_r++;
                char *res1 = new char[length_r + 2];
                std::memcpy(res1, res, length_r);
                for (int i = length_r; i > 0; --i)
                    res1[i] = res1[i - 1];
                res1[0] = '9';
                res1[length_r + 1] = '\0';
                delete[] res;
                res = res1;
            }
        }
        //subtraction
        if ((a.digits[0] == '0' && this->digits[0] == '9') || (a.digits[0] == '9' && this->digits[0] == '0')) {
            char *p;
            char *n;
            int length_p, length_n;
            if (a.digits[0] == '0') {
                p = a.digits;
                n = this->additional_code();
                length_n = this->length;
                length_p = a.length;
            } else {
                p = this->digits;
                n = a.additional_code();
                length_p = this->length;
                length_n = a.length;
            }
            res = char_subtract(n, p, length_p, length_n, length_r);
            res[length_r + 1] = '\0';
            if (res[0] == '9')
                res = back_from_additional(res, length_r);
            res = rm_zeroes(res, length_r);
            res[length_r + 1] = '\0';
            delete[] n;
        }
        LongNum tmp;
        tmp.length = length_r;
        delete[] tmp.digits;
        tmp.digits = new char[length_r + 2];
        memcpy(tmp.digits, res, length_r + 1);
        delete[] res;
        return tmp;
    }


    LongNum LongNum::operator-(const LongNum &a) const {
        LongNum b(a);
        if(b.digits[0] == '0')
            b.digits[0] = '9';
        else
            b.digits[0] = '0';
        return *this + b;
    }


    std::ostream &operator<<(std::ostream &out, const LongNum &a) {
        if (a.digits[0] == '9')
            out << a.digits[0] << ".";
        if (a.digits[0] == '0')
            out << a.digits[0] << ".";
        for (int i = 1; i < a.length + 1; ++i)
            out << a.digits[i];
        return out;
    }

    std::istream &operator>>(std::istream &in, LongNum &a) {
        std::string s;
        in >> s;
        char res[s.length() + 1];
        for(int i = 0; i < s.length() + 1; ++i){
            res[i] = s[i];
        }
        try {
            LongNum b(res);
            a.length = b.length;
            delete[] a.digits;
            a.digits = new char[b.length + 2];
            memcpy(a.digits, b.digits, b.length + 2);
        }
        catch(std::runtime_error &e){
            in.setstate(std::ios_base::failbit);
            return in;
        }
        return in;
    }
}