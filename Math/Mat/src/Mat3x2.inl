#include "../include/Mat3x2.hpp"

namespace Math::Mat {
    template <typename Ty_>
    constexpr typename mat<3, 2, Ty_>::col_type &mat<3, 2, Ty_>::operator[](std::size_t i) noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr const typename mat<3, 2, Ty_>::col_type &mat<3, 2, Ty_>::operator[](std::size_t i) const noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat()
        : value{col_type(1, 0), col_type(0, 1), col_type(0, 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(Ty_ scalar)
        : value{col_type(scalar, 0), col_type(0, scalar), col_type(0, 0)}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(Ty_ x0, Ty_ y0, Ty_ x1, Ty_ y1, Ty_ x2, Ty_ y2)
        : value{col_type(x0, y0), col_type(x1, y1), col_type(x2, y2)}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(const Math::Mat::mat<3, 2, Ty_>::col_type &v0,
                                  const Math::Mat::mat<3, 2, Ty_>::col_type &v1,
                                  const Math::Mat::mat<3, 2, Ty_>::col_type &v2)
        : value{col_type(v0), col_type(v1), col_type(v2)}
    {

    }

    template <typename Ty_>
    template<
            typename X1, typename Y1,
            typename X2, typename Y2,
            typename X3, typename Y3>
    constexpr mat<3, 2, Ty_>::mat(X1 x1, Y1 y1, X2 x2, Y2 y2, X3 x3, Y3 y3)
        : value{col_type(x1, y1), col_type(x2, y2), col_type(x3, y3)}
    {

    }

    template <typename Ty_>
    template<typename V1, typename V2, typename V3>
    constexpr mat<3, 2, Ty_>::mat(const Vec::vec<2, V1> &v1, const Vec::vec<2, V2> &v2, const Vec::vec<2, V3> &v3)
        : value{col_type(v1), col_type(v2), col_type(v3)}
    {

    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<3, 2, Ty_>::mat(const mat<3, 2, U> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(const mat<2, 2, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(0)}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(const mat<3, 3, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(const mat<4, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(const mat<2, 3, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(0)}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(const mat<2, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(0)}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(const mat<3, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(const mat<4, 2, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
    {

    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_>::mat(const mat<4, 3, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2])}
    {

    }

    template <typename Ty_>
    template<typename U>
    constexpr mat<3, 2, Ty_>& mat<3, 2, Ty_>::operator=(mat<3, 2, U> const& m)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        return *this;
    }

    template <typename Ty_>
    template<typename U>
    constexpr mat<3, 2, Ty_>& mat<3, 2, Ty_>::operator+=(U s)
    {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        return *this;
    }

template <typename Ty_>
    template<typename U>
constexpr mat<3, 2, Ty_>& mat<3, 2, Ty_>::operator+=(mat<3, 2, U> const& m)
    {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
        return *this;
    }

template <typename Ty_>
    template<typename U>
constexpr mat<3, 2, Ty_>& mat<3, 2, Ty_>::operator-=(U s)
    {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        return *this;
    }

template <typename Ty_>
    template<typename U>
constexpr mat<3, 2, Ty_>& mat<3, 2, Ty_>::operator-=(mat<3, 2, U> const& m)
    {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[2] -= m[2];
        return *this;
    }

template <typename Ty_>
    template<typename U>
constexpr mat<3, 2, Ty_>& mat<3, 2, Ty_>::operator*=(U s)
    {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        return *this;
    }

template <typename Ty_>
    template<typename U>
constexpr mat<3, 2, Ty_> & mat<3, 2, Ty_>::operator/=(U s)
    {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        return *this;
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_>& mat<3, 2, Ty_>::operator++()
    {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        return *this;
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_>& mat<3, 2, Ty_>::operator--()
    {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        return *this;
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> mat<3, 2, Ty_>::operator++(int)
    {
        mat<3, 2, Ty_> Result(*this);
        ++*this;
        return Result;
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> mat<3, 2, Ty_>::operator--(int)
    {
        mat<3, 2, Ty_> Result(*this);
        --*this;
        return Result;
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator+(mat<3, 2, Ty_> const& m)
    {
    return m;
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator-(mat<3, 2, Ty_> const& m)
    {
    return mat<3, 2, Ty_>(
    -m[0],
    -m[1],
    -m[2]);
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator+(mat<3, 2, Ty_> const& m, Ty_ scalar)
    {
    return mat<3, 2, Ty_>(
            m[0] + scalar,
    m[1] + scalar,
    m[2] + scalar);
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator+(mat<3, 2, Ty_> const& m1, mat<3, 2, Ty_> const& m2)
    {
    return mat<3, 2, Ty_>(
            m1[0] + m2[0],
    m1[1] + m2[1],
    m1[2] + m2[2]);
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator-(mat<3, 2, Ty_> const& m, Ty_ scalar)
    {
    return mat<3, 2, Ty_>(
            m[0] - scalar,
    m[1] - scalar,
    m[2] - scalar);
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator-(mat<3, 2, Ty_> const& m1, mat<3, 2, Ty_> const& m2)
    {
    return mat<3, 2, Ty_>(
            m1[0] - m2[0],
    m1[1] - m2[1],
    m1[2] - m2[2]);
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator*(mat<3, 2, Ty_> const& m, Ty_ scalar)
    {
    return mat<3, 2, Ty_>(
            m[0] * scalar,
    m[1] * scalar,
    m[2] * scalar);
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator*(Ty_ scalar, mat<3, 2, Ty_> const& m)
    {
        return mat<3, 2, Ty_>(
                m[0] * scalar,
                m[1] * scalar,
                m[2] * scalar);
    }

template <typename Ty_>
constexpr typename mat<3, 2, Ty_>::col_type operator*(mat<3, 2, Ty_> const& m, typename mat<3, 2, Ty_>::row_type const& v)
    {
    return typename mat<3, 2, Ty_>::col_type(
            m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
    m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z);
    }

template <typename Ty_>
constexpr typename mat<3, 2, Ty_>::row_type operator*(typename mat<3, 2, Ty_>::col_type const& v, mat<3, 2, Ty_> const& m)
    {
        return typename mat<3, 2, Ty_>::row_type(
                v.x * m[0][0] + v.y * m[0][1],
                v.x * m[1][0] + v.y * m[1][1],
                v.x * m[2][0] + v.y * m[2][1]);
    }

template <typename Ty_>
constexpr mat<2, 2, Ty_> operator*(mat<3, 2, Ty_> const& m1, mat<2, 3, Ty_> const& m2)
    {
    const Ty_ SrcA00 = m1[0][0];
    const Ty_ SrcA01 = m1[0][1];
    const Ty_ SrcA10 = m1[1][0];
    const Ty_ SrcA11 = m1[1][1];
    const Ty_ SrcA20 = m1[2][0];
    const Ty_ SrcA21 = m1[2][1];

    const Ty_ SrcB00 = m2[0][0];
    const Ty_ SrcB01 = m2[0][1];
    const Ty_ SrcB02 = m2[0][2];
    const Ty_ SrcB10 = m2[1][0];
    const Ty_ SrcB11 = m2[1][1];
    const Ty_ SrcB12 = m2[1][2];

    mat<2, 2, Ty_> Result;
    Result[0][0] = SrcA00 * SrcB00 + SrcA10 * SrcB01 + SrcA20 * SrcB02;
    Result[0][1] = SrcA01 * SrcB00 + SrcA11 * SrcB01 + SrcA21 * SrcB02;
    Result[1][0] = SrcA00 * SrcB10 + SrcA10 * SrcB11 + SrcA20 * SrcB12;
    Result[1][1] = SrcA01 * SrcB10 + SrcA11 * SrcB11 + SrcA21 * SrcB12;
    return Result;
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator*(mat<3, 2, Ty_> const& m1, mat<3, 3, Ty_> const& m2)
    {
    return mat<3, 2, Ty_>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
    m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
    m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
    m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
    m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
    m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2]);
    }

template <typename Ty_>
constexpr mat<4, 2, Ty_> operator*(mat<3, 2, Ty_> const& m1, mat<4, 3, Ty_> const& m2)
    {
    return mat<4, 2, Ty_>(
            m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2],
    m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2],
    m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2],
    m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2],
    m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2],
    m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2],
    m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1] + m1[2][0] * m2[3][2],
    m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1] + m1[2][1] * m2[3][2]);
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator/(mat<3, 2, Ty_> const& m, Ty_ scalar)
    {
    return mat<3, 2, Ty_>(
            m[0] / scalar,
    m[1] / scalar,
    m[2] / scalar);
    }

template <typename Ty_>
constexpr mat<3, 2, Ty_> operator/(Ty_ scalar, mat<3, 2, Ty_> const& m)
    {
        return mat<3, 2, Ty_>(
                scalar / m[0],
                scalar / m[1],
                scalar / m[2]);
    }

template <typename Ty_>
constexpr bool operator==(mat<3, 2, Ty_> const& m1, mat<3, 2, Ty_> const& m2)
    {
    return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]);
    }

template <typename Ty_>
constexpr bool operator!=(mat<3, 2, Ty_> const& m1, mat<3, 2, Ty_> const& m2)
    {
    return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]);
    }
}