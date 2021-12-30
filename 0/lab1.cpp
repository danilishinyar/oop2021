#include "iostream"

#include "lab1.h"

namespace lab1{

    Matrix* input(){
        int m, n;
        Matrix* matr;
        std::cout << "Enter number of lines:" << std::endl;
        if(getNum(m) == -1)
            return nullptr;
        std::cout << "Enter number of rows:" << std::endl;
        if(getNum(n) == -1)
            return nullptr;
        matr = new Matrix;
        matr->rows = n;
        matr->lines = m;
        for(int i = 0; i < m; ++i){
            std::cout << "Enter line" << i+1 << ":" << std::endl;
            for(int j = 0; j < n; ++j) {
                int a;
                if(getNum(a) == -1)
                    return nullptr;
                if(a != 0) {
                    matr->values.push_back(a);
                    matr->row_index.push_back(j);
                }
            }
            matr->line_index.push_back(i);
        }
        return matr;
    }


    void erase(Matrix* matr){
        matr->line_index.clear();
        matr->line_index.shrink_to_fit();
        matr->row_index.clear();
        matr->row_index.shrink_to_fit();
        matr->values.clear();
        matr->values.shrink_to_fit();
        delete matr;
    }


    void output(const char *msg, Matrix* matr){
        int i, j, k, n;
        k = 0;
        n = 0;
        std::cout << msg << std::endl;
        while(k < matr->line_index.size() || n < matr->row_index.size()) {
            for (i = 0; i < matr->lines; ++i) {
                for (j = 0; j < matr->rows; ++j) {
                    if (i == matr->line_index[k] && j == matr->row_index[n]) {
                        std::cout << matr->values[n] << "  ";
                        n++;
                    } else
                        std::cout << "0" << "  ";

                }
                std::cout << std::endl;
                k++;
            }
        }
    }


    int getDights(int n){
        int s = 0;
        if(n < 0)
            n = -n;
        while(n != 0){
            s = s + n % 10;
            n = n / 10;
        }
        return s;
    }


    int* getFinalNum(Matrix* matr){
        int* res;
        int a, m, n;
        res = new int[matr->lines];
        m = 0; n = 0;
        for(int i = 0; i < matr->lines; i++){
            res[i] = 0;
            if(i == matr->line_index[m] and matr->row_index[n] == 0) {
                a = getDights(matr->values[n]);
                res[i] = matr->values[n];
                n++;
                for (int j = 1; j < matr->rows; j++) {
                    if (i == matr->line_index[m] && j == matr->row_index[n]) {
                        if (a == getDights(matr->values[n]))
                            res[i] += matr->values[n];
                        n++;
                    }
                }
            }
            else
                res[i] = 0;
            m++;
        }
        return res;
    }

    void output_res(const char *msg, int* res, Matrix* matr){
        int i;
        std::cout << msg << std::endl;
        for (i = 0; i < matr->lines; ++i){
            std::cout << res[i] << "  ";
        }
        delete[] res;
    }
}