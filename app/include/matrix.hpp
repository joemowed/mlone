#ifndef __MATRIX_INC_GRD__
#define __MATRIX_INC_GRD__

#include <cstddef>
#include <vector>
#define M_IMPL CPU_Matrix
template <typename MATRIX_IMPL_TYPE> class Matrix {
  private:
    using T = float;

  public:
    virtual ~Matrix() = default;
    virtual T at(std::size_t i, std::size_t j);
};

#endif
