#ifndef BLUEPRINT_VEC3_H
#define BLUEPRINT_VEC3_H

#include <type_traits>
#include <functional>
#include <immintrin.h>
#include <cmath>
#include <limits>
#include <algorithm>

#include "BaseVec.hpp"
#include "../../Attribute.h"
#include "../../detail/type_traits.h"
#include "../../detail/simd.h"

namespace Math::Vec {
    template <typename Ty_>
    struct vec<3, Ty_> {
        using ValueType = Ty_;
        using VecType = vec<3, ValueType>;

        ValueType x, y, z;

    private:
        template <typename U_, typename Op_>
        constexpr void scalar_op(U_ scalar, Op_ op) noexcept {
            x = op(x, scalar);
            y = op(y, scalar);
            z = op(z, scalar);
        }

    public:
        constexpr vec();
        constexpr vec(vec const& v);
        explicit constexpr vec(Ty_ scalar);
        constexpr vec(Ty_ _x, Ty_ _y, Ty_ _z);
        template <typename U_> explicit constexpr vec(vec<1, U_> const& v);
        template <typename U_> constexpr vec(vec<3, U_> const& v);
        template <typename U_> constexpr vec(vec<4, U_> const& v);
        template <typename X_, typename Y_, typename Z_> constexpr vec(X_ _x, Y_ _y, Z_ _z);
        template <typename X_, typename Y_, typename Z_> constexpr vec(vec<1, X_> const& _x, Y_ _y, Z_ _z);
        template <typename X_, typename Y_, typename Z_> constexpr vec(X_ _x, vec<1, Y_> const& _y, Z_ _z);
        template <typename X_, typename Y_, typename Z_> constexpr vec(X_ _x, Y_ _y, vec<1, Z_> const& _z);
        template <typename X_, typename Y_, typename Z_> constexpr vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, Z_ _z);
        template <typename X_, typename Y_, typename Z_> constexpr vec(X_ _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z);
        template <typename X_, typename Y_, typename Z_> constexpr vec(vec<1, X_> const& _x, Y_ _y, vec<1, Z_> const& _z);
        template <typename X_, typename Y_, typename Z_> constexpr vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z);
        template <typename A_, typename B_> constexpr vec(vec<2, A_> const& _xy, B_ _z);
        template <typename A_, typename B_> constexpr vec(vec<2, A_> const& _xy, vec<1, B_> const& _z);
        template <typename A_, typename B_> constexpr vec(A_ _x, vec<2, B_> const& _yz);
        template <typename A_, typename B_> constexpr vec(vec<1, A_> const& _x, vec<2, B_> const& _yz);

        OPTIMIZE_O3 ALWAYS_INLINE
        static constexpr std::size_t length() noexcept;

        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr Ty_& operator[](std::size_t i) noexcept ;
        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr Ty_ const& operator[](std::size_t i) const noexcept ;

        ALWAYS_INLINE constexpr vec<3, Ty_>& operator=(vec<3, Ty_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator+=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator+=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator+=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator-=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator-=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator-=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator*=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator*=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator*=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator/=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator/=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator/=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator%=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator%=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator%=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator&=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator&=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator&=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator|=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator|=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator|=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator^=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator^=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator^=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator<<=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator<<=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator<<=(vec<3, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator>>=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator>>=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<3, Ty_>& operator>>=(vec<3, U_> const& v) noexcept ;

        ALWAYS_INLINE constexpr vec<3, Ty_>& operator++() noexcept ;
        ALWAYS_INLINE constexpr vec<3, Ty_>& operator--() noexcept ;
        ALWAYS_INLINE constexpr vec<3, Ty_> operator++(int) noexcept ;
        ALWAYS_INLINE constexpr vec<3, Ty_> operator--(int) noexcept ;
    };
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator+(vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator-(vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator+(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator+(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator+(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator+(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator+(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator-(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator-(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator-(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator-(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator-(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator*(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator*(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator*(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator*(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator*(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator/(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator/(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator/(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator/(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator/(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator%(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator%(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator%(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator%(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator%(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator&(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator&(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator&(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator&(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator&(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator|(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator|(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator|(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator|(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator|(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator^(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator^(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator^(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator^(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator^(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator<<(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator<<(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator<<(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator<<(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator<<(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator>>(vec<3, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator>>(vec<3, Ty_> const& v, vec<1, Ty_> const& scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator>>(Ty_ scalar, vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator>>(vec<1, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator>>(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<3, Ty_> operator~(vec<3, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr bool operator==(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr bool operator!=(vec<3, Ty_> const& v1, vec<3, Ty_> const& v2);
    ALWAYS_INLINE constexpr vec<3, bool> operator&&(vec<3, bool> const& v1, vec<3, bool> const& v2);
    ALWAYS_INLINE constexpr vec<3, bool> operator||(vec<3, bool> const& v1, vec<3, bool> const& v2);
}

#include "../src/Vec3.inl"

#endif //BLUEPRINT_VEC3_H
