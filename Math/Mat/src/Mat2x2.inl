#include "../include/Mat2x2.hpp"

namespace Math::Mat {
    template <typename Ty_>
    constexpr typename mat<2, 2, Ty_>::col_type& mat<2, 2, Ty_>::operator[](std::size_t i) noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr const typename mat<2, 2, Ty_>::col_type &mat<2, 2, Ty_>::operator[](std::size_t i) const noexcept {
        return this->value[i];
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat()
        : value{col_type(1, 0), col_type(0, 1)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const mat<2, 2, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(Ty_ scalar)
        : value{col_type(scalar, 0), col_type(0, scalar)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const Ty_ &x1, const Ty_ &y1, const Ty_ &x2, const Ty_ &y2)
        : value{col_type(x1, y1), col_type(x2, y2)}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const Math::Mat::mat<2, 2, Ty_>::col_type &v1,
                                  const Math::Mat::mat<2, 2, Ty_>::col_type &v2)
                                  : value{v1, v2}
    {

    }

    template <typename Ty_>
    template <typename U, typename V, typename M, typename N>
    constexpr mat<2, 2, Ty_>::mat(const U &x1, const V &y1, const M &x2, const N &y2)
        : value{col_type(static_cast<Ty_>(x1), value_type(y1)), col_type(static_cast<Ty_>(x2), value_type(y2))}
    {

    }

    template <typename Ty_>
    template <typename U, typename V>
    constexpr mat<2, 2, Ty_>::mat(const Vec::vec<2, U> &v1, const Vec::vec<2, V> &v2)
        : value{col_type(v1), col_type(v2)}
    {

    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>::mat(const mat<2, 2, U> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const mat<3, 3, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const mat<4, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const mat<2, 3, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const mat<3, 2, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2 ,Ty_>::mat(const mat<2, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const mat<4, 2, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const mat<3, 4, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>::mat(const mat<4, 3, Ty_> &m)
        : value{col_type(m[0]), col_type(m[1])}
    {

    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator=(mat<2, 2, U> const& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];
        return *this;
    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator+=(U scalar) {
        this->value[0] += scalar;
        this->value[1] += scalar;
        return *this;
    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator+=(mat<2, 2, U> const& m) {
        this->value[0] += m[0];
        this->value[1] += m[1];
        return *this;
    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator-=(U scalar) {
        this->value[0] -= scalar;
        this->value[1] -= scalar;
        return *this;
    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator-=(mat<2, 2, U> const& m) {
        this->value[0] -= m[0];
        this->value[1] -= m[1];
        return *this;
    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator*=(U scalar) {
        this->value[0] *= scalar;
        this->value[1] *= scalar;
        return *this;
    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator*=(mat<2, 2, U> const& m) {
        return (*this = *this * m);
    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator/=(U scalar) {
        this->value[0] /= scalar;
        this->value[1] /= scalar;
        return *this;
    }

    template <typename Ty_>
    template <typename U>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator/=(mat<2, 2, U> const& m) {
        return *this *= inverse(m);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator++() {
        ++this->value[0];
        ++this->value[1];
        return *this;
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_>& mat<2, 2, Ty_>::operator--() {
        --this->value[0];
        --this->value[1];
        return *this;
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> mat<2, 2, Ty_>::operator++(int) {
        mat<2, 2, Ty_> Result(*this);
        ++*this;
        return Result;
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> mat<2, 2, Ty_>::operator--(int) {
        mat<2, 2, Ty_> Result(*this);
        --*this;
        return Result;
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator+(mat<2, 2, Ty_> const& m) {
        return m;
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator-(mat<2, 2, Ty_> const& m) {
        return mat<2, 2, Ty_>(
                -m[0],
                -m[1]);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator+(mat<2, 2, Ty_> const& m, Ty_ scalar) {
        return mat<2, 2, Ty_>(
                m[0] + scalar,
                m[1] + scalar);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator+(Ty_ scalar, mat<2, 2, Ty_> const& m) {
        return mat<2, 2, Ty_>(
                m[0] + scalar,
                m[1] + scalar);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator+(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2) {
        return mat<2, 2, Ty_>(
                m1[0] + m2[0],
                m1[1] + m2[1]);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator-(mat<2, 2, Ty_> const& m, Ty_ scalar) {
        return mat<2, 2, Ty_>(
                m[0] - scalar,
                m[1] - scalar);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator-(Ty_ scalar, mat<2, 2, Ty_> const& m) {
        return mat<2, 2, Ty_>(
                scalar - m[0],
                scalar - m[1]);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator-(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2) {
        return mat<2, 2, Ty_>(
                m1[0] - m2[0],
                m1[1] - m2[1]);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator*(mat<2, 2, Ty_> const& m, Ty_ scalar) {
        return mat<2, 2, Ty_>(
                m[0] * scalar,
                m[1] * scalar);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator*(Ty_ scalar, mat<2, 2, Ty_> const& m) {
        return mat<2, 2, Ty_>(
                m[0] * scalar,
                m[1] * scalar);
    }

    template <typename Ty_>
    constexpr typename mat<2, 2, Ty_>::col_type operator*(
        mat<2, 2, Ty_> const& m,
        typename mat<2, 2, Ty_>::row_type const& v
    ) {
        return Vec::vec<2, Ty_>(
                m[0][0] * v.x + m[1][0] * v.y,
                m[0][1] * v.x + m[1][1] * v.y);
    }

    template <typename Ty_>
    constexpr typename mat<2, 2, Ty_>::row_type operator*(
        typename mat<2, 2, Ty_>::col_type const& v,
        mat<2, 2, Ty_> const& m
    ) {
        return Vec::vec<2, Ty_>(
                v.x * m[0][0] + v.y * m[0][1],
                v.x * m[1][0] + v.y * m[1][1]);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator*(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2) {
        return mat<2, 2, Ty_>(
                m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
                m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
                m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
                m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]);
    }

    template <typename Ty_>
    constexpr mat<3, 2, Ty_> operator*(mat<2, 2, Ty_> const& m1, mat<3, 2, Ty_> const& m2) {
        return mat<3, 2, Ty_>(
                m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
                m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
                m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
                m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
                m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
                m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1]);
    }

    template <typename Ty_>
    constexpr mat<4, 2, Ty_> operator*(mat<2, 2, Ty_> const& m1, mat<4, 2, Ty_> const& m2) {
        return mat<4, 2, Ty_>(
                m1[0][0] * m2[0][0] + m1[1][0] * m2[0][1],
                m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
                m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
                m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1],
                m1[0][0] * m2[2][0] + m1[1][0] * m2[2][1],
                m1[0][1] * m2[2][0] + m1[1][1] * m2[2][1],
                m1[0][0] * m2[3][0] + m1[1][0] * m2[3][1],
                m1[0][1] * m2[3][0] + m1[1][1] * m2[3][1]);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator/(mat<2, 2, Ty_> const& m, Ty_ scalar) {
        return mat<2, 2, Ty_>(
                m[0] / scalar,
                m[1] / scalar);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator/(Ty_ scalar, mat<2, 2, Ty_> const& m) {
        return mat<2, 2, Ty_>(
                scalar / m[0],
                scalar / m[1]);
    }

    template <typename Ty_>
    constexpr typename mat<2, 2, Ty_>::col_type operator/(mat<2, 2, Ty_> const& m, typename mat<2, 2, Ty_>::row_type const& v) {
        return inverse(m) * v;
    }

    template <typename Ty_>
    constexpr typename mat<2, 2, Ty_>::row_type operator/(typename mat<2, 2, Ty_>::col_type const& v, mat<2, 2, Ty_> const& m) {
        return v *  inverse(m);
    }

    template <typename Ty_>
    constexpr mat<2, 2, Ty_> operator/(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2) {
        mat<2, 2, Ty_> m1_copy(m1);
        return m1_copy /= m2;
    }

    template <typename Ty_>
    constexpr bool operator==(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2) {
        return (m1[0] == m2[0]) && (m1[1] == m2[1]);
    }

    template <typename Ty_>
    constexpr bool operator!=(mat<2, 2, Ty_> const& m1, mat<2, 2, Ty_> const& m2) {
        return (m1[0] != m2[0]) || (m1[1] != m2[1]);
    }
}