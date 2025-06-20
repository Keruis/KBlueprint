#include "../include/Mat2x4.hpp"

namespace Math::Mat {
    template <typename Ty_>
    constexpr typename mat<2, 4, Ty_>::col_type &mat<2, 4, Ty_>::operator[](std::size_t i) noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr const typename mat<2, 4, Ty_>::col_type &mat<2, 4, Ty_>::operator[](std::size_t i) const noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat()
        : value{col_type(1, 0, 0, 0), col_type(0, 1, 0, 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(Ty_ scalar)
        : value{col_type(scalar, 0, 0, 0), col_type(0, scalar, 0, 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(Ty_ x0, Ty_ y0, Ty_ z0, Ty_ w0, Ty_ x1, Ty_ y1, Ty_ z1, Ty_ w1)
        : value{col_type(x0, y0, z0, w0), col_type(x1, y1, z1, w1)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(const Math::Mat::mat<2, 4, Ty_>::col_type &v0,
                                  const Math::Mat::mat<2, 4, Ty_>::col_type &v1)
        : value{col_type(v0), col_type(v1)}
    {

    }

    template <typename Ty_>
    template<
            typename X1, typename Y1, typename Z1, typename W1,
            typename X2, typename Y2, typename Z2, typename W2>
    constexpr mat<2, 4, Ty_>::mat(X1 x1, Y1 y1, Z1 z1, W1 w1, X2 x2, Y2 y2, Z2 z2, W2 w2)
        : value{col_type(x1, y1, z1, w1), col_type(x2, y2, z2, w2)}
    {

    }

    template <typename Ty_>
    template<typename U, typename V>
    constexpr mat<2, 4, Ty_>::mat(const Vec::vec<4, U> &v1, const Vec::vec<4, V> &v2)
        : value{col_type(v1), col_type(v2)}
    {

    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 4, Ty_>::mat(const mat<2, 4, U> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(const mat<2, 2, Ty_> &m)
        : value{col_type(m[0], 0, 0), col_type(m[1], 0, 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(const mat<3, 3, Ty_> &m)
        : value{col_type(m[0], 0), col_type(m[1], 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(const mat<4, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(const mat<2, 3, Ty_> &m)
        : value{col_type(m[0], 0), col_type(m[1], 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(const mat<3, 2, Ty_> &m)
        : value{col_type(m[0], 0, 0), col_type(m[1], 0, 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(const mat<3, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(const mat<4, 2, Ty_> &m)
        : value{col_type(m[0], 0, 0), col_type(m[1], 0, 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 4, Ty_>::mat(const mat<4, 3, Ty_> &m)
        : value{col_type(m[0], 0), col_type(m[1], 0)}
    {

    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<2, 4, Ty_>& mat<2, 4, Ty_>::operator=(mat<2, 4, U> const& m)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<2, 4, Ty_>& mat<2, 4, Ty_>::operator+=(U s)
    {
        this->value[0] += s;
        this->value[1] += s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<2, 4, Ty_>& mat<2, 4, Ty_>::operator+=(mat<2, 4, U> const& m)
    {
        this->value[0] += m[0];
        this->value[1] += m[1];
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<2, 4, Ty_>& mat<2, 4, Ty_>::operator-=(U s)
    {
        this->value[0] -= s;
        this->value[1] -= s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<2, 4, Ty_>& mat<2, 4, Ty_>::operator-=(mat<2, 4, U> const& m)
    {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<2, 4, Ty_>& mat<2, 4, Ty_>::operator*=(U s)
    {
        this->value[0] *= s;
        this->value[1] *= s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<2, 4, Ty_> & mat<2, 4, Ty_>::operator/=(U s)
    {
        this->value[0] /= s;
        this->value[1] /= s;
        return *this;
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_>& mat<2, 4, Ty_>::operator++()
    {
        ++this->value[0];
        ++this->value[1];
        return *this;
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_>& mat<2, 4, Ty_>::operator--()
    {
        --this->value[0];
        --this->value[1];
        return *this;
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> mat<2, 4, Ty_>::operator++(int)
    {
        mat<2, 4, Ty_> Result(*this);
        ++*this;
        return Result;
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> mat<2, 4, Ty_>::operator--(int)
    {
        mat<2, 4, Ty_> Result(*this);
        --*this;
        return Result;
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator+(mat<2, 4, Ty_> const& m)
    {
        return m;
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator-(mat<2, 4, Ty_> const& m)
    {
        return mat<2, 4, Ty_>(
                -m[0],
                -m[1]);
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator+(mat<2, 4, Ty_> const& m, Ty_ scalar)
    {
        return mat<2, 4, Ty_>(
                m[0] + scalar,
                m[1] + scalar);
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator+(mat<2, 4, Ty_> const& m1, mat<2, 4, Ty_> const& m2)
    {
        return mat<2, 4, Ty_>(
                m1[0] + m2[0],
                m1[1] + m2[1]);
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator-(mat<2, 4, Ty_> const& m, Ty_ scalar)
    {
        return mat<2, 4, Ty_>(
                m[0] - scalar,
                m[1] - scalar);
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator-(mat<2, 4, Ty_> const& m1, mat<2, 4, Ty_> const& m2)
    {
        return mat<2, 4, Ty_>(
                m1[0] - m2[0],
                m1[1] - m2[1]);
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator*(mat<2, 4, Ty_> const& m, Ty_ scalar)
    {
        return mat<2, 4, Ty_>(
                m[0] * scalar,
                m[1] * scalar);
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator*(Ty_ scalar, mat<2, 4, Ty_> const& m)
    {
        return mat<2, 4, Ty_>(
                m[0] * scalar,
                m[1] * scalar);
    }

    template<typename Ty_>
    constexpr typename mat<2, 4, Ty_>::col_type operator*(mat<2, 4, Ty_> const& m, typename mat<2, 4, Ty_>::row_type const& v)
    {
        return typename mat<2, 4, Ty_>::col_type(
                m[0][0] * v.x + m[1][0] * v.y,
                m[0][1] * v.x + m[1][1] * v.y,
                m[0][2] * v.x + m[1][2] * v.y,
                m[0][3] * v.x + m[1][3] * v.y);
    }

    template<typename Ty_>
    constexpr typename mat<2, 4, Ty_>::row_type operator*(typename mat<2, 4, Ty_>::col_type const& v, mat<2, 4, Ty_> const& m)
    {
        return typename mat<2, 4, Ty_>::row_type(
                v.x * m[0][0] + v.y * m[0][1] + v.z * m[0][2] + v.w * m[0][3],
                v.x * m[1][0] + v.y * m[1][1] + v.z * m[1][2] + v.w * m[1][3]);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator*(mat<2, 4, Ty_> const& m1, mat<4, 2, Ty_> const& m2)
    {
        Ty_ SrcA00 = m1[0][0];
        Ty_ SrcA01 = m1[0][1];
        Ty_ SrcA02 = m1[0][2];
        Ty_ SrcA03 = m1[0][3];
        Ty_ SrcA10 = m1[1][0];
        Ty_ SrcA11 = m1[1][1];
        Ty_ SrcA12 = m1[1][2];
        Ty_ SrcA13 = m1[1][3];

        Ty_ SrcB00 = m2[0][0];
        Ty_ SrcB01 = m2[0][1];
        Ty_ SrcB10 = m2[1][0];
        Ty_ SrcB11 = m2[1][1];
        Ty_ SrcB20 = m2[2][0];
        Ty_ SrcB21 = m2[2][1];
        Ty_ SrcB30 = m2[3][0];
        Ty_ SrcB31 = m2[3][1];

        mat<4, 4, Ty_> Result;
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01;
        Result[0][2] = SrcA02 * SrcB00 + SrcA12 * SrcB01;
        Result[0][3] = SrcA03 * SrcB00 + SrcA13 * SrcB01;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11;
        Result[1][2] = SrcA02 * SrcB10 + SrcA12 * SrcB11;
        Result[1][3] = SrcA03 * SrcB10 + SrcA13 * SrcB11;
        Result[2][0] = SrcA00 * SrcB20 + SrcA10 * SrcB21;
        Result[2][1] = SrcA01 * SrcB20 + SrcA11 * SrcB21;
        Result[2][2] = SrcA02 * SrcB20 + SrcA12 * SrcB21;
        Result[2][3] = SrcA03 * SrcB20 + SrcA13 * SrcB21;
        Result[3][0] = SrcA00 * SrcB30 + SrcA10 * SrcB31;
        Result[3][1] = SrcA01 * SrcB30 + SrcA11 * SrcB31;
        Result[3][2] = SrcA02 * SrcB30 + SrcA12 * SrcB31;
        Result[3][3] = SrcA03 * SrcB30 + SrcA13 * SrcB31;
        return Result;
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator*(mat<2, 4, Ty_> const& m1, mat<2, 2, Ty_> const& m2)
    {
        return mat<2, 4, Ty_>(
                m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
                m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
                m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
                m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1],
                m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
                m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
                m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
                m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1]);
    }

    template<typename Ty_>
    constexpr mat<3, 4, Ty_> operator*(mat<2, 4, Ty_> const& m1, mat<3, 2, Ty_> const& m2)
    {
        return mat<3, 4, Ty_>(
                m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
                m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
                m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1],
                m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1],
                m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
                m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
                m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1],
                m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1],
                m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
                m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
                m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1],
                m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1]);
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator/(mat<2, 4, Ty_> const& m, Ty_ scalar)
    {
        return mat<2, 4, Ty_>(
                m[0] / scalar,
                m[1] / scalar);
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator/(Ty_ scalar, mat<2, 4, Ty_> const& m)
    {
        return mat<2, 4, Ty_>(
                scalar / m[0],
                scalar / m[1]);
    }

    template<typename Ty_>
    constexpr bool operator==(mat<2, 4, Ty_> const& m1, mat<2, 4, Ty_> const& m2)
    {
        return (m1[0] == m2[0]) && (m1[1] == m2[1]);
    }

    template<typename Ty_>
    constexpr bool operator!=(mat<2, 4, Ty_> const& m1, mat<2, 4, Ty_> const& m2)
    {
        return (m1[0] != m2[0]) || (m1[1] != m2[1]);
    }
}