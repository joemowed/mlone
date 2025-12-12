#ifndef _MATRIX_INC_GRD_
#define _MATRIX_INC_GRD_

#define MATRIX_IMPL_CPU_ST_VALUE 1

/* "MATRIX_IMPL" below is the flag for setting what implementation of the matrix
 * library will be in use. Available options are listed above.*/
#define MATRIX_IMPL MATRIX_IMPL_CPU_ST_VALUE

#if MATRIX_IMPL == MATRIX_IMPL_CPU_ST_VALUE
#include "matrix_st.hpp"
#endif

#endif
