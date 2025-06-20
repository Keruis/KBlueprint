#ifndef BLUEPRINT_MMAT_H
#define BLUEPRINT_MMAT_H

#include "Mat/include/Mat2x2.hpp"
#include "Mat/include/Mat2x3.hpp"
#include "Mat/include/Mat2x4.hpp"
#include "Mat/include/Mat3x2.hpp"
#include "Mat/include/Mat3x3.hpp"
#include "Mat/include/Mat3x4.hpp"
#include "Mat/include/Mat4x2.hpp"
#include "Mat/include/Mat4x3.hpp"
#include "Mat/include/Mat4x4.hpp"

#include "Mat/include/Mat4x4Float.hpp"

namespace Math::Mat {
    using MatF22 = mat<2, 2, float>;
    using MatF23 = mat<2, 3, float>;
    using MatF24 = mat<2, 4, float>;
    using MatF32 = mat<3, 2, float>;
    using MatF33 = mat<3, 3, float>;
    using MatF34 = mat<3, 4, float>;
    using MatF42 = mat<4, 2, float>;
    using MatF43 = mat<4, 3, float>;
    using MatF44 = mat<4, 4, float>;
}

#endif //BLUEPRINT_MMAT_H
