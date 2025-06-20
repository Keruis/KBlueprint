#ifndef BLUEPRINT_MAT4X3_H
#define BLUEPRINT_MAT4X3_H

#include "BaseMat.h"
#include "../../Vec/include/Vec3.hpp"
#include "../../Vec/include/Vec4.hpp"
#include "../../../Attribute.h"

namespace Math::Mat {
    template<typename Ty_>
    struct mat<4, 3, Ty_> {
        typedef Vec::vec<3, Ty_> col_type;
        typedef Vec::vec<4, Ty_> row_type;
        typedef mat<4, 3, Ty_> type;
        typedef mat<3, 4, Ty_> transpose_type;
        typedef Ty_ value_type;

    private:
        col_type value[4];

    public:
        static constexpr std::size_t length(){return 4;}

        constexpr col_type & operator[](std::size_t i) noexcept;
        constexpr col_type const& operator[](std::size_t i) const noexcept;

        constexpr mat();
        explicit constexpr mat(Ty_ s);
        constexpr mat(
                Ty_ const& x0, Ty_ const& y0, Ty_ const& z0,
                Ty_ const& x1, Ty_ const& y1, Ty_ const& z1,
                Ty_ const& x2, Ty_ const& y2, Ty_ const& z2,
                Ty_ const& x3, Ty_ const& y3, Ty_ const& z3);
        constexpr mat(
                col_type const& v0,
                col_type const& v1,
                col_type const& v2,
                col_type const& v3);

        template<
                typename X1, typename Y1, typename Z1,
                typename X2, typename Y2, typename Z2,
                typename X3, typename Y3, typename Z3,
                typename X4, typename Y4, typename Z4>
        constexpr mat(
                X1 const& x1, Y1 const& y1, Z1 const& z1,
                X2 const& x2, Y2 const& y2, Z2 const& z2,
                X3 const& x3, Y3 const& y3, Z3 const& z3,
                X4 const& x4, Y4 const& y4, Z4 const& z4);

        template<typename V1, typename V2, typename V3, typename V4>
        constexpr mat(
                Vec::vec<3, V1> const& v1,
                Vec::vec<3, V2> const& v2,
                Vec::vec<3, V3> const& v3,
                Vec::vec<3, V4> const& v4);

        template<typename U>
        explicit constexpr mat(mat<4, 3, U> const& m);
        explicit constexpr mat(mat<2, 2, Ty_> const& x);
        explicit constexpr mat(mat<3, 3, Ty_> const& x);
        explicit constexpr mat(mat<4, 4, Ty_> const& x);
        explicit constexpr mat(mat<2, 3, Ty_> const& x);
        explicit constexpr mat(mat<3, 2, Ty_> const& x);
        explicit constexpr mat(mat<2, 4, Ty_> const& x);
        explicit constexpr mat(mat<4, 2, Ty_> const& x);
        explicit constexpr mat(mat<3, 4, Ty_> const& x);

        template<typename U>
        constexpr mat<4, 3, Ty_> & operator=(mat<4, 3, U> const& m);
        template<typename U>
        constexpr mat<4, 3, Ty_> & operator+=(U s);
        template<typename U>
        constexpr mat<4, 3, Ty_> & operator+=(mat<4, 3, U> const& m);
        template<typename U>
        constexpr mat<4, 3, Ty_> & operator-=(U s);
        template<typename U>
        constexpr mat<4, 3, Ty_> & operator-=(mat<4, 3, U> const& m);
        template<typename U>
        constexpr mat<4, 3, Ty_> & operator*=(U s);
        template<typename U>
        constexpr mat<4, 3, Ty_> & operator/=(U s);

        constexpr mat<4, 3, Ty_>& operator++();
        constexpr mat<4, 3, Ty_>& operator--();
        constexpr mat<4, 3, Ty_> operator++(int);
        constexpr mat<4, 3, Ty_> operator--(int);
    };

    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator+(mat<4, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator-(mat<4, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator+(mat<4, 3, Ty_> const& m, Ty_ scalar);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator+(mat<4, 3, Ty_> const& m1, mat<4, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator-(mat<4, 3, Ty_> const& m, Ty_ scalar);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator-(mat<4, 3, Ty_> const& m1, mat<4, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator*(mat<4, 3, Ty_> const& m, Ty_ scalar);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator*(Ty_ scalar, mat<4, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr typename mat<4, 3, Ty_>::col_type operator*(mat<4, 3, Ty_> const& m, typename mat<4, 3, Ty_>::row_type const& v);
    template<typename Ty_>
    constexpr typename mat<4, 3, Ty_>::row_type operator*(typename mat<4, 3, Ty_>::col_type const& v, mat<4, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr mat<2, 3, Ty_> operator*(mat<4, 3, Ty_> const& m1, mat<2, 4, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<3, 3, Ty_> operator*(mat<4, 3, Ty_> const& m1, mat<3, 4, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator*(mat<4, 3, Ty_> const& m1, mat<4, 4, Ty_> const& m2);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator/(mat<4, 3, Ty_> const& m, Ty_ scalar);
    template<typename Ty_>
    constexpr mat<4, 3, Ty_> operator/(Ty_ scalar, mat<4, 3, Ty_> const& m);
    template<typename Ty_>
    constexpr bool operator==(mat<4, 3, Ty_> const& m1, mat<4, 3, Ty_> const& m2);
    template<typename Ty_>
    constexpr bool operator!=(mat<4, 3, Ty_> const& m1, mat<4, 3, Ty_> const& m2);
}

#endif //BLUEPRINT_MAT4X3_H
