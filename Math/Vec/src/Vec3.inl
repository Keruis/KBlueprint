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
constexpr Math::Vec::vec<3, Ty_> &Math::Vec::vec<3, Ty_>::operator+=(U_ scalar) noexcept {
    if consteval {
        scalar_op(scalar, std::plus<>{});
    } else {
        if constexpr (std::is_same_v<Ty_, float>) {
            __m128 s = _mm_set1_ps(static_cast<float>(scalar));
            __m128 v = _mm_load_ps(data);
            v = _mm_add_ps(v, s);
            _mm_store_ps(data, v);
        } else if constexpr (std::is_same_v<Ty_, double>) {
            __m256d s = _mm256_set1_pd(static_cast<double>(scalar));
            __m256d v = _mm256_load_pd(data);
            v = _mm256_add_pd(v, s);
            _mm256_store_pd(data, v);
        } else if constexpr (std::is_integral_v<Ty_> && sizeof(Ty_) == 4) {
            __m128i s = _mm_set1_epi32(static_cast<int32_t>(scalar));
            __m128i v = _mm_load_si128(reinterpret_cast<const __m128i*>(data));
            v = _mm_add_epi32(v, s);
            _mm_store_si128(reinterpret_cast<__m128i*>(data), v);
        } else if constexpr (std::is_integral_v<Ty_> && sizeof(Ty_) == 8) {
            __m256i s = _mm256_set1_epi64x(static_cast<int64_t>(scalar));
            __m256i v = _mm256_load_si256(reinterpret_cast<const __m256i*>(data));
            v = _mm256_add_epi64(v, s);
            _mm256_store_si256(reinterpret_cast<__m256i*>(data), v);
        } else {
            scalar_op(scalar, std::plus<>{});
        }
    }
    return *this;
}

