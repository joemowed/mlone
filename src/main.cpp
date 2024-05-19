#include <iostream>
#include <matrix.hpp>
#include <random>
#include <vector>
int main(int argc, char *[]) {

    const std::vector<float> vec{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    const std::vector<float> vec1{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    const std::vector<float> resVec1{3, 6, 9, 12, 6, 12, 18, 24, 9, 18, 27, 36, 12, 24, 36, 48};
    const std::vector<float> resVec2(9, 30);
    matrix res2{4, 4, resVec1};
    matrix mat{4, 3, vec};
    matrix mat1{3, 4, vec1};
    matrix res1 = mat * mat1;
    res2.coutMat("res2");
    res1.coutMat("res");
    mat.coutMat("A");
    mat1.coutMat("B");
    bool s = res1 == res2;
    std::cout << "\n\n" << s << "\n\n";
    return 0;
}
