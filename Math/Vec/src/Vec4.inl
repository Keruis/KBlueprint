#include "../include/Vec4.hpp"

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_>::vec() : x{}, y{}, z{}, w{} {}

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_>::vec(const vec<4, Ty_> &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_>::vec(Ty_ scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_>::vec(Ty_ _x, Ty_ _y, Ty_ _z, Ty_ _w) : x(_x), y(_y), z(_z), w(_w) {}

template <typename Ty_>
template <typename U_> constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, U_> const& v) : x(v.x), y(v.x), z(v.x), w(v.x) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(X_ _x, Y_ _y, Z_ _z, W_ _w) : x(_x), y(_y), z(_z), w(_w) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, X_> const& _x, Y_ _y, Z_ _z, W_ _w) : x(_x.x), y(_y), z(_z), w(_w) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(X_ _x, vec<1, Y_> const& _y, Z_ _z, W_ _w) : x(_x), y(_y.x), z(_z), w(_w) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, Z_ _z, W_ _w) : x(_x.x), y(_y.x), z(_z), w(_w) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(X_ _x, Y_ _y, vec<1, Z_> const& _z, W_ _w) : x(_x), y(_y), z(_z.x), w(_w) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, X_> const& _x, Y_ _y, vec<1, Z_> const& _z, W_ _w) : x(_x.x), y(_y), z(_z.x), w(_w) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(X_ _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z, W_ _w) : x(_x), y(_y.x), z(_z.x), w(_w) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z, W_ _w) : x(_x.x), y(_y.x), z(_z.x), w(_w) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(X_ _x, Y_ _y, Z_ _z, vec<1, W_> const& _w) : x(_x), y(_y), z(_z), w(_w.x) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, X_> const& _x, Y_ _y, Z_ _z, vec<1, W_> const& _w) : x(_x.x), y(_y), z(_z), w(_w.x) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(X_ _x, vec<1, Y_> const& _y, Z_ _z, vec<1, W_> const& _w) : x(_x), y(_y.x), z(_z), w(_w.x) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, Z_ _z, vec<1, W_> const& _w) : x(_x.x), y(_y.x), z(_z), w(_w.x) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(X_ _x, Y_ _y, vec<1, Z_> const& _z, vec<1, W_> const& _w) : x(_x), y(_y), z(_z.x), w(_w.x) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, X_> const& _x, Y_ _y, vec<1, Z_> const& _z, vec<1, W_> const& _w) : x(_x.x), y(_y), z(_z.x), w(_w.x) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(X_ _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z, vec<1, W_> const& _w) : x(_x), y(_y.x), z(_z.x), w(_w.x) {}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_, typename W_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z, vec<1, W_> const& _w) : x(_x.x), y(_y.x), z(_z.x), w(_w.x) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<2, A_> const& _xy, B_ _z, C_ _w) : x(_xy.x), y(_xy.y), z(_z), w(_w) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<2, A_> const& _xy, vec<1, B_> const& _z, C_ _w) : x(_xy.x), y(_xy.y), z(_z.x), w(_w) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<2, A_> const& _xy, B_ _z, vec<1, C_> const& _w) : x(_xy.x), y(_xy.y), z(_z), w(_w.x) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<2, A_> const& _xy, vec<1, B_> const& _z, vec<1, C_> const& _w) : x(_xy.x), y(_xy.y), z(_z.x), w(_w.x) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(A_ _x, vec<2, B_> const& _yz, C_ _w) : x(_x), y(_yz.x), z(_yz.y), w(_w) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, A_> const& _x, vec<2, B_> const& _yz, C_ _w) : x(_x.x), y(_yz.x), z(_yz.y), w(_w) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(A_ _x, vec<2, B_> const& _yz, vec<1, C_> const& _w) : x(_x), y(_yz.x), z(_yz.y), w(_w.x) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, A_> const& _x, vec<2, B_> const& _yz, vec<1, C_> const& _w) : x(_x.x), y(_yz.x), z(_yz.y), w(_w.x) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(A_ _x, B_ _y, vec<2, C_> _zw) : x(_x), y(_y), z(_zw.x), w(_zw.y) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, A_> const& _x, B_ _y, vec<2, C_> _zw) : x(_x.x), y(_y), z(_zw.x), w(_zw.y) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(A_ _x, vec<1, B_> const& _y, vec<2, C_> _zw) : x(_x), y(_y.x), z(_zw.x), w(_zw.y) {}

template <typename Ty_>
template <typename A_, typename B_, typename C_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, A_> const& _x, vec<1, B_> const& _y, vec<2, C_> _zw) : x(_x.x), y(_y.x), z(_zw.x), w(_zw.y) {}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<3, A_> const& _xyz, B_ _w) : x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w) {}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<3, A_> const& _xyz, vec<1, B_> const& _w) : x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w.x) {}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<4, Ty_>::vec(A_ _x, vec<3, B_> const& _yzw) : x(_x), y(_yzw.x), z(_yzw.y), w(_yzw.z) {}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<1, A_> const& _x, vec<3, B_> const& _yzw) : x(_x.x), y(_yzw.x), z(_yzw.y), w(_yzw.z) {}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<4, Ty_>::vec(vec<2, A_> const& _xy, vec<2, B_> _zw) : x(_xy.x), y(_xy.y), z(_zw.x), w(_zw.y) {}

template <typename Ty_>
constexpr std::size_t Math::Vec::vec<4, Ty_>::length() noexcept {
    return 4;
}

template <typename Ty_>
constexpr Ty_ &Math::Vec::vec<4, Ty_>::operator[](std::size_t i) noexcept {
    switch (i) {
        default:
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
    }
}

template <typename Ty_>
constexpr const Ty_ &Math::Vec::vec<4, Ty_>::operator[](std::size_t i) const noexcept {
    switch (i) {
        default:
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
    }
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<4, Ty_>& Math::Vec::vec<4, Ty_>::operator=(vec<4, U_> const& v) noexcept {
    x = v.x; y = v.y; z = v.z; w = v.w;
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_>& Math::Vec::vec<4, Ty_>::operator=(vec<4, Ty_> const& v) noexcept {
    x = v.x; y = v.y; z = v.z; w = v.w;
    return *this;
}

#define DEFINE_VEC4_OP(op) \
template <typename Ty_> \
template <typename U_> \
constexpr Math::Vec::vec<4, Ty_>& Math::Vec::vec<4, Ty_>::operator op##=(U_ scalar) noexcept { \
    x op##= scalar; y op##= scalar; z op##= scalar; w op##= scalar; \
    return *this; \
} \
\
template <typename Ty_> \
template <typename U_> \
constexpr Math::Vec::vec<4, Ty_>& Math::Vec::vec<4, Ty_>::operator op##=(vec<1, U_> const& v) noexcept { \
    x op##= v.x; y op##= v.x; z op##= v.x; w op##= v.x; \
    return *this; \
} \
\
template <typename Ty_> \
template <typename U_> \
constexpr Math::Vec::vec<4, Ty_>& Math::Vec::vec<4, Ty_>::operator op##=(vec<4, U_> const& v) noexcept { \
    x op##= v.x; y op##= v.y; z op##= v.z; w op##= v.w; \
    return *this; \
}

DEFINE_VEC4_OP(+)
DEFINE_VEC4_OP(-)
DEFINE_VEC4_OP(*)
DEFINE_VEC4_OP(/)
DEFINE_VEC4_OP(%)
DEFINE_VEC4_OP(&)
DEFINE_VEC4_OP(|)
DEFINE_VEC4_OP(^)
DEFINE_VEC4_OP(<<)
DEFINE_VEC4_OP(>>)

#undef DEFINE_VEC4_OP

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_> &Math::Vec::vec<4, Ty_>::operator++() noexcept {
    ++this->x;
    ++this->y;
    ++this->z;
    ++this->w;
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_> &Math::Vec::vec<4, Ty_>::operator--() noexcept {
    --this->x;
    --this->y;
    --this->z;
    --this->w;
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_> Math::Vec::vec<4, Ty_>::operator++(int) noexcept {
    vec<4, Ty_> res(*this);
    ++*this;
    return res;
}

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_> Math::Vec::vec<4, Ty_>::operator--(int) noexcept {
    vec<4, Ty_> res(*this);
    --*this;
    return res;
}

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_> Math::Vec::operator+(const vec<4, Ty_> &v) {
    return v;
}

template <typename Ty_>
constexpr Math::Vec::vec<4, Ty_> Math::Vec::operator-(const vec<4, Ty_> &v) {
    return vec<4, Ty_>(
            -v.x,
            -v.y
            -v.z,
            -v.w);
}


#define DEFINE_VEC4_BINARY_OP(OP_SYMBOL)                                                  \
template <typename Ty_>                                                                            \
constexpr Math::Vec::vec<4, Ty_> Math::Vec::operator OP_SYMBOL(vec<4, Ty_> const& v, Ty_ scalar) {                    \
    return { v.x OP_SYMBOL scalar, v.y OP_SYMBOL scalar, v.z OP_SYMBOL scalar, v.w OP_SYMBOL scalar }; \
}                                                                                                  \
                                                                                                   \
template <typename Ty_>                                                                            \
constexpr Math::Vec::vec<4, Ty_> Math::Vec::operator OP_SYMBOL(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2) {        \
    return { v1.x OP_SYMBOL v2.x, v1.y OP_SYMBOL v2.x, v1.z OP_SYMBOL v2.x, v1.w OP_SYMBOL v2.x }; \
}                                                                                                  \
                                                                                                   \
template <typename Ty_>                                                                            \
constexpr Math::Vec::vec<4, Ty_> Math::Vec::operator OP_SYMBOL(Ty_ scalar, vec<4, Ty_> const& v) {                    \
    return { scalar OP_SYMBOL v.x, scalar OP_SYMBOL v.y, scalar OP_SYMBOL v.z, scalar OP_SYMBOL v.w }; \
}                                                                                                  \
                                                                                                   \
template <typename Ty_>                                                                            \
constexpr Math::Vec::vec<4, Ty_> Math::Vec::operator OP_SYMBOL(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2) {        \
    return { v1.x OP_SYMBOL v2.x, v1.x OP_SYMBOL v2.y, v1.x OP_SYMBOL v2.z, v1.x OP_SYMBOL v2.w }; \
}                                                                                                  \
                                                                                                   \
template <typename Ty_>                                                                            \
constexpr Math::Vec::vec<4, Ty_> Math::Vec::operator OP_SYMBOL(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2) {        \
    return { v1.x OP_SYMBOL v2.x, v1.y OP_SYMBOL v2.y, v1.z OP_SYMBOL v2.z, v1.w OP_SYMBOL v2.w }; \
}

DEFINE_VEC4_BINARY_OP(+);
DEFINE_VEC4_BINARY_OP(-);
DEFINE_VEC4_BINARY_OP(*);
DEFINE_VEC4_BINARY_OP(/);
DEFINE_VEC4_BINARY_OP(%);
DEFINE_VEC4_BINARY_OP(&);
DEFINE_VEC4_BINARY_OP(|);
DEFINE_VEC4_BINARY_OP(^);
DEFINE_VEC4_BINARY_OP(<<);
DEFINE_VEC4_BINARY_OP(>>);