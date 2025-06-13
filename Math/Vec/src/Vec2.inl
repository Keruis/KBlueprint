#include "../include/Vec2.hpp"

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_>::vec()
    : x(0),
      y(0)
{

}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_>::vec(const vec<2, Ty_> &v)
    : x(v.x),
      y(v.y)
{

}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_>::vec(Ty_ scalar)
    : x(scalar),
      y(scalar)
{

}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_>::vec(Ty_ _x, Ty_ _y)
    : x(_x),
      y(_y)
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_>::vec(const vec<1, U_> &v)
    : x(static_cast<Ty_>(v.x)),
      y(static_cast<Ty_>(v.y))
{

}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<2, Ty_>::vec(A_ _x, B_ _y)
    : x(static_cast<Ty_>(_x)),
      y(static_cast<Ty_>(_y))
{

}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<2, Ty_>::vec(const vec<1, A_> &_x, B_ _y)
    : x(static_cast<Ty_>(_x.x)),
      y(static_cast<Ty_>(_y))
{

}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<2, Ty_>::vec(A_ _x, const vec<1, B_> &_y)
    : x(_x),
      y(_y.x)
{

}

template <typename Ty_>
template <typename A_, typename B_>
constexpr Math::Vec::vec<2, Ty_>::vec(const vec<1, A_> &_x, const vec<1, B_> &_y)
    : x(_x.x),
      y(_y.x)
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_>::vec(const vec<2, U_> &v)
    : x(static_cast<Ty_>(v.x)),
      y(static_cast<Ty_>(v.y))
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_>::vec(const vec<3, U_> &v)
        : x(static_cast<Ty_>(v.x)),
          y(static_cast<Ty_>(v.y))
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_>::vec(const vec<4, U_> &v)
        : x(static_cast<Ty_>(v.x)),
          y(static_cast<Ty_>(v.y))
{

}

template <typename Ty_>
constexpr std::size_t Math::Vec::vec<2, Ty_>::length() noexcept {
    return 2;
}

template <typename Ty_>
constexpr Ty_ &Math::Vec::vec<2, Ty_>::operator[](std::size_t i) noexcept {
    switch (i) {
        default:
        case 0:
            return x;
        case 1:
            return y;
    }
}

template <typename Ty_>
constexpr const Ty_ &Math::Vec::vec<2, Ty_>::operator[](std::size_t i) const noexcept {
    switch (i) {
        default:
        case 0:
            return x;
        case 1:
            return y;
    }
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator=(const vec<2, Ty_> &v) noexcept {
    this->x = v.x;
    this->y = v.y;
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator=(const vec<2, U_> &v) noexcept {
        this->x = static_cast<Ty_>(v.x);
        this->y = static_cast<Ty_>(v.y);
        return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator+=(U_ scalar) noexcept {
    this->x += static_cast<Ty_>(scalar);
    this->y += static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator+=(const vec<1, U_> &v) noexcept {
    this->x += static_cast<Ty_>(v.x);
    this->y += static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator+=(const vec<2, U_> &v) noexcept {
    this->x += static_cast<Ty_>(v.x);
    this->y += static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator-=(U_ scalar) noexcept {
    this->x -= static_cast<Ty_>(scalar);
    this->y -= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator-=(const vec<1, U_> &v) noexcept {
    this->x -= static_cast<Ty_>(v.x);
    this->y -= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator-=(const vec<2, U_> &v) noexcept {
    this->x -= static_cast<Ty_>(v.x);
    this->y -= static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator*=(U_ scalar) noexcept {
    this->x *= static_cast<Ty_>(scalar);
    this->y *= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator*=(const vec<1, U_> &v) noexcept {
    this->x *= static_cast<Ty_>(v.x);
    this->y *= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator*=(const vec<2, U_> &v) noexcept {
    this->x *= static_cast<Ty_>(v.x);
    this->y *= static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator/=(U_ scalar) noexcept {
    this->x /= static_cast<Ty_>(scalar);
    this->y /= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator/=(const vec<1, U_> &v) noexcept {
    this->x /= static_cast<Ty_>(v.x);
    this->y /= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator/=(const vec<2, U_> &v) noexcept {
    this->x /= static_cast<Ty_>(v.x);
    this->y /= static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator%=(U_ scalar) noexcept {
    this->x %= static_cast<Ty_>(scalar);
    this->y %= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator%=(const vec<1, U_> &v) noexcept {
    this->x %= static_cast<Ty_>(v.x);
    this->y %= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator%=(const vec<2, U_> &v) noexcept {
    this->x %= static_cast<Ty_>(v.x);
    this->y %= static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator&=(U_ scalar) noexcept {
    this->x &= static_cast<Ty_>(scalar);
    this->y &= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator&=(const vec<1, U_> &v) noexcept {
    this->x &= static_cast<Ty_>(v.x);
    this->y &= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator&=(const vec<2, U_> &v) noexcept {
    this->x &= static_cast<Ty_>(v.x);
    this->y &= static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator|=(U_ scalar) noexcept {
    this->x |= static_cast<Ty_>(scalar);
    this->y |= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator|=(const vec<1, U_> &v) noexcept {
    this->x |= static_cast<Ty_>(v.x);
    this->y |= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator|=(const vec<2, U_> &v) noexcept {
    this->x |= static_cast<Ty_>(v.x);
    this->y |= static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator^=(U_ scalar) noexcept {
    this->x ^= static_cast<Ty_>(scalar);
    this->y ^= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator^=(const vec<1, U_> &v) noexcept {
    this->x ^= static_cast<Ty_>(v.x);
    this->y ^= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator^=(const vec<2, U_> &v) noexcept {
    this->x ^= static_cast<Ty_>(v.x);
    this->y ^= static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator<<=(U_ scalar) noexcept {
    this->x <<= static_cast<Ty_>(scalar);
    this->y <<= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator<<=(const vec<1, U_> &v) noexcept {
    this->x <<= static_cast<Ty_>(v.x);
    this->y <<= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator<<=(const vec<2, U_> &v) noexcept {
    this->x <<= static_cast<Ty_>(v.x);
    this->y <<= static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator>>=(U_ scalar) noexcept {
    this->x >>= static_cast<Ty_>(scalar);
    this->y >>= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator>>=(const vec<1, U_> &v) noexcept {
    this->x >>= static_cast<Ty_>(v.x);
    this->y >>= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator>>=(const vec<2, U_> &v) noexcept {
    this->x >>= static_cast<Ty_>(v.x);
    this->y >>= static_cast<Ty_>(v.y);
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator++() noexcept {
    ++this->x;
    ++this->y;
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> &Math::Vec::vec<2, Ty_>::operator--() noexcept {
    --this->x;
    --this->y;
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::vec<2, Ty_>::operator++(int) noexcept {
    vec<2, Ty_> res(*this);
    ++*this;
    return res;
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::vec<2, Ty_>::operator--(int) noexcept {
    vec<2, Ty_> res(*this);
    --*this;
    return res;
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator+(const vec<2, Ty_> &v) {
    return v;
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator-(const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            -v.x,
            -v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator+(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x + scalar,
            v.y + scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator+(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x + v2.x,
            v1.y + v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator+(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar + v.x,
            scalar + v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator+(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x + v2.x,
            v1.x + v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator+(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x + v2.x,
            v1.y + v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator-(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x - scalar,
            v.y - scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator-(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x - v2.x,
            v1.y - v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator-(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar - v.x,
            scalar - v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator-(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x - v2.x,
            v1.x - v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator-(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x - v2.x,
            v1.y - v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator*(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x * scalar,
            v.y * scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator*(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x * v2.x,
            v1.y * v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator*(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar * v.x,
            scalar * v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator*(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x * v2.x,
            v1.x * v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator*(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x * v2.x,
            v1.y * v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator/(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x / scalar,
            v.y / scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator/(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x / v2.x,
            v1.y / v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator/(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar / v.x,
            scalar / v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator/(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x / v2.x,
            v1.x / v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator/(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x / v2.x,
            v1.y / v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator%(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x % scalar,
            v.y % scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator%(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x % v2.x,
            v1.y % v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator%(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar % v.x,
            scalar % v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator%(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x % v2.x,
            v1.x % v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator%(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x % v2.x,
            v1.y % v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator&(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x & scalar,
            v.y & scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator&(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x & v2.x,
            v1.y & v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator&(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar & v.x,
            scalar & v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator&(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x & v2.x,
            v1.x & v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator&(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x & v2.x,
            v1.y & v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator|(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x | scalar,
            v.y | scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator|(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x | v2.x,
            v1.y | v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator|(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar | v.x,
            scalar | v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator|(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x | v2.x,
            v1.x | v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator|(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x | v2.x,
            v1.y | v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator^(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x ^ scalar,
            v.y ^ scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator^(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x ^ v2.x,
            v1.y ^ v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator^(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar ^ v.x,
            scalar ^ v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator^(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x ^ v2.x,
            v1.x ^ v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator^(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x ^ v2.x,
            v1.y ^ v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator<<(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x << scalar,
            v.y << scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator<<(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x << v2.x,
            v1.y << v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator<<(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar << v.x,
            scalar << v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator<<(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x << v2.x,
            v1.x << v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator<<(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x << v2.x,
            v1.y << v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator>>(const vec<2, Ty_> &v, Ty_ scalar) {
    return vec<2, Ty_>(
            v.x >> scalar,
            v.y >> scalar);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator>>(const vec<2, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x >> v2.x,
            v1.y >> v2.x);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator>>(Ty_ scalar, const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            scalar >> v.x,
            scalar >> v.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator>>(const vec<1, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x >> v2.x,
            v1.x >> v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator>>(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return vec<2, Ty_>(
            v1.x >> v2.x,
            v1.y >> v2.y);
}

template <typename Ty_>
constexpr Math::Vec::vec<2, Ty_> Math::Vec::operator~(const vec<2, Ty_> &v) {
    return vec<2, Ty_>(
            ~v.x,
            ~v.y);
}

template <typename Ty_>
constexpr bool Math::Vec::operator==(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    if constexpr (std::numeric_limits<Ty_>::is_iec559) {
        if (std::isnan(v1.x) || std::isnan(v2.x)) return false;
        if (std::isinf(v1.x) || std::isinf(v2.x))
            return std::signbit(v1.x) == std::signbit(v2.x) && v1.x == v2.x;

        const Ty_ abs_diff_x = std::abs(v1.x - v2.x);
        const Ty_ max_abs_x = std::max(std::abs(v1.x), std::abs(v2.x));
        const bool x_equal = abs_diff_x <= std::numeric_limits<Ty_>::epsilon() * max_abs_x;

        if (std::isnan(v1.y) || std::isnan(v2.y)) return false;
        if (std::isinf(v1.y) || std::isinf(v2.y))
            return std::signbit(v1.y) == std::signbit(v2.y) && v1.y == v2.y;

        const Ty_ abs_diff_y = std::abs(v1.y - v2.y);
        const Ty_ max_abs_y = std::max(std::abs(v1.y), std::abs(v2.y));
        const bool y_equal = abs_diff_y <= std::numeric_limits<Ty_>::epsilon() * max_abs_y;

        return x_equal && y_equal;
    } else {
        return v1.x == v2.x && v1.y == v2.y;
    }
}

template <typename Ty_>
constexpr bool Math::Vec::operator!=(const vec<2, Ty_> &v1, const vec<2, Ty_> &v2) {
    return !(v1 == v2);
}

constexpr Math::Vec::vec<2, bool> Math::Vec::operator&&(const vec<2, bool> &v1, const vec<2, bool> &v2) {
    return vec<2, bool>(v1.x && v2.x, v1.y && v2.y);
}

constexpr Math::Vec::vec<2, bool> Math::Vec::operator||(const vec<2, bool> &v1, const vec<2, bool> &v2) {
    return vec<2, bool>(v1.x || v2.x, v1.y || v2.y);
}