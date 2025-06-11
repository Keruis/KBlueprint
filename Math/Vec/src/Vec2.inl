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