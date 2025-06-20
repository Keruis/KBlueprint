#include "../include/Mat4x4.hpp"

namespace Math::Mat {
    template <typename Ty_>
    constexpr typename mat<4, 4, Ty_>::col_type &mat<4, 4, Ty_>::operator[](std::size_t i) noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr const typename mat<4, 4, Ty_>::col_type &mat<4, 4, Ty_>::operator[](std::size_t i) const noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat()
        : value{col_type(1, 0, 0, 0), col_type(0, 1, 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(Ty_ s)
        : value{col_type(s, 0, 0, 0), col_type(0, s, 0, 0), col_type(0, 0, s, 0), col_type(0, 0, 0, s)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const Ty_ &x0, const Ty_ &y0, const Ty_ &z0, const Ty_ &w0, const Ty_ &x1,
                                  const Ty_ &y1, const Ty_ &z1, const Ty_ &w1, const Ty_ &x2, const Ty_ &y2,
                                  const Ty_ &z2, const Ty_ &w2, const Ty_ &x3, const Ty_ &y3, const Ty_ &z3,
                                  const Ty_ &w3)
                                  : value{
            col_type(x0, y0, z0, w0),
            col_type(x1, y1, z1, w1),
            col_type(x2, y2, z2, w2),
            col_type(x3, y3, z3, w3)}
                                  {

                                  }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const Math::Mat::mat<4, 4, Ty_>::col_type &v0,
                                  const Math::Mat::mat<4, 4, Ty_>::col_type &v1,
                                  const Math::Mat::mat<4, 4, Ty_>::col_type &v2,
                                  const Math::Mat::mat<4, 4, Ty_>::col_type &v3)
        : value{col_type(v0), col_type(v1), col_type(v2), col_type(v3)}
                                  {

                                  }

    template <typename Ty_>
    template <typename U>
    constexpr mat<4, 4, Ty_>::mat(const mat<4, 4, U> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(m[3])}
    {

    }

    template <typename Ty_>
    template<
            typename X1, typename Y1, typename Z1, typename W1,
            typename X2, typename Y2, typename Z2, typename W2,
            typename X3, typename Y3, typename Z3, typename W3,
            typename X4, typename Y4, typename Z4, typename W4>
    constexpr mat<4, 4, Ty_>::mat(const X1 &x1, const Y1 &y1, const Z1 &z1, const W1 &w1, const X2 &x2, const Y2 &y2,
                                  const Z2 &z2, const W2 &w2, const X3 &x3, const Y3 &y3, const Z3 &z3, const W3 &w3,
                                  const X4 &x4, const Y4 &y4, const Z4 &z4, const W4 &w4)
            : value{col_type(x1, y1, z1, w1), col_type(x2, y2, z2, w2), col_type(x3, y3, z3, w3), col_type(x4, y4, z4, w4)}
                                  {

                                  }

    template <typename Ty_>
    template<typename V1, typename V2, typename V3, typename V4>
    constexpr mat<4, 4, Ty_>::mat(const Vec::vec<4, V1> &v1, const Vec::vec<4, V2> &v2, const Vec::vec<4, V3> &v3,
                                  const Vec::vec<4, V4> &v4)
        : value{col_type(v1), col_type(v2), col_type(v3), col_type(v4)}
                                  {

                                  }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const mat<2, 2, Ty_> &m)
        : value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const mat<3, 3, Ty_> &m)
        : value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 0), col_type(0, 0, 0, 1)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const mat<2, 3, Ty_> &m)
        : value{col_type(m[0], 0), col_type(m[1], 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const mat<3, 2, Ty_> &m)
        : value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(m[2], 1, 0), col_type(0, 0, 0, 1)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const mat<2, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const mat<4, 2, Ty_> &m)
        : value{col_type(m[0], 0, 0), col_type(m[1], 0, 0), col_type(0, 0, 1, 0), col_type(0, 0, 0, 1)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const mat<3, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1]), col_type(m[2]), col_type(0, 0, 0, 1)}
    {

    }

    template <typename Ty_>
    constexpr mat<4, 4, Ty_>::mat(const mat<4, 3, Ty_> &m)
        : value{col_type(m[0], 0), col_type(m[1], 0), col_type(m[2], 0), col_type(m[3], 1)}
    {

    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 4, Ty_>& mat<4, 4, Ty_>::operator=(mat<4, 4, U> const& m)
    {
        this->value[0] = m[0];
        this->value[1] = m[1];
        this->value[2] = m[2];
        this->value[3] = m[3];
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 4, Ty_>& mat<4, 4, Ty_>::operator+=(U s)
    {
        this->value[0] += s;
        this->value[1] += s;
        this->value[2] += s;
        this->value[3] += s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 4, Ty_>& mat<4, 4, Ty_>::operator+=(mat<4, 4, U> const& m)
    {
        this->value[0] += m[0];
        this->value[1] += m[1];
        this->value[2] += m[2];
        this->value[3] += m[3];
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 4, Ty_> & mat<4, 4, Ty_>::operator-=(U s)
    {
        this->value[0] -= s;
        this->value[1] -= s;
        this->value[2] -= s;
        this->value[3] -= s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 4, Ty_> & mat<4, 4, Ty_>::operator-=(mat<4, 4, U> const& m)
    {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        this->value[2] -= m[2];
        this->value[3] -= m[3];
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 4, Ty_> & mat<4, 4, Ty_>::operator*=(U s)
    {
        this->value[0] *= s;
        this->value[1] *= s;
        this->value[2] *= s;
        this->value[3] *= s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 4, Ty_> & mat<4, 4, Ty_>::operator*=(mat<4, 4, U> const& m)
    {
        return (*this = *this * m);
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 4, Ty_> & mat<4, 4, Ty_>::operator/=(U s)
    {
        this->value[0] /= s;
        this->value[1] /= s;
        this->value[2] /= s;
        this->value[3] /= s;
        return *this;
    }

    template<typename Ty_>
    template<typename U>
    constexpr mat<4, 4, Ty_> & mat<4, 4, Ty_>::operator/=(mat<4, 4, U> const& m)
    {
        return *this *= inverse(m);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> & mat<4, 4, Ty_>::operator++()
    {
        ++this->value[0];
        ++this->value[1];
        ++this->value[2];
        ++this->value[3];
        return *this;
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> & mat<4, 4, Ty_>::operator--()
    {
        --this->value[0];
        --this->value[1];
        --this->value[2];
        --this->value[3];
        return *this;
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> mat<4, 4, Ty_>::operator++(int)
    {
        mat<4, 4, Ty_> Result(*this);
        ++*this;
        return Result;
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> mat<4, 4, Ty_>::operator--(int)
    {
        mat<4, 4, Ty_> Result(*this);
        --*this;
        return Result;
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator+(mat<4, 4, Ty_> const& m)
    {
        return m;
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator-(mat<4, 4, Ty_> const& m)
    {
        return mat<4, 4, Ty_>(
                -m[0],
                -m[1],
                -m[2],
                -m[3]);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator+(mat<4, 4, Ty_> const& m, Ty_ scalar)
    {
        return mat<4, 4, Ty_>(
                m[0] + scalar,
                m[1] + scalar,
                m[2] + scalar,
                m[3] + scalar);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator+(Ty_ scalar, mat<4, 4, Ty_> const& m)
    {
        return mat<4, 4, Ty_>(
                m[0] + scalar,
                m[1] + scalar,
                m[2] + scalar,
                m[3] + scalar);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator+(mat<4, 4, Ty_> const& m1, mat<4, 4, Ty_> const& m2)
    {
        return mat<4, 4, Ty_>(
                m1[0] + m2[0],
                m1[1] + m2[1],
                m1[2] + m2[2],
                m1[3] + m2[3]);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator-(mat<4, 4, Ty_> const& m, Ty_ scalar)
    {
        return mat<4, 4, Ty_>(
                m[0] - scalar,
                m[1] - scalar,
                m[2] - scalar,
                m[3] - scalar);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator-(Ty_ scalar, mat<4, 4, Ty_> const& m)
    {
        return mat<4, 4, Ty_>(
                scalar - m[0],
                scalar - m[1],
                scalar - m[2],
                scalar - m[3]);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator-(mat<4, 4, Ty_> const& m1, mat<4, 4, Ty_> const& m2)
    {
        return mat<4, 4, Ty_>(
                m1[0] - m2[0],
                m1[1] - m2[1],
                m1[2] - m2[2],
                m1[3] - m2[3]);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator*(mat<4, 4, Ty_> const& m, Ty_ scalar)
    {
        return mat<4, 4, Ty_>(
                m[0] * scalar,
                m[1] * scalar,
                m[2] * scalar,
                m[3] * scalar);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator*(Ty_ scalar, mat<4, 4, Ty_> const& m)
    {
        return mat<4, 4, Ty_>(
                m[0] * scalar,
                m[1] * scalar,
                m[2] * scalar,
                m[3] * scalar);
    }

    template<typename Ty_>
    constexpr typename mat<4, 4, Ty_>::col_type operator*
            (
                    mat<4, 4, Ty_> const& m,
                    typename mat<4, 4, Ty_>::row_type const& v
            )
    {
        typename mat<4, 4, Ty_>::col_type const Mov0(v[0]);
        typename mat<4, 4, Ty_>::col_type const Mov1(v[1]);
        typename mat<4, 4, Ty_>::col_type const Mul0 = m[0] * Mov0;
        typename mat<4, 4, Ty_>::col_type const Mul1 = m[1] * Mov1;
        typename mat<4, 4, Ty_>::col_type const Add0 = Mul0 + Mul1;
        typename mat<4, 4, Ty_>::col_type const Mov2(v[2]);
        typename mat<4, 4, Ty_>::col_type const Mov3(v[3]);
        typename mat<4, 4, Ty_>::col_type const Mul2 = m[2] * Mov2;
        typename mat<4, 4, Ty_>::col_type const Mul3 = m[3] * Mov3;
        typename mat<4, 4, Ty_>::col_type const Add1 = Mul2 + Mul3;
        typename mat<4, 4, Ty_>::col_type const Add2 = Add0 + Add1;
        return Add2;
    }

    template<typename Ty_>
    constexpr typename mat<4, 4, Ty_>::row_type operator*(
            const typename mat<4, 4, Ty_>::col_type& v,
            const mat<4, 4, Ty_>& m
    ) {
        return typename mat<4, 4, Ty_>::row_type{
                m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
                m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
                m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
                m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]
        };
    }

    template<typename Ty_>
    constexpr mat<2, 4, Ty_> operator*(mat<4, 4, Ty_> const& m1, mat<2, 4, Ty_> const& m2)
    {
        return mat<2, 4, Ty_>(
                m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
                m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
                m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
                m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
                m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
                m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
                m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
                m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3]);
    }

    template<typename Ty_>
    constexpr mat<3, 4, Ty_> operator*(mat<4, 4, Ty_> const& m1, mat<3, 4, Ty_> const& m2)
    {
        return mat<3, 4, Ty_>(
                m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1] + m1[2][0] * m2[0][2] + m1[3][0] * m2[0][3],
                m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1] + m1[2][1] * m2[0][2] + m1[3][1] * m2[0][3],
                m1[0][2] * m2[0][0] + m1[1][2] * m2[0][1] + m1[2][2] * m2[0][2] + m1[3][2] * m2[0][3],
                m1[0][3] * m2[0][0] + m1[1][3] * m2[0][1] + m1[2][3] * m2[0][2] + m1[3][3] * m2[0][3],
                m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1] + m1[2][0] * m2[1][2] + m1[3][0] * m2[1][3],
                m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1] + m1[2][1] * m2[1][2] + m1[3][1] * m2[1][3],
                m1[0][2] * m2[1][0] + m1[1][2] * m2[1][1] + m1[2][2] * m2[1][2] + m1[3][2] * m2[1][3],
                m1[0][3] * m2[1][0] + m1[1][3] * m2[1][1] + m1[2][3] * m2[1][2] + m1[3][3] * m2[1][3],
                m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1] + m1[2][0] * m2[2][2] + m1[3][0] * m2[2][3],
                m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1] + m1[2][1] * m2[2][2] + m1[3][1] * m2[2][3],
                m1[0][2] * m2[2][0] + m1[1][2] * m2[2][1] + m1[2][2] * m2[2][2] + m1[3][2] * m2[2][3],
                m1[0][3] * m2[2][0] + m1[1][3] * m2[2][1] + m1[2][3] * m2[2][2] + m1[3][3] * m2[2][3]);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator*(const mat<4, 4, Ty_>& m1, const mat<4, 4, Ty_>& m2)
    {
        using vec4 = typename mat<4, 4, Ty_>::col_type;
        mat<4, 4, Ty_> result{};

        const vec4& A0 = m1[0];
        const vec4& A1 = m1[1];
        const vec4& A2 = m1[2];
        const vec4& A3 = m1[3];

        const vec4& B0 = m2[0];
        const vec4& B1 = m2[1];
        const vec4& B2 = m2[2];
        const vec4& B3 = m2[3];

        result[0] = A0 * B0[0] + A1 * B0[1] + A2 * B0[2] + A3 * B0[3];
        result[1] = A0 * B1[0] + A1 * B1[1] + A2 * B1[2] + A3 * B1[3];
        result[2] = A0 * B2[0] + A1 * B2[1] + A2 * B2[2] + A3 * B2[3];
        result[3] = A0 * B3[0] + A1 * B3[1] + A2 * B3[2] + A3 * B3[3];

        return result;
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator/(mat<4, 4, Ty_> const& m, Ty_ scalar)
    {
        return mat<4, 4, Ty_>(
                m[0] / scalar,
                m[1] / scalar,
                m[2] / scalar,
                m[3] / scalar);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator/(Ty_ scalar,	mat<4, 4, Ty_> const& m)
    {
        return mat<4, 4, Ty_>(
                scalar / m[0],
                scalar / m[1],
                scalar / m[2],
                scalar / m[3]);
    }

    template<typename Ty_>
    constexpr typename mat<4, 4, Ty_>::col_type operator/(mat<4, 4, Ty_> const& m, typename mat<4, 4, Ty_>::row_type const& v)
    {
        return inverse(m) * v;
    }

    template<typename Ty_>
    constexpr typename mat<4, 4, Ty_>::row_type operator/(typename mat<4, 4, Ty_>::col_type const& v, mat<4, 4, Ty_> const& m)
    {
        return v * inverse(m);
    }

    template<typename Ty_>
    constexpr mat<4, 4, Ty_> operator/(mat<4, 4, Ty_> const& m1, mat<4, 4, Ty_> const& m2)
    {
        mat<4, 4, Ty_> m1_copy(m1);
        return m1_copy /= m2;
    }

    template<typename Ty_>
    constexpr bool operator==(mat<4, 4, Ty_> const& m1, mat<4, 4, Ty_> const& m2)
    {
        return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
    }

    template<typename Ty_>
    constexpr bool operator!=(mat<4, 4, Ty_> const& m1, mat<4, 4, Ty_> const& m2)
    {
        return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
    }
}