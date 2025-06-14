#include "../include/Vec3.hpp"

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_>::vec()
    : x(0), y(0), z(0)
{

}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<3, Ty_> &v)
    : x(v.x), y(v.y), z(v.z)
{

}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_>::vec(Ty_ scalar)
    : x(scalar), y(scalar), z(scalar)
{

}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_>::vec(Ty_ _x, Ty_ _y, Ty_ _z)
    : x(_x), y(_y), z(_z)
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<1, U_> &v)
    : x(static_cast<Ty_>(v.x)),
      y(static_cast<Ty_>(v.x)),
      z(static_cast<Ty_>(v.x))
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<3, U_> &v)
    : x(static_cast<Ty_>(v.x)),
      y(static_cast<Ty_>(v.y)),
      z(static_cast<Ty_>(v.z))
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<4, U_> &v)
    : x(static_cast<Ty_>(v.x)),
      y(static_cast<Ty_>(v.y)),
      z(static_cast<Ty_>(v.z))
{

}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_>
constexpr Math::Vec::vec<3, Ty_>::vec(X_ _x, Y_ _y, Z_ _z)
        : x(static_cast<Ty_>(_x)),
          y(static_cast<Ty_>(_y)),
          z(static_cast<Ty_>(_z))
{

}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<1, X_> &_x, Y_ _y, Z_ _z)
        : x(static_cast<Ty_>(_x.x)),
          y(static_cast<Ty_>(_y)),
          z(static_cast<Ty_>(_z))
{

}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_>
constexpr Math::Vec::vec<3, Ty_>::vec(X_ _x, const vec<1, Y_> &_y, Z_ _z)
        : x(static_cast<Ty_>(_x)),
          y(static_cast<Ty_>(_y.x)),
          z(static_cast<Ty_>(_z))
{

}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_>
constexpr Math::Vec::vec<3, Ty_>::vec(X_ _x, Y_ _y, const vec<1, Z_> &_z)
        : x(static_cast<Ty_>(_x)),
          y(static_cast<Ty_>(_y)),
          z(static_cast<Ty_>(_z.x))
{

}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<1, X_> &_x, const vec<1, Y_> &_y, Z_ _z)
        : x(static_cast<Ty_>(_x.x)),
          y(static_cast<Ty_>(_y.x)),
          z(static_cast<Ty_>(_z))
{

}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_>
constexpr Math::Vec::vec<3, Ty_>::vec(X_ _x, const vec<1, Y_> &_y, const vec<1, Z_> &_z)
        : x(static_cast<Ty_>(_x)),
          y(static_cast<Ty_>(_y.x)),
          z(static_cast<Ty_>(_z.x))
{

}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<1, X_> &_x, Y_ _y, const vec<1, Z_> &_z)
        : x(static_cast<Ty_>(_x.x)),
          y(static_cast<Ty_>(_y)),
          z(static_cast<Ty_>(_z.x))
{

}

template <typename Ty_>
template <typename X_, typename Y_, typename Z_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<1, X_> &_x, const vec<1, Y_> &_y, const vec<1, Z_> &_z)
        : x(static_cast<Ty_>(_x.x)),
          y(static_cast<Ty_>(_y.x)),
          z(static_cast<Ty_>(_z.x))
{

}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<2, A_> &_xy, B_ _z)
        : x(static_cast<Ty_>(_xy.x))
        , y(static_cast<Ty_>(_xy.y))
        , z(static_cast<Ty_>(_z))
{

}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<2, A_> &_xy, const vec<1, B_> &_z)
        : x(static_cast<Ty_>(_xy.x)),
          y(static_cast<Ty_>(_xy.y)),
          z(static_cast<Ty_>(_z.x))
{

}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<3, Ty_>::vec(A_ _x, const vec<2, B_> &_yz)
        : x(static_cast<Ty_>(_x)),
          y(static_cast<Ty_>(_yz.x)),
          z(static_cast<Ty_>(_yz.y))
{

}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<3, Ty_>::vec(const vec<1, A_> &_x, const vec<2, B_> &_yz)
        : x(static_cast<Ty_>(_x.x)),
          y(static_cast<Ty_>(_yz.x)),
          z(static_cast<Ty_>(_yz.y))
{

}

template <typename Ty_>
constexpr std::size_t Math::Vec::vec<3, Ty_>::length() noexcept {
    return 3;
}

template <typename Ty_>
constexpr Ty_ &Math::Vec::vec<3, Ty_>::operator[](std::size_t i) noexcept {
    switch (i) {
        default:
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
    }
}

template <typename Ty_>
constexpr const Ty_ &Math::Vec::vec<3, Ty_>::operator[](std::size_t i) const noexcept {
    switch (i) {
        default:
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
    }
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> &Math::Vec::vec<3, Ty_>::operator=(const vec<3, Ty_> &v) noexcept {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_> &Math::Vec::vec<3, Ty_>::operator=(const vec<3, U_> &v) noexcept {
    this->x = static_cast<Ty_>(v.x);
    this->y = static_cast<Ty_>(v.y);
    this->z = static_cast<Ty_>(v.z);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator+=(U_ scalar) noexcept {
    x += static_cast<Ty_>(scalar);
    y += static_cast<Ty_>(scalar);
    z += static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator+=(const vec<1, U_> &v) noexcept {
    return *this += v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator+=(const vec<3, U_> &v) noexcept {
    x += static_cast<Ty_>(v.x);
    y += static_cast<Ty_>(v.y);
    z += static_cast<Ty_>(v.z);
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator-=(U_ scalar) noexcept {
    x -= static_cast<Ty_>(scalar);
    y -= static_cast<Ty_>(scalar);
    z -= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator-=(const vec<1, U_> &v) noexcept {
    return *this -= v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator-=(const vec<3, U_> &v) noexcept {
    x -= static_cast<Ty_>(v.x);
    y -= static_cast<Ty_>(v.y);
    z -= static_cast<Ty_>(v.z);
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator*=(U_ scalar) noexcept {
    x *= static_cast<Ty_>(scalar);
    y *= static_cast<Ty_>(scalar);
    z *= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator*=(const vec<1, U_> &v) noexcept {
    return *this *= v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator*=(const vec<3, U_> &v) noexcept {
    x *= static_cast<Ty_>(v.x);
    y *= static_cast<Ty_>(v.y);
    z *= static_cast<Ty_>(v.z);
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator/=(U_ scalar) noexcept {
    x /= static_cast<Ty_>(scalar);
    y /= static_cast<Ty_>(scalar);
    z /= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator/=(const vec<1, U_> &v) noexcept {
    return *this /= v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator/=(const vec<3, U_> &v) noexcept {
    x /= static_cast<Ty_>(v.x);
    y /= static_cast<Ty_>(v.y);
    z /= static_cast<Ty_>(v.z);
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator%=(U_ scalar) noexcept {
    x %= static_cast<Ty_>(scalar);
    y %= static_cast<Ty_>(scalar);
    z %= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator%=(const vec<1, U_> &v) noexcept {
    return *this %= v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator%=(const vec<3, U_> &v) noexcept {
    x %= static_cast<Ty_>(v.x);
    y %= static_cast<Ty_>(v.y);
    z %= static_cast<Ty_>(v.z);
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator&=(U_ scalar) noexcept {
    x &= static_cast<Ty_>(scalar);
    y &= static_cast<Ty_>(scalar);
    z &= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator&=(const vec<1, U_> &v) noexcept {
    return *this &= v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator&=(const vec<3, U_> &v) noexcept {
    x &= static_cast<Ty_>(v.x);
    y &= static_cast<Ty_>(v.y);
    z &= static_cast<Ty_>(v.z);
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator|=(U_ scalar) noexcept {
    x |= static_cast<Ty_>(scalar);
    y |= static_cast<Ty_>(scalar);
    z |= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator|=(const vec<1, U_> &v) noexcept {
    return *this |= v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator|=(const vec<3, U_> &v) noexcept {
    x |= static_cast<Ty_>(v.x);
    y |= static_cast<Ty_>(v.y);
    z |= static_cast<Ty_>(v.z);
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator^=(U_ scalar) noexcept {
    x ^= static_cast<Ty_>(scalar);
    y ^= static_cast<Ty_>(scalar);
    z ^= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator^=(const vec<1, U_> &v) noexcept {
    return *this ^= v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator^=(const vec<3, U_> &v) noexcept {
    x ^= static_cast<Ty_>(v.x);
    y ^= static_cast<Ty_>(v.y);
    z ^= static_cast<Ty_>(v.z);
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator<<=(U_ scalar) noexcept {
    x <<= static_cast<Ty_>(scalar);
    y <<= static_cast<Ty_>(scalar);
    z <<= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator<<=(const vec<1, U_> &v) noexcept {
    return *this <<= v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator<<=(const vec<3, U_> &v) noexcept {
    x <<= static_cast<Ty_>(v.x);
    y <<= static_cast<Ty_>(v.y);
    z <<= static_cast<Ty_>(v.z);
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator>>=(U_ scalar) noexcept {
    x >>= static_cast<Ty_>(scalar);
    y >>= static_cast<Ty_>(scalar);
    z >>= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator>>=(const vec<1, U_> &v) noexcept {
    return *this >>= v.x;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<3, Ty_>& Math::Vec::vec<3, Ty_>::operator>>=(const vec<3, U_> &v) noexcept {
    x >>= static_cast<Ty_>(v.x);
    y >>= static_cast<Ty_>(v.y);
    z >>= static_cast<Ty_>(v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> &Math::Vec::vec<3, Ty_>::operator++() noexcept {
    ++this->x;
    ++this->y;
    ++this->z;
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> &Math::Vec::vec<3, Ty_>::operator--() noexcept {
    --this->x;
    --this->y;
    --this->z;
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::vec<3, Ty_>::operator++(int) noexcept {
    vec<3, Ty_> res(*this);
    ++*this;
    return res;
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::vec<3, Ty_>::operator--(int) noexcept {
    vec<3, Ty_> res(*this);
    --*this;
    return res;
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator+(const vec<3, Ty_> &v) {
    return v;
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator-(const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            -v.x,
            -v.y
            -v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator+(const vec<3, Ty_> &v, Ty_ scalar) {
    return vec<3, Ty_>(
            v.x + scalar,
            v.y + scalar,
            v.z + scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator+(const vec<3, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x + v2.x,
            v1.y + v2.x,
            v1.z + v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator+(Ty_ scalar, const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            scalar + v.x,
            scalar + v.y,
            scalar + v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator+(const vec<1, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x + v2.x,
            v1.x + v2.y,
            v1.x + v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator+(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x + v2.x,
            v1.y + v2.y,
            v1.z + v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator-(const vec<3, Ty_> &v, Ty_ scalar) {
    return vec<3, Ty_>(
            v.x - scalar,
            v.y - scalar,
            v.z - scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator-(const vec<3, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x - v2.x,
            v1.y - v2.x,
            v1.z - v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator-(Ty_ scalar, const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            scalar - v.x,
            scalar - v.y,
            scalar - v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator-(const vec<1, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x - v2.x,
            v1.x - v2.y,
            v1.x - v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator-(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x - v2.x,
            v1.y - v2.y,
            v1.z - v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator*(const vec<3, Ty_> &v, Ty_ scalar) {
    return vec<3, Ty_>(
            v.x * scalar,
            v.y * scalar,
            v.z * scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator*(const vec<3, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x * v2.x,
            v1.y * v2.x,
            v1.z * v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator*(Ty_ scalar, const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            scalar * v.x,
            scalar * v.y,
            scalar * v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator*(const vec<1, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x * v2.x,
            v1.x * v2.y,
            v1.x * v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator*(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x * v2.x,
            v1.y * v2.y,
            v1.z * v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator/(const vec<3, Ty_> &v, Ty_ scalar) {
    return vec<3, Ty_>(
            v.x / scalar,
            v.y / scalar,
            v.z / scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator/(const vec<3, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x / v2.x,
            v1.y / v2.x,
            v1.z / v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator/(Ty_ scalar, const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            scalar / v.x,
            scalar / v.y,
            scalar / v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator/(const vec<1, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x / v2.x,
            v1.x / v2.y,
            v1.x / v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator/(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x / v2.x,
            v1.y / v2.y,
            v1.z / v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator%(const vec<3, Ty_> &v, Ty_ scalar) {
    return vec<3, Ty_>(
            v.x % scalar,
            v.y % scalar,
            v.z % scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator%(const vec<3, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x % v2.x,
            v1.y % v2.x,
            v1.z % v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator%(Ty_ scalar, const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            scalar % v.x,
            scalar % v.y,
            scalar % v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator%(const vec<1, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x % v2.x,
            v1.x % v2.y,
            v1.x % v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator%(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x % v2.x,
            v1.y % v2.y,
            v1.z % v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator&(const vec<3, Ty_> &v, Ty_ scalar) {
    return vec<3, Ty_>(
            v.x & scalar,
            v.y & scalar,
            v.z & scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator&(const vec<3, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x & v2.x,
            v1.y & v2.x,
            v1.z & v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator&(Ty_ scalar, const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            scalar & v.x,
            scalar & v.y,
            scalar & v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator&(const vec<1, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x & v2.x,
            v1.x & v2.y,
            v1.x & v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator&(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x & v2.x,
            v1.y & v2.y,
            v1.z & v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator|(const vec<3, Ty_> &v, Ty_ scalar) {
    return vec<3, Ty_>(
            v.x | scalar,
            v.y | scalar,
            v.z | scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator|(const vec<3, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x | v2.x,
            v1.y | v2.x,
            v1.z | v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator|(Ty_ scalar, const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            scalar | v.x,
            scalar | v.y,
            scalar | v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator|(const vec<1, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x | v2.x,
            v1.x | v2.y,
            v1.x | v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator|(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x | v2.x,
            v1.y | v2.y,
            v1.z | v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator^(const vec<3, Ty_> &v, Ty_ scalar) {
    return vec<3, Ty_>(
            v.x ^ scalar,
            v.y ^ scalar,
            v.z ^ scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator^(const vec<3, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x ^ v2.x,
            v1.y ^ v2.x,
            v1.z ^ v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator^(Ty_ scalar, const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            scalar ^ v.x,
            scalar ^ v.y,
            scalar ^ v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator^(const vec<1, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x ^ v2.x,
            v1.x ^ v2.y,
            v1.x ^ v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator^(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x ^ v2.x,
            v1.y ^ v2.y,
            v1.z ^ v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator<<(const vec<3, Ty_> &v, Ty_ scalar) {
    return vec<3, Ty_>(
            v.x << scalar,
            v.y << scalar,
            v.z << scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator<<(const vec<3, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x << v2.x,
            v1.y << v2.x,
            v1.z << v2.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator<<(Ty_ scalar, const vec<3, Ty_> &v) {
    return vec<3, Ty_>(
            scalar << v.x,
            scalar << v.y,
            scalar << v.z);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator<<(const vec<1, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x << v2.x,
            v1.x << v2.y,
            v1.x << v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<3, Ty_> Math::Vec::operator<<(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return vec<3, Ty_>(
            v1.x << v2.x,
            v1.y << v2.y,
            v1.z << v2.z);
}

template <typename Ty_>
constexpr bool Math::Vec::operator==(const vec<3, Ty_>& v1, const vec<3, Ty_>& v2) {
    if constexpr (std::numeric_limits<Ty_>::is_iec559) { // 浮点数
        if (std::isnan(v1.x) || std::isnan(v2.x)) return false;
        if (std::isinf(v1.x) || std::isinf(v2.x))
            if (!(std::signbit(v1.x) == std::signbit(v2.x) && v1.x == v2.x)) return false;
        const Ty_ abs_diff_x = std::abs(v1.x - v2.x);
        const Ty_ max_abs_x = std::max(std::abs(v1.x), std::abs(v2.x));
        const bool x_equal = abs_diff_x <= std::numeric_limits<Ty_>::epsilon() * max_abs_x;
        if (!x_equal) return false;

        if (std::isnan(v1.y) || std::isnan(v2.y)) return false;
        if (std::isinf(v1.y) || std::isinf(v2.y))
            if (!(std::signbit(v1.y) == std::signbit(v2.y) && v1.y == v2.y)) return false;
        const Ty_ abs_diff_y = std::abs(v1.y - v2.y);
        const Ty_ max_abs_y = std::max(std::abs(v1.y), std::abs(v2.y));
        const bool y_equal = abs_diff_y <= std::numeric_limits<Ty_>::epsilon() * max_abs_y;
        if (!y_equal) return false;

        if (std::isnan(v1.z) || std::isnan(v2.z)) return false;
        if (std::isinf(v1.z) || std::isinf(v2.z))
            if (!(std::signbit(v1.z) == std::signbit(v2.z) && v1.z == v2.z)) return false;
        const Ty_ abs_diff_z = std::abs(v1.z - v2.z);
        const Ty_ max_abs_z = std::max(std::abs(v1.z), std::abs(v2.z));
        const bool z_equal = abs_diff_z <= std::numeric_limits<Ty_>::epsilon() * max_abs_z;
        return z_equal;

    } else {
        return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    }
}

template <typename Ty_>
constexpr bool Math::Vec::operator!=(const vec<3, Ty_> &v1, const vec<3, Ty_> &v2) {
    return !(v1 == v2);
}

constexpr Math::Vec::vec<3, bool> Math::Vec::operator&&(const vec<3, bool> &v1, const vec<3, bool> &v2) {
    return vec<3, bool>(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z);
}

constexpr Math::Vec::vec<3, bool> Math::Vec::operator||(const vec<3, bool> &v1, const vec<3, bool> &v2) {
    return vec<3, bool>(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z);
}