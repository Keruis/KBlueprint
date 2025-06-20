#ifndef BLUEPRINT_MAT4X4FLOAT_H
#define BLUEPRINT_MAT4X4FLOAT_H

#include "Mat4x4.hpp"
#include "../../Vec/include/Vec3Float.hpp"

namespace Math::Mat {
    template <typename Ty_ = float>
    constexpr mat<4, 4, Ty_> RotationRollPitchYaw(Ty_ pitch, Ty_ yaw, Ty_ roll) {
        const Ty_ cp = std::cos(pitch);
        const Ty_ sp = std::sin(pitch);

        const Ty_ cy = std::cos(yaw);
        const Ty_ sy = std::sin(yaw);

        const Ty_ cr = std::cos(roll);
        const Ty_ sr = std::sin(roll);

        mat<4, 4, Ty_> rotX = {
                1, 0,  0, 0,
                0, cp, sp, 0,
                0,-sp, cp, 0,
                0, 0,  0, 1,
        };

        mat<4, 4, Ty_> rotY = {
                cy, 0, -sy, 0,
                0, 1,   0, 0,
                sy, 0,  cy, 0,
                0, 0,   0, 1,
        };

        mat<4, 4, Ty_> rotZ = {
                cr, sr, 0, 0,
                -sr, cr, 0, 0,
                0,  0, 1, 0,
                0,  0, 0, 1,
        };

        return rotY * rotX * rotZ;
    }

    template <typename Ty_ = float>
    constexpr mat<4, 4, Ty_> LookAtLH(const Vec::vec<3, Ty_>& eye, const Vec::vec<3, Ty_>& target, const Vec::vec<3, Ty_>& up) {
        Vec::vec<3, Ty_> zaxis = Vec::normalize(target - eye);
        Vec::vec<3, Ty_> xaxis = Vec::normalize(Vec::cross(up, zaxis));
        Vec::vec<3, Ty_> yaxis = Vec::cross(zaxis, xaxis);

        return mat<4, 4, float>(
                xaxis.x, yaxis.x, zaxis.x, 0.0f,
                xaxis.y, yaxis.y, zaxis.y, 0.0f,
                xaxis.z, yaxis.z, zaxis.z, 0.0f,
                -Vec::dot(xaxis, eye), -Vec::dot(yaxis, eye), -Vec::dot(zaxis, eye), 1.0f
        );
    }
}

#endif //BLUEPRINT_MAT4X4FLOAT_H
