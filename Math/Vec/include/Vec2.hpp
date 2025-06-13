#ifndef BLUEPRINT_VEC2_H
#define BLUEPRINT_VEC2_H

#include <cmath>
#include <limits>
#include <algorithm>

#include "BaseVec.hpp"
#include "../../Attribute.h"

namespace Math::Vec {
    template <typename Ty_>
    struct vec<2, Ty_> {
        using ValueType = Ty_;
        using VecType = vec<2, ValueType>;

        ValueType x;
        ValueType y;

        constexpr vec();
        constexpr vec(vec const& v);
        explicit constexpr vec(Ty_ scalar);
        constexpr vec(Ty_ _x, Ty_ _y);
        template <typename U_> explicit constexpr vec(vec<1, U_> const& v);
        template <typename A_, typename B_> constexpr vec(A_ _x, B_ _y);
        template <typename A_, typename B_> constexpr vec(vec<1, A_> const& _x, B_ _y);
        template <typename A_, typename B_> constexpr vec(A_ _x, vec<1, B_> const& _y);
        template <typename A_, typename B_> constexpr vec(vec<1, A_> const& _x, vec<1, B_> const& _y);
        template <typename U_> constexpr vec(vec<2, U_> const& v);
        template <typename U_> constexpr vec(vec<3, U_> const& v);
        template <typename U_> constexpr vec(vec<4, U_> const& v);

        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr static std::size_t length() noexcept ;

        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr Ty_& operator[](std::size_t i) noexcept ;
        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr Ty_ const& operator[](std::size_t i) const noexcept ;

        ALWAYS_INLINE constexpr vec<2, Ty_>& operator=(vec<2, Ty_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator+=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator+=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator+=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator-=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator-=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator-=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator*=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator*=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator*=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator/=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator/=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator/=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator%=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator%=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator%=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator&=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator&=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator&=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator|=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator|=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator|=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator^=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator^=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator^=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator<<=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator<<=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator<<=(vec<2, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator>>=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator>>=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<2, Ty_>& operator>>=(vec<2, U_> const& v) noexcept ;

        ALWAYS_INLINE constexpr vec<2, Ty_>& operator++() noexcept ;
        ALWAYS_INLINE constexpr vec<2, Ty_>& operator--() noexcept ;
        ALWAYS_INLINE constexpr vec<2, Ty_> operator++(int) noexcept ;
        ALWAYS_INLINE constexpr vec<2, Ty_> operator--(int) noexcept ;
    };
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator+(vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator-(vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator+(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator+(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator+(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator+(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator+(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator-(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator-(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator-(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator-(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator-(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator*(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator*(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator*(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator*(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator*(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator/(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator/(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator/(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator/(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator/(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator%(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator%(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator%(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator%(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator%(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator&(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator&(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator&(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator&(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator&(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator|(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator|(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator|(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator|(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator|(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator^(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator^(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator^(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator^(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator^(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator<<(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator<<(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator<<(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator<<(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator<<(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator>>(vec<2, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator>>(vec<2, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator>>(Ty_ scalar, vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator>>(vec<1, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator>>(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<2, Ty_> operator~(vec<2, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr bool operator==(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr bool operator!=(vec<2, Ty_> const& v1, vec<2, Ty_> const& v2);
    ALWAYS_INLINE constexpr vec<2, bool> operator&&(vec<2, bool> const& v1, vec<2, bool> const& v2);
    ALWAYS_INLINE constexpr vec<2, bool> operator||(vec<2, bool> const& v1, vec<2, bool> const& v2);
}

#include "../src/Vec2.inl"

#endif //BLUEPRINT_VEC2_H
