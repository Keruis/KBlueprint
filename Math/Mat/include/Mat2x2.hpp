#ifndef BLUEPRINT_MAT2X2_H
#define BLUEPRINT_MAT2X2_H

#include "BaseMat.h"
#include "../../Vec/include/Vec2.hpp"
#include "../../../Attribute.h"

namespace Math::Mat {
    template <typename Ty_>
    struct mat<2, 2, Ty_> {
        typedef Vec::vec<2, Ty_> col_type;
        typedef Vec::vec<2, Ty_> row_type;
        typedef mat<2, 2, Ty_> type;
        typedef mat<2, 2, Ty_> transpose_type;
        typedef Ty_ value_type;

        private:
            col_type value[2];

        public:
        OPTIMIZE_O3 ALWAYS_INLINE
        static constexpr std::size_t length() { return 2; }

        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr col_type& operator[](std::size_t i) noexcept;
        OPTIMIZE_O3 ALWAYS_INLINE
        constexpr col_type const& operator[](std::size_t i) const noexcept;

        constexpr mat();
        constexpr mat(mat<2, 2, Ty_> const& m);
        explicit constexpr mat(Ty_ scalar);
        constexpr mat(Ty_ const& x1, Ty_ const& y1, Ty_ const& x2, Ty_ const& y2);
        constexpr mat(col_type const& v1, col_type const& v2);
        template<typename U, typename V, typename M, typename N>
        constexpr mat(U const& x1, V const& y1, M const& x2, N const& y2);
        template<typename U, typename V>
        constexpr mat(Vec::vec<2, U> const& v1, Vec::vec<2, V> const& v2);
        template<typename U>
        explicit constexpr mat(mat<2, 2, U> const& m);
        explicit constexpr mat(mat<3, 3, Ty_> const& m);
        explicit constexpr mat(mat<4, 4, Ty_> const& m);
        explicit constexpr mat(mat<2, 3, Ty_> const& m);
        explicit constexpr mat(mat<3, 2, Ty_> const& m);
        explicit constexpr mat(mat<2, 4, Ty_> const& m);
        explicit constexpr mat(mat<4, 2, Ty_> const& m);
        explicit constexpr mat(mat<3, 4, Ty_> const& m);
        explicit constexpr mat(mat<4, 3, Ty_> const& m);

        template <typename U_> constexpr mat<2, 2, Ty_> & operator=(mat<2, 2, U_> const& m);
        template <typename U_> constexpr mat<2, 2, Ty_> & operator+=(U_ s);
        template <typename U_> constexpr mat<2, 2, Ty_> & operator+=(mat<2, 2, U_> const& m);
        template <typename U_> constexpr mat<2, 2, Ty_> & operator-=(U_ s);
        template <typename U_> constexpr mat<2, 2, Ty_> & operator-=(mat<2, 2, U_> const& m);
        template <typename U_> constexpr mat<2, 2, Ty_> & operator*=(U_ s);
        template <typename U_> constexpr mat<2, 2, Ty_> & operator*=(mat<2, 2, U_> const& m);
        template <typename U_> constexpr mat<2, 2, Ty_> & operator/=(U_ s);
        template <typename U_> constexpr mat<2, 2, Ty_> & operator/=(mat<2, 2, U_> const& m);


        constexpr mat<2, 2, Ty_> & operator++ ();
        constexpr mat<2, 2, Ty_> & operator-- ();
        constexpr mat<2, 2, Ty_> operator++(int);
        constexpr mat<2, 2, Ty_> operator--(int);
    };

    template <typename Ty_> constexpr mat<2, 2, Ty_> operator+(mat<2, 2, Ty_> const& m);
    template <typename Ty_> constexpr mat<2, 2, Ty_> operator-(mat<2, 2, Ty_> const& m);
    template <typename Ty_> constexpr mat<2, 2, Ty_> operator+(mat<2, 2, Ty_> const& m, Ty_ scalar);
    template <typename Ty_> constexpr mat<2, 2, Ty_> operator+(Ty_ scalar, mat<2, 2, Ty_> const& m);
    template <typename Ty_> constexpr mat<2, 2, Ty_> operator+(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2);
    template <typename Ty_> constexpr mat<2, 2, Ty_> operator-(mat<2, 2, Ty_> const& m, Ty_ scalar);
    template <typename Ty_> constexpr mat<2, 2, Ty_> operator-(Ty_ scalar, mat<2, 2, Ty_> const& m);
    template <typename Ty_> constexpr mat<2, 2, Ty_> operator-(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2);
    template <typename Ty_> constexpr mat<2, 2, Ty_> operator*(mat<2, 2, Ty_> const& m, Ty_ scalar);
    template <typename Ty_> constexpr mat<2, 2, Ty_> operator*(Ty_ scalar, mat<2, 2, Ty_> const& m);
    template <typename Ty_> constexpr typename mat<2, 2, Ty_>::col_type operator*(mat<2, 2, Ty_> const& m, typename mat<2, 2, Ty_>::row_type const& v);
    template<typename Ty_> constexpr typename mat<2, 2, Ty_>::row_type operator*(typename mat<2, 2, Ty_>::col_type const& v, mat<2, 2, Ty_> const& m);
    template<typename Ty_> constexpr mat<2, 2, Ty_> operator*(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2);
    template<typename Ty_> constexpr mat<3, 2, Ty_> operator*(mat<2, 2, Ty_> const& m1, mat<3, 2, Ty_> const& m2);
    template<typename Ty_> constexpr mat<4, 2, Ty_> operator*(mat<2, 2, Ty_> const& m1, mat<4, 2, Ty_> const& m2);
    template<typename Ty_> constexpr mat<2, 2, Ty_> operator/(mat<2, 2, Ty_> const& m, Ty_ scalar);
    template<typename Ty_> constexpr mat<2, 2, Ty_> operator/(Ty_ scalar, mat<2, 2, Ty_> const& m);
    template<typename Ty_> constexpr typename mat<2, 2, Ty_>::col_type operator/(mat<2, 2, Ty_> const& m, typename mat<2, 2, Ty_>::row_type const& v);
    template<typename Ty_> constexpr typename mat<2, 2, Ty_>::row_type operator/(typename mat<2, 2, Ty_>::col_type const& v, mat<2, 2, Ty_> const& m);
    template<typename Ty_> constexpr mat<2, 2, Ty_> operator/(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2);
    template <typename Ty_> constexpr bool operator==(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2);
    template <typename Ty_> constexpr bool operator!=(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2);
}

#include "../src/Mat2x2.inl"

#endif //BLUEPRINT_MAT2X2_H
