#include "../include/Vec1.hpp"

template <typename Ty_>
constexpr std::size_t Math::Vec::vec<1, Ty_>::length() noexcept {
    return 1;
}

template <typename Ty_>
constexpr Ty_& Math::Vec::vec<1, Ty_>::operator[](typename std::size_t) noexcept {
    return x;
}

template <typename Ty_>
constexpr Ty_ const& Math::Vec::vec<1, Ty_>::operator[](typename std::size_t) const noexcept {
    return x;
}

template <typename Ty_>
constexpr Math::Vec::vec<1, Ty_>::vec()
    : x(0)
{

}

template <typename Ty_>
constexpr Math::Vec::vec<1, Ty_>::vec(const vec<1, Ty_> &v)
    : x(v.x)
{

}

template <typename Ty_>
constexpr Math::Vec::vec<1, Ty_>::vec(Ty_ scalar)
    : x(scalar)
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_>::vec(const vec<1, U_> &v)
    : x(static_cast<Ty_>(v.x))
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_>::vec(const vec<2, U_> &v)
    : x(static_cast<Ty_>(v.x))
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_>::vec(const vec<3, U_> &v)
    : x(static_cast<Ty_>(v.x))
{

}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_>::vec(const vec<4, U_> &v)
    : x(static_cast<Ty_>(v.x))
{

}

template <typename Ty_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator=(const vec<1, Ty_> &v) noexcept {
    this->x = v.x;
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator=(const vec<1, U_> &v) noexcept {
    this->x = static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator+=(U_ scalar) noexcept {
    this->x += static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator+=(const vec<1, U_> &v) noexcept {
    this->x = static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator-=(U_ scalar) noexcept {
    this->x -= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator-=(const vec<1, U_> &v) noexcept {
    this->x -= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator*=(U_ scalar) noexcept {
    this->x -= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator*=(const vec<1, U_> &v) noexcept {
    this->x -= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator/=(U_ scalar) noexcept {
    this->x -= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator/=(const vec<1, U_> &v) noexcept {
    this->x -= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator++() noexcept {
    ++this->x;
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator--() noexcept {
    --this->x;
    return *this;
}

template <typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::vec<1, Ty_>::operator++(int) noexcept {
    vec<1, Ty_> res(*this);
    ++*this;
    return res;
}

template <typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::vec<1, Ty_>::operator--(int) noexcept {
    vec<1, Ty_> res(*this);
    --*this;
    return res;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator%=(U_ scalar) noexcept {
    this->x %= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator%=(const vec<1, U_> &v) noexcept {
    this->x %= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator&=(U_ scalar) noexcept {
    this->x &= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator&=(const vec<1, U_> &v) noexcept {
    this->x &= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator|=(U_ scalar) noexcept {
    this->x |= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator|=(const vec<1, U_> &v) noexcept {
    this->x |= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator^=(U_ scalar) noexcept {
    this->x ^= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator^=(const vec<1, U_> &v) noexcept {
    this->x ^= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator<<=(U_ scalar) noexcept {
    this->x <<= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator<<=(const vec<1, U_> &v) noexcept {
    this->x <<= static_cast<Ty_>(v.x);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator>>=(U_ scalar) noexcept {
    this->x >>= static_cast<Ty_>(scalar);
    return *this;
}

template <typename Ty_>
template <typename U_>
constexpr Math::Vec::vec<1, Ty_> &Math::Vec::vec<1, Ty_>::operator>>=(const vec<1, U_> &v) noexcept {
    this->x >>= static_cast<Ty_>(v.x);
    return *this;
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator+(const vec<1, Ty_> &v) {
    return v;
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator-(const vec<1, Ty_> &v) {
    return vec<1, Ty_>(-v.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator+(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(v.x + scalar);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator+(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(scalar + v.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator+(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(v1.x + v2.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator-(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(v.x - scalar);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator-(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(scalar - v.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator-(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(v1.x - v2.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator*(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(v.x * scalar);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator*(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(scalar * v.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator*(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(v1.x * v2.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator/(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(v.x / scalar);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator/(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(scalar / v.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator/(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(v1.x / v2.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator%(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(v.x % scalar);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator%(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(scalar % v.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator%(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(v1.x % v2.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator&(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(v.x & scalar);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator&(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(scalar & v.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator&(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(v1.x & v2.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator|(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(v.x | scalar);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator|(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(scalar | v.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator|(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(v1.x | v2.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator^(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(v.x ^ scalar);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator^(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(scalar ^ v.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator^(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(v1.x ^ v2.x);
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator<<(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(static_cast<Ty_>(v.x << scalar));
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator<<(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(static_cast<Ty_>(scalar << v.x));
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator<<(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(static_cast<Ty_>(v1.x << v2.x));
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator>>(const vec<1, Ty_> &v, Ty_ scalar) {
    return vec<1, Ty_>(static_cast<Ty_>(v.x >> scalar));
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator>>(Ty_ scalar, const vec<1, Ty_> &v) {
    return vec<1, Ty_>(static_cast<Ty_>(scalar >> v.x));
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator>>(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return vec<1, Ty_>(static_cast<Ty_>(v1.x >> v2.x));
}

template<typename Ty_>
constexpr Math::Vec::vec<1, Ty_> Math::Vec::operator~(const vec<1, Ty_> &v) {
    return vec<1, Ty_>(~v.x);
}


template<typename Ty_>
constexpr bool Math::Vec::operator==(const vec<1, Ty_>& v1, const vec<1, Ty_>& v2) {
    if constexpr (std::numeric_limits<Ty_>::is_iec559) {
        if (std::isnan(v1.x) || std::isnan(v2.x)) {
            return false;
        }

        if (std::isinf(v1.x) || std::isinf(v2.x)) {
            return std::signbit(v1.x) == std::signbit(v2.x) && v1.x == v2.x;
        }
        const Ty_ abs_diff = std::abs(v1.x - v2.x);
        const Ty_ max_abs = std::max(std::abs(v1.x), std::abs(v2.x));
        return abs_diff <= std::numeric_limits<Ty_>::epsilon() * max_abs;
    } else {
        return v1.x == v2.x;
    }
}

template<typename Ty_>
constexpr bool Math::Vec::operator!=(const vec<1, Ty_> &v1, const vec<1, Ty_> &v2) {
    return !(v1 == v2);
}

constexpr Math::Vec::vec<1, bool> Math::Vec::operator&&(const vec<1, bool> &v1, const vec<1, bool> &v2) {
    return vec<1, bool>(v1.x && v2.x);
}

constexpr Math::Vec::vec<1, bool> Math::Vec::operator||(const vec<1, bool> &v1, const vec<1, bool> &v2) {
    return vec<1, bool>(v1.x || v2.x);
}
