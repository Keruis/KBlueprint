#ifndef BLUEPRINT_MAT3X3_H
#define BLUEPRINT_MAT3X3_H

#include "BaseMat.h"
#include "../../Vec/include/Vec3.hpp"
#include "../../../Attribute.h"

namespace Math::Mat {
    template<typename Ty_>
    struct mat<3, 3, Ty_> {
        typedef Vec::vec<3, Ty_> col_type;
        typedef Vec::vec<3, Ty_> row_type;
        typedef mat<3, 3, Ty_> type;
        typedef mat<3, 3, Ty_> transpose_type;
        typedef Ty_ value_type;

    private:
        col_type value[3];

    public:
        static constexpr std::size_t length() { return 3; }

        constexpr col_type & operator[](std::size_t i) noexcept;
        constexpr col_type const& operator[](std::size_t i) const noexcept;

        constexpr mat();
        explicit constexpr mat(Ty_ scalar);
        constexpr mat(
                Ty_ x0, Ty_ y0, Ty_ z0,
                Ty_ x1, Ty_ y1, Ty_ z1,
                Ty_ x2, Ty_ y2, Ty_ z2);
        constexpr mat(
                col_type const& v0,
                col_type const& v1,
                col_type const& v2);

        template<
                typename X1, typename Y1, typename Z1,
                typename X2, typename Y2, typename Z2,
                typename X3, typename Y3, typename Z3>
        constexpr mat(
                X1 x1, Y1 y1, Z1 z1,
                X2 x2, Y2 y2, Z2 z2,
                X3 x3, Y3 y3, Z3 z3);

        template<typename V1, typename V2, typename V3>
        constexpr mat(
                Vec::vec<3, V1> const& v1,
                Vec::vec<3, V2> const& v2,
                Vec::vec<3, V3> const& v3);

        template<typename U>
        explicit constexpr mat(mat<3, 3, U> const& m);

        explicit constexpr mat(mat<2, 2, Ty_> const& x);
        explicit constexpr mat(mat<4, 4, Ty_> const& x);
        explicit constexpr mat(mat<2, 3, Ty_> const& x);
        explicit constexpr mat(mat<3, 2, Ty_> const& x);
        explicit constexpr mat(mat<2, 4, Ty_> const& x);
        explicit constexpr mat(mat<4, 2, Ty_> const& x);
        explicit constexpr mat(mat<3, 4, Ty_> const& x);
        explicit constexpr mat(mat<4, 3, Ty_> const& x);

        template<typename U>
        constexpr mat<3, 3, Ty_> & operator=(mat<3, 3, U> const& m);
        template<typename U>
        constexpr mat<3, 3, Ty_> & operator+=(U s);
        template<typename U>
        constexpr mat<3, 3, Ty_> & operator+=(mat<3, 3, U> const& m);
        template<typename U>
        constexpr mat<3, 3, Ty_> & operator-=(U s);
        template<typename U>
        constexpr mat<3, 3, Ty_> & operator-=(mat<3, 3, U> const& m);
        template<typename U>
        constexpr mat<3, 3, Ty_> & operator*=(U s);
        template<typename U>
        constexpr mat<3, 3, Ty_> & operator*=(mat<3, 3, U> const& m);
        template<typename U>
        constexpr mat<3, 3, Ty_> & operator/=(U s);
        template<typename U>
        constexpr mat<3, 3, Ty_> & operator/=(mat<3, 3, U> const& m);

        constexpr mat<3, 3, Ty_> & operator++();
        constexpr mat<3, 3, Ty_> & operator--();
        constexpr mat<3, 3, Ty_> operator++(int);
        constexpr mat<3, 3, Ty_> operator--(int);
    };

    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator+(mat<3, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator-(mat<3, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator+(mat<3, 3, Ty_> const& m, Ty_ scalar);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator+(Ty_ scalar, mat<3, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator+(mat<3, 3, Ty_> const& m1, mat<3, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator-(mat<3, 3, Ty_> const& m, Ty_ scalar);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator-(Ty_ scalar, mat<3, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator-(mat<3, 3, Ty_> const& m1, mat<3, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator*(mat<3, 3, Ty_> const& m, Ty_ scalar);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator*(Ty_ scalar, mat<3, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr typename mat<3, 3, Ty_>::col_type operator*(mat<3, 3, Ty_> const& m, typename mat<3, 3, Ty_>::row_type const& v);
    template<typename Ty_>
    constexpr typename mat<3, 3, Ty_>::row_type operator*(typename mat<3, 3, Ty_>::col_type const& v, mat<3, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator*(mat<3, 3, Ty_> const& m1, mat<3, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<2, 3, Ty_> operator*(mat<3, 3, Ty_> const& m1, mat<2, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator*(mat<3, 3, Ty_> const& m1, mat<4, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator/(mat<3, 3, Ty_> const& m, Ty_ scalar);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator/(Ty_ scalar, mat<3, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr typename mat<3, 3, Ty_>::col_type operator/(mat<3, 3, Ty_> const& m, typename mat<3, 3, Ty_>::row_type const& v);
    template<typename Ty_>
    constexpr typename mat<3, 3, Ty_>::row_type operator/(typename mat<3, 3, Ty_>::col_type const& v, mat<3, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator/(mat<3, 3, Ty_> const& m1, mat<3, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr bool operator==(mat<3, 3, Ty_> const& m1, mat<3, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr bool operator!=(mat<3, 3, Ty_> const& m1, mat<3, 3, Ty_> const& m2);
}

#endif //BLUEPRINT_MAT3X3_H
