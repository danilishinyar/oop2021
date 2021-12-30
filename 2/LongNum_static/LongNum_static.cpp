#include "LongNum_static.h"

#include <iostream>
#include <cstring>
#include <cmath>

namespace Num_static {
    LongNum::LongNum() {
        length = 1;
        dights[0] = '0';
        dights[1] = '0';
    }

    LongNum::LongNum(long num) {
        length = 0;
        long n = std::abs(num);
        while (n > 0) {
            length++;
            n = n / 10;
        }
        if(length < MAX) {
            if (num >= 0)
                dights[0] = '0';
            else
                dights[0] = '9';
            num = std::abs(num);
            for (int i = 1; i < length + 1; ++i) {
                dights[i] = (char) (num / pow(10, length - i) + 48);
                long k = pow(10, length - i);
                num = num % k;
            }
        }
        else{
            throw std::runtime_error("invalid input");
        }
    }

    LongNum::LongNum(const char *num) {
        if (num[0] == '-' && num[1] == '0') {
            length = 1;
            dights[0] = '0';
            dights[1] = '1';
            return;
        }
        if (num[0] == '-') {
            length = 0;
            while (num[length] != '\0')
                length++;
            length--;
            if(length < MAX) {
                std::memcpy(dights, num, length + 1);
                dights[0] = '9';
            }
            else
                throw std::runtime_error("invalid input");
        } else {
            length = 0;
            while (num[length] != '\0')
                length++;
            if(length < MAX) {
                std::memcpy(dights, num, length + 1);
                for (int i = length; i > 0; --i)
                    dights[i] = dights[i - 1];
                dights[0] = '0';
            }
            else
                throw std::runtime_error("invalid input");
        }
    }

    LongNum::LongNum(const LongNum &a) {
        length = a.length;
        memcpy(dights, a.dights, a.length + 1);
    }

    char *LongNum::additional_code() const {
        char* res = new char[10];
        res[0] = dights[0];
        if (dights[0] == '9') {
            for (int i = 1; i < length + 1; ++i)
                res[i] = char(9 - int(dights[i]) + 2 * 48);
            int k = 1;
            for (int i = 0; i < length; ++i) {
                res[length] = char(int(res[length]) + k);
                k = 0;
                if (res[length - i] > '9') {
                    k = 1;
                    res[length - i] = '0';
                    res[length - i - 1] = char(int(res[length - i - 1]) + k);
                    k = 0;
                }
            }
        } else {
            for (int i = 0; i < length + 1; ++i)
                res[i] = dights[i];
        }
        return res;
    }

    void LongNum::increase_10_times() {
        if(length < MAX - 1) {
            length += 1;
            char res[10];
            for (int i = 0; i < length; ++i)
                res[i] = dights[i];
            res[length] = '0';
            memcpy(dights, res, length + 1);
        }
        else
            throw std::runtime_error("reached max'");
    }

    void LongNum::decrease_10_times() {
        if(length > 1) {
            length--;
            char res[10];
            for (int i = 0; i < length + 1; ++i)
                res[i] = dights[i];
            memcpy(dights, res, length + 1);
        }
        else{
            length = 1;
            dights[0] = '0';
            dights[1] = '0';
        }
    }

    LongNum &LongNum::equal(const LongNum &a) {
        length = a.length;
        memcpy(dights, a.dights, a.length + 1);
        return *this;
    }

    LongNum LongNum::add(const LongNum &a){
        char *res = nullptr;
        int length_r = std::max(a.length, this->length);
        //sum of positive
        if (a.dights[0] == '0' && this->dights[0] == '0') {
            res = new char[length_r + 1];
            //full res with '0'
            for (int i = 0; i < length_r + 1; ++i)
                res[i] = '0';
            int k = 0;
            for (int i = 0; i < length_r + 1; ++i) {
                if (a.length - i >= 0 && this->length - i >= 0) {//to the end of smaller num
                    res[length_r - i] = char(
                            int(a.dights[a.length - i]) + int(this->dights[this->length - i]) + k - 48);
                    k = 0;
                    if (res[length_r - i] > '9') {
                        k = 1;
                        res[length_r - i] = char(int(res[length_r - i]) - 10);
                    }
                } else {
                    if (this->length > a.length)
                        res[length_r - i] = char(int(this->dights[this->length - i]) + k);
                    else
                        res[length_r - i] = char(int(a.dights[a.length - i]) + k);
                    if (res[length_r - i] > '9') {
                        k = 1;
                        res[length_r - i] = char(int(res[length_r - i]) - 10);
                    }
                }
            }
            //overflow (1 + 999 for eg)
            if (int(res[0]) > int('0')) {
                length_r++;
                char *res1 = new char[length_r + 1];
                std::memcpy(res1, res, length_r);
                for (int i = length_r; i > 0; --i)
                    res1[i] = res1[i - 1];
                res1[0] = '0';
                delete[] res;
                res = res1;
            }
        }
        //sum of negative (9.111 + 9.222)
        if (a.dights[0] == '9' && this->dights[0] == '9') {
            res = new char[length_r + 1];
            //full res with '0'
            for (int i = 0; i < length_r + 1; ++i)
                res[i] = '0';
            //res[0] = '0';
            int k = 0;
            for (int i = 0; i < length_r + 1; ++i) {
                if (a.length - i > 0 && this->length - i > 0) {//to the end of smaller num
                    res[length_r - i] = char(
                            int(a.dights[a.length - i]) + int(this->dights[this->length - i]) + k - 48);
                    k = 0;
                    if (res[length_r - i] > '9') {
                        k = 1;
                        res[length_r - i] = char(int(res[length_r - i]) - 10);
                    }
                } else {
                    if (this->length - i > a.length - i) {
                        res[length_r - i] = char(int(this->dights[this->length - i]) + k);
                        k = 0;
                    } else if (this->length - i == a.length - i) {
                        res[length_r - i] = char(9 + 48 + k);
                        k = 0;
                    } else {
                        res[length_r - i] = char(int(a.dights[a.length - i]) + k);
                        k = 0;
                    }
                    if (res[length_r - i] > '9') {
                        k = 1;
                        if (res[0] > '9')
                            res[0] = char(int(res[0]) - 9);
                        else
                            res[length_r - i] = char(int(res[length_r - i]) - 10);
                    }
                }
            }
            //overflow (-1 + -999 for eg)
            if (int(res[0]) > int('0') && res[0] != '9') {
                length_r++;
                char *res1 = new char[length_r + 1];
                std::memcpy(res1, res, length_r);
                for (int i = length_r; i > 0; --i)
                    res1[i] = res1[i - 1];
                res1[0] = '9';
                delete[] res;
                res = res1;
            }
        }
        //subtraction
        if ((a.dights[0] == '0' && this->dights[0] == '9') || (a.dights[0] == '9' && this->dights[0] == '0')) {
            char p[MAX];
            char n[MAX];
            int length_p, length_n;
            if (a.dights[0] == '0') {
                memcpy(p, a.dights, a.length + 1);
                char* r = this->additional_code();
                memcpy(n, r, this->length + 1);
                delete[] r;
                length_n = this->length;
                length_p = a.length;
            } else {
                memcpy(p, this->dights, this->length + 1);
                char* r = a.additional_code();
                memcpy(n, r, a.length + 1);
                delete[] r;
                length_p = this->length;
                length_n = a.length;
            }
            res = new char[length_r + 1];
            //full res with '0'
            for (int i = 0; i < length_r + 1; ++i)
                res[i] = '0';
            int k = 0;
            for (int i = 0; i < length_r + 1; ++i) {
                if (length_p - i >= 0 && length_n - i >= 0) {//to the end of smaller num
                    res[length_r - i] = char(int(p[length_p - i]) + int(n[length_n - i]) + k - 48);
                    k = 0;
                    if (res[length_r - i] > '9') {
                        k = 1;
                        res[length_r - i] = char(int(res[length_r - i]) - 10);
                    }
                } else {
                    if (length_p > length_n)
                        res[length_r - i] = char(int(p[length_p - i]) + k + 9);
                    else
                        res[length_r - i] = char(int(n[length_n - i]) + k);
                    if (res[length_r - i] > '9') {
                        k = 1;
                        res[length_r - i] = char(int(res[length_r - i]) - 10);
                    }
                }
            }
            if (res[0] == '9') {//back from additional
                res[length_r] = char(int(res[length_r]) - 1);
                int i = length_r;
                while (int(res[i]) < int('0') && i > 0) {
                    res[i] = '9';
                    i--;
                    res[i] = char(int(res[i]) - 1);
                }
                for (int j = 1; j < length_r + 1; ++j)
                    res[j] = char(int('9') - int(res[j]) + 48);
            }
            int c = 0;
            while (c <= length_r) {
                if(res[c] == '0')
                    c++;
                else
                    break;
            }
            if (res[1] == '0') {
                if (c != length_r + 1) {
                    int i = 1;
                    int l = length_r;
                    while (res[i] == '0') {
                        length_r--;
                        i++;
                    }
                    char *res1 = new char[length_r + 1];
                    res1[0] = res[0];
                    i = 1;
                    int j = 1;
                    while (i <= l) {
                        if (res[i] != '0') {
                            res1[j] = res[i];
                            j++;
                        }
                        i++;
                    }
                    delete[] res;
                    res = res1;
                } else {
                    if (c == length_r + 1) {
                        char *res1 = new char[2];
                        res1[0] = '0';
                        res1[1] = '0';
                        delete[] res;
                        length_r = 1;
                        res = res1;
                    }
                }
            }
        }
        if(length_r < MAX) {
            LongNum tmp;
            tmp.length = length_r;
            memcpy(tmp.dights, res, length_r + 1);
            delete[] res;
            return tmp;
        }
        else
            throw std::runtime_error("overflow");
    }


    LongNum LongNum::subtract(const LongNum &a) {
        LongNum b(a);
        if(b.dights[0] == '0')
            b.dights[0] = '9';
        else
            b.dights[0] = '0';
        return this->add(b);
    }


    std::ostream& LongNum::output(std::ostream &out) const {
        out << "\nLength:" << length << '\n';
        if (dights[0] == '9')
            out << dights[0] << ".";
        if (dights[0] == '0')
            out << dights[0] << ".";
        for (int i = 1; i < length + 1; ++i)
            out << dights[i];
        return out;
    }

    std::istream& LongNum::input(std::istream &in) {
        int i = 0;
        char *res = nullptr;
        char *tmp = nullptr;
        char m = ' ';
        while (m != '\n') {//dights string
            in.get(m);
            if(m == '\n')
                break;
            if((m < '0'  || m > '9') && m != '-')
                throw std::runtime_error("invalid input");
            if((m != '\n')) {
                if (res != nullptr) {
                    delete[] tmp;
                    tmp = new char[i];
                    memcpy(tmp, res, i);
                    delete[] res;
                    res = new char[i + 1];
                    memcpy(res, tmp, i);
                    res[i] = m;
                } else {
                    res = new char[1];
                    tmp = new char[1];
                    res[0] = m;
                    tmp[0] = m;
                }
                i++;
            }
        }
        delete[] tmp;
        tmp = new char[i + 1];
        memcpy(tmp, res, i);
        tmp[i] = '\0';
        LongNum tmp1(tmp);
        this->length = tmp1.length;
        memcpy(this->dights, tmp1.dights, this->length + 1);
        delete[] res;
        delete[] tmp;
    }
}
