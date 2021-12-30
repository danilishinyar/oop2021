#include "lab1.h"

using namespace lab1;

int main() {
    Matrix* a;
    a = input();
    if (a == nullptr)
        return 0;
   int* res = getFinalNum(a);
   output("Matrix:", a);
   output_res("Result:", res, a);
    erase(a);
    return 0;
}
