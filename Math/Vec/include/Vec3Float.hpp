#ifndef BLUEPRINT_VEC3FLOAT_H
#define BLUEPRINT_VEC3FLOAT_H

#include "Vec3.hpp"

namespace Math::Vec {
    template <typename Ty_ = float>
    constexpr vec<3, Ty_> normalize(const vec<3, float>& v) {
        float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        return len == 0.0f ? v : vec<3, float>(v.x / len, v.y / len, v.z / len);
    }

    template <typename Ty_ = float>
    constexpr float dot(const vec<3, Ty_>& a, const vec<3, Ty_>& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    template <typename Ty_ = float>
    constexpr vec<3, Ty_> cross(const vec<3, float>& a, const vec<3, float>& b) {
        return vec<3, float>(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
        );
    }
}

#endif