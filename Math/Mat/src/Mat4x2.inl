#include "../include/Mat4x2.hpp"

namespace Math::Mat {
    template <typename Ty_>
    constexpr typename mat<4, 2, Ty_>::col_type &mat<4, 2, Ty_>::operator[](std::size_t i) noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr const typename mat<4, 2, Ty_>::col_type &mat<4, 2, Ty_>::operator[](std::size_t i) const noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat()
        : value{col_type(1, 0), col_type(0, 1), col_type(0, 0), col_type(0, 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(Ty_ scalar)
        : value{col_type(scalar, 0), col_type(0, scalar), col_type(0, 0), col_type(0, 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(Ty_ x0, Ty_ y0, Ty_ x1, Ty_ y1, Ty_ x2, Ty_ y2, Ty_ x3, Ty_ y3)
        : value{col_type(x0, y0), col_type(x1, y1), col_type(x2, y2), col_type(x3, y3)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(const Math::Mat::mat<4, 2, Ty_>::col_type &v0,
                                  const Math::Mat::mat<4, 2, Ty_>::col_type &v1,
                                  const Math::Mat::mat<4, 2, Ty_>::col_type &v2,
                                  const Math::Mat::mat<4, 2, Ty_>::col_type &v3)
            : value{col_type(v0), col_type(v1), col_type(v2), col_type(v3)}
                                  {

                                  }

    template <typename Ty_>
    template<
            typename X0, typename Y0,
            typename X1, typename Y1,
            typename X2, typename Y2,
            typename X3, typename Y3>
    constexpr mat<4, 2, Ty_>::mat(X0 x0, Y0 y0, X1 x1, Y1 y1, X2 x2, Y2 y2, X3 x3, Y3 y3)
        : value{col_type(x0, y0), col_type(x1, y1), col_type(x2, y2), col_type(x3, y3)}
    {

    }

    template <typename Ty_>
    template<typename V1, typename V2, typename V3, typename V4>
    constexpr mat<4, 2, Ty_>::mat(const Vec::vec<2, V1> &v1, const Vec::vec<2, V2> &v2, const Vec::vec<2, V3> &v3,
                                  const Vec::vec<2, V4> &v4)
            : 	value{col_type(v1), col_type(v2), col_type(v3), col_type(v4)}
                                  {

                                  }

    template <typename Ty_>
    template <typename U>
    constexpr mat<4, 2, Ty_>::mat(const mat<4, 2, U> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(const mat<2, 2, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(0), col_type(0)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(const mat<3, 3, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(const mat<4, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(const mat<2, 3, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(0), col_type(0)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(const mat<3, 2, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(const mat<2, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(0), col_type(0)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(const mat<4, 3, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_>::mat(const mat<3, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0)}
    {

    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 2, Ty_>& mat<4, 2, Ty_>::operator=(mat<4, 2, U> const& m)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 2, Ty_> & mat<4, 2, Ty_>::operator+=(U s)
    {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        this->value[3] += s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 2, Ty_> & mat<4, 2, Ty_>::operator+=(mat<4, 2, U> const& m)
    {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
        this->value[3] += m[3];
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 2, Ty_> & mat<4, 2, Ty_>::operator-=(U s)
    {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        this->value[3] -= s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 2, Ty_> & mat<4, 2, Ty_>::operator-=(mat<4, 2, U> const& m)
    {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[2] -= m[2];
        this->value[3] -= m[3];
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 2, Ty_> & mat<4, 2, Ty_>::operator*=(U s)
    {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        this->value[3] *= s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 2, Ty_> & mat<4, 2, Ty_>::operator/=(U s)
    {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        this->value[3] /= s;
        return *this;
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> & mat<4, 2, Ty_>::operator++()
    {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        ++this->value[3];
        return *this;
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> & mat<4, 2, Ty_>::operator--()
    {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        --this->value[3];
        return *this;
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> mat<4, 2, Ty_>::operator++(int)
    {
        mat<4, 2, Ty_> Result(*this);
        ++*this;
        return Result;
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> mat<4, 2, Ty_>::operator--(int)
    {
        mat<4, 2, Ty_> Result(*this);
        --*this;
        return Result;
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator+(mat<4, 2, Ty_> const& m)
    {
        return m;
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator-(mat<4, 2, Ty_> const& m)
    {
        return mat<4, 2, Ty_>(
                -m[0],
                -m[1],
                -m[2],
                -m[3]);
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator+(mat<4, 2, Ty_> const& m, Ty_ scalar)
    {
        return mat<4, 2, Ty_>(
                m[0] + scalar,
                m[1] + scalar,
                m[2] + scalar,
                m[3] + scalar);
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator+(mat<4, 2, Ty_> const& m1, mat<4, 2, Ty_> const& m2)
    {
        return mat<4, 2, Ty_>(
                m1[0] + m2[0],
                m1[1] + m2[1],
                m1[2] + m2[2],
                m1[3] + m2[3]);
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator-(mat<4, 2, Ty_> const& m, Ty_ scalar)
    {
        return mat<4, 2, Ty_>(
                m[0] - scalar,
                m[1] - scalar,
                m[2] - scalar,
                m[3] - scalar);
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator-(mat<4, 2, Ty_> const& m1, mat<4, 2, Ty_> const& m2)
    {
        return mat<4, 2, Ty_>(
                m1[0] - m2[0],
                m1[1] - m2[1],
                m1[2] - m2[2],
                m1[3] - m2[3]);
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator*(mat<4, 2, Ty_> const& m, Ty_ scalar)
    {
        return mat<4, 2, Ty_>(
                m[0] * scalar,
                m[1] * scalar,
                m[2] * scalar,
                m[3] * scalar);
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator*(Ty_ scalar, mat<4, 2, Ty_> const& m)
    {
        return mat<4, 2, Ty_>(
                m[0] * scalar,
                m[1] * scalar,
                m[2] * scalar,
                m[3] * scalar);
    }

    template<typename Ty_>
    constexpr typename mat<4, 2, Ty_>::col_type operator*(mat<4, 2, Ty_> const& m, typename mat<4, 2, Ty_>::row_type const& v)
    {
        return typename mat<4, 2, Ty_>::col_type(
                m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
                m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w);
    }

    template<typename Ty_>
    constexpr typename mat<4, 2, Ty_>::row_type operator*(typename mat<4, 2, Ty_>::col_type const& v, mat<4, 2, Ty_> const& m)
    {
        return typename mat<4, 2, Ty_>::row_type(
                v.x * m[0][0] + v.y * m[0][1],
                v.x * m[1][0] + v.y * m[1][1],
                v.x * m[2][0] + v.y * m[2][1],
                v.x * m[3][0] + v.y * m[3][1]);
    }

    template<typename Ty_>
    constexpr mat<2, 2, Ty_> operator*(mat<4, 2, Ty_> const& m1, mat<2, 4, Ty_> const& m2)
    {
        Ty_ const SrcA00 = m1[0][0];
        Ty_ const SrcA01 = m1[0][1];
        Ty_ const SrcA10 = m1[1][0];
        Ty_ const SrcA11 = m1[1][1];
        Ty_ const SrcA20 = m1[2][0];
        Ty_ const SrcA21 = m1[2][1];
        Ty_ const SrcA30 = m1[3][0];
        Ty_ const SrcA31 = m1[3][1];

        Ty_ const SrcB00 = m2[0][0];
        Ty_ const SrcB01 = m2[0][1];
        Ty_ const SrcB02 = m2[0][2];
        Ty_ const SrcB03 = m2[0][3];
        Ty_ const SrcB10 = m2[1][0];
        Ty_ const SrcB11 = m2[1][1];
        Ty_ const SrcB12 = m2[1][2];
        Ty_ const SrcB13 = m2[1][3];

        mat<2, 2, Ty_> Result;
        Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02 + SrcA30 * SrcB03;
        Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02 + SrcA31 * SrcB03;
        Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12 + SrcA30 * SrcB13;
        Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12 + SrcA31 * SrcB13;
        return Result;
    }

    template<typename Ty_>
    constexpr mat<3, 2, Ty_> operator*(mat<4, 2, Ty_> const& m1, mat<3, 4, Ty_> const& m2)
    {
        return mat<3, 2, Ty_>(
                m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
                m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
                m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
                m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
                m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
                m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3]);
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator*(mat<4, 2, Ty_> const& m1, mat<4, 4, Ty_> const& m2)
    {
        return mat<4, 2, Ty_>(
                m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
                m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
                m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
                m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
                m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
                m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
                m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2] + m1[3][0] * m2[3][3],
                m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2] + m1[3][1] * m2[3][3]);
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator/(mat<4, 2, Ty_> const& m, Ty_ scalar)
    {
        return mat<4, 2, Ty_>(
                m[0] / scalar,
                m[1] / scalar,
                m[2] / scalar,
                m[3] / scalar);
    }

    template<typename Ty_>
    constexpr mat<4, 2, Ty_> operator/(Ty_ scalar, mat<4, 2, Ty_> const& m)
    {
        return mat<4, 2, Ty_>(
                scalar / m[0],
                scalar / m[1],
                scalar / m[2],
                scalar / m[3]);
    }

    template<typename Ty_>
    constexpr bool operator==(mat<4, 2, Ty_> const& m1, mat<4, 2, Ty_> const& m2)
    {
        return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
    }

    template<typename Ty_>
    constexpr bool operator!=(mat<4, 2, Ty_> const& m1, mat<4, 2, Ty_> const& m2)
    {
        return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
    }
}