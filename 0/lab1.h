#include <iostream>
#include <vector>

namespace lab1{



    struct Matrix{
        std::vector <int> row_index;
        std::vector <int> line_index;
        std::vector <int> values;
        int rows;
        int lines;
    };




    template<class T>
    int getNum(T &a){
        std::cin >> a;
        if(!std::cin.good())
            return -1;
        return 1;
    }



    Matrix* input();
    void output(const char*, Matrix*);
    int* getFinalNum(Matrix*);
    int getDights(int);
    void output_res(const char* , int*, Matrix*);
    void erase(Matrix*);
}
