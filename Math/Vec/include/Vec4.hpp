#ifndef BLUEPRINT_VEC4_H
#define BLUEPRINT_VEC4_H

#include "BaseVec.hpp"
#include "../../Attribute.h"

namespace Math::Vec {
    template <typename Ty_>
    struct vec<4, Ty_> {
        using ValueType = Ty_;
        using VecType = vec<1, ValueType>;

        ValueType x;
        ValueType y;
        ValueType z;
        ValueType w;

        constexpr vec();
        constexpr vec(vec<4, Ty_> const& v);
        explicit constexpr vec(Ty_ scalar);
        constexpr vec(Ty_ _x, Ty_ _y, Ty_ _z, Ty_ _w);
        template <typename U_> explicit constexpr vec(vec<1, U_> const& v);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(X_ _x, Y_ _y, Z_ _z, W_ _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(vec<1, X_> const& _x, Y_ _y, Z_ _z, W_ _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(X_ _x, vec<1, Y_> const& _y, Z_ _z, W_ _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, Z_ _z, W_ _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(X_ _x, Y_ _y, vec<1, Z_> const& _z, W_ _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(vec<1, X_> const& _x, Y_ _y, vec<1, Z_> const& _z, W_ _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(X_ _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z, W_ _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z, W_ _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(vec<1, X_> const& _x, Y_ _y, Z_ _z, vec<1, W_> const& _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(X_ _x, vec<1, Y_> _y, Z_ _z, vec<1, W_> const& _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, Z_ _z, vec<1, W_> const& _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(X_ _x, Y_ _y, vec<1, Z_> const& _z, vec<1, W_> const& _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(vec<1, X_> const& _x, Y_ _y, vec<1, Z_> const& _z, vec<1, W_> const& _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(X_ _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z, vec<1, W_> const& _w);
        template <typename X_, typename Y_, typename Z_, typename W_> constexpr vec(vec<1, X_> const& _x, vec<1, Y_> const& _y, vec<1, Z_> const& _z, vec<1, W_> const& _w);
        template <typename A_, typename B_, typename C_> constexpr vec(vec<2, A_> const& _xy, B_ _z, C_ _w);
        template <typename A_, typename B_, typename C_> constexpr vec(vec<2, A_> const& _xy, vec<1, B_> const& _z, C_ _w);
        template <typename A_, typename B_, typename C_> constexpr vec(vec<2, A_> const& _xy, B_ _z, vec<1, C_> const& _w);
        template <typename A_, typename B_, typename C_> constexpr vec(vec<2, A_> const& _xy, vec<1, B_> const& _z, vec<1, C_> const& _w);
        template <typename A_, typename B_, typename C_> constexpr vec(A_ _x, vec<2, B_> const& _yz, C_ _w);
        template <typename A_, typename B_, typename C_> constexpr vec(vec<1, A_> const& _x, vec<2, B_> const& _yz, C_ _w);
        template <typename A_, typename B_, typename C_> constexpr vec(A_ _x, vec<2, B_> const& _yz, vec<1, C_> const& _w);
        template <typename A_, typename B_, typename C_> constexpr vec(vec<1, A_> const& _x, vec<2, B_> const& _yz, vec<1, C_> const& _w);
        template <typename A_, typename B_, typename C_> constexpr vec(A_ _x, B_ _y, vec<2, C_> _zw);
        template <typename A_, typename B_, typename C_> constexpr vec(vec<1, A_> const& _x, B_ _y, vec<2, C_> _zw);
        template <typename A_, typename B_, typename C_> constexpr vec(A_ _x, vec<1, B_> const& _y, vec<2, C_> _zw);
        template <typename A_, typename B_, typename C_> constexpr vec(vec<1, A_> const& _x, vec<1, B_> const& _y, vec<2, C_> _zw);
        template <typename A_, typename B_> constexpr vec(vec<3, A_> const& _xyz, B_ _w);
        template <typename A_, typename B_> constexpr vec(vec<3, A_> const& _xyz, vec<1, B_> const& _w);
        template <typename A_, typename B_> constexpr vec(A_ _x, vec<3, B_> const& _yzw);
        template <typename A_, typename B_> constexpr vec(vec<1, A_> const& _x, vec<3, B_> const& _yzw);
        template <typename A_, typename B_> constexpr vec(vec<2, A_> const& _xy, vec<2, B_> _zw);

        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr static std::size_t length() noexcept ;

        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr Ty_& operator[](std::size_t i) noexcept ;
        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr Ty_ const& operator[](std::size_t i) const noexcept ;

        ALWAYS_INLINE constexpr vec<4, Ty_>& operator=(vec<4, Ty_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator+=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator+=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator+=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator-=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator-=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator-=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator*=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator*=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator*=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator/=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator/=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator/=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator%=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator%=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator%=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator&=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator&=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator&=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator|=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator|=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator|=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator^=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator^=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator^=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator<<=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator<<=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator<<=(vec<4, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator>>=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator>>=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<4, Ty_>& operator>>=(vec<4, U_> const& v) noexcept ;

        ALWAYS_INLINE constexpr vec<4, Ty_>& operator++() noexcept ;
        ALWAYS_INLINE constexpr vec<4, Ty_>& operator--() noexcept ;
        ALWAYS_INLINE constexpr vec<4, Ty_> operator++(int) noexcept ;
        ALWAYS_INLINE constexpr vec<4, Ty_> operator--(int) noexcept ;
    };
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator+(vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator-(vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator+(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator+(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator+(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator+(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator+(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator-(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator-(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator-(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator-(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator-(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator*(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator*(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator*(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator*(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator*(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator/(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator/(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator/(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator/(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator/(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator%(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator%(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator%(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator%(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator%(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator&(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator&(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator&(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator&(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator&(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator|(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator|(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator|(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator|(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator|(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator^(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator^(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator^(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator^(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator^(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator<<(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator<<(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator<<(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator<<(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator<<(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator>>(vec<4, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator>>(vec<4, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator>>(Ty_ scalar, vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator>>(vec<1, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator>>(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<4, Ty_> operator~(vec<4, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr bool operator==(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr bool operator!=(vec<4, Ty_> const& v1, vec<4, Ty_> const& v2);
    ALWAYS_INLINE constexpr vec<4, bool> operator&&(vec<4, bool> const& v1, vec<4, bool> const& v2);
    ALWAYS_INLINE constexpr vec<4, bool> operator||(vec<4, bool> const& v1, vec<4, bool> const& v2);
}


#endif //BLUEPRINT_VEC4_H
