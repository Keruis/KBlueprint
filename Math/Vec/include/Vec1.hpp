#ifndef BLUEPRINT_VEC1_H
#define BLUEPRINT_VEC1_H

#include <cmath>
#include <limits>
#include <algorithm>

#include "BaseVec.hpp"
#include "../../../Attribute.h"

namespace Math::Vec {
    template <typename Ty_>
    struct vec<1, Ty_> {
        using ValueType = Ty_;
        using VecType = vec<1, ValueType>;

        ValueType x;

        constexpr vec();
        constexpr vec(vec const& v);
        explicit constexpr vec(Ty_ scalar);
        template<typename U_> constexpr vec(vec<1, U_> const& v);
        template<typename U_> constexpr vec(vec<2, U_> const& v);
        template<typename U_> constexpr vec(vec<3, U_> const& v);
        template<typename U_> constexpr vec(vec<4, U_> const& v);

        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr static std::size_t length() noexcept ;

        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr Ty_& operator[](std::size_t i) noexcept ;
        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr Ty_ const& operator[](std::size_t i) const noexcept ;

        ALWAYS_INLINE constexpr vec<1, Ty_>& operator=(vec<1, Ty_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator+=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator+=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator-=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator-=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator*=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator*=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator/=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator/=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator%=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator%=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator&=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator&=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator|=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator|=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator^=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator^=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator<<=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator<<=(vec<1, U_> const& v) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator>>=(U_ scalar) noexcept ;
        template <typename U_> ALWAYS_INLINE constexpr vec<1, Ty_>& operator>>=(vec<1, U_> const& v) noexcept ;

        ALWAYS_INLINE constexpr vec<1, Ty_>& operator++() noexcept ;
        ALWAYS_INLINE constexpr vec<1, Ty_>& operator--() noexcept ;
        ALWAYS_INLINE constexpr vec<1, Ty_> operator++(int) noexcept ;
        ALWAYS_INLINE constexpr vec<1, Ty_> operator--(int) noexcept ;
    };

    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator+(vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator-(vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator+(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator+(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator+(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator-(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator-(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator-(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator*(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator*(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator*(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator/(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator/(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator/(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator%(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator%(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator%(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator&(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator&(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator&(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator|(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator|(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator|(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator^(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator^(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator^(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator<<(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator<<(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator<<(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator>>(vec<1, Ty_> const& v, Ty_ scalar);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator>>(Ty_ scalar, vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator>>(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr vec<1, Ty_> operator~(vec<1, Ty_> const& v);
    template <typename Ty_> ALWAYS_INLINE constexpr bool operator==(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    template <typename Ty_> ALWAYS_INLINE constexpr bool operator!=(vec<1, Ty_> const& v1, vec<1, Ty_> const& v2);
    ALWAYS_INLINE constexpr vec<1, bool> operator&&(vec<1, bool> const& v1, vec<1, bool> const& v2);
    ALWAYS_INLINE constexpr vec<1, bool> operator||(vec<1, bool> const& v1, vec<1, bool> const& v2);
}

#include "../src/Vec1.inl"

#endif //BLUEPRINT_VEC1_H
