#include <cassert>
#include <matMath.hpp>
matrix MM::addMat(matrix &mat1, matrix &mat2) {
    assert(((mat1.getDimensions().cols == mat2.getDimensions().cols) && (mat1.getDimensions().rows == mat2.getDimensions().rows)) && "matrix dims must match for addition");
    const matrixDimensions dims = {.rows = mat1.getDimensions().rows, .cols = mat1.getDimensions().cols};
    matrix ret = matrix(dims);
    for (int x = 0; x < mat1.getDimensions().cols; x++) {
        for (int y = 0; y < mat1.getDimensions().rows; y++) {
            const float res = mat1.getMember(x, y) + mat2.getMember(x, y);
            ret.setMember(x, y, res);
        }
    }
    return ret;
}
