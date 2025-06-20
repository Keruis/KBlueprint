#ifndef BLUEPRINT_FRAMELIMITER_H
#define BLUEPRINT_FRAMELIMITER_H

#include <chrono>
#include <thread>
#include "../Attribute.h"

namespace Render::utils {
    class FrameLimiter {
    public:
        using clock = std::chrono::steady_clock;
        using duration = std::chrono::duration<double>;

        explicit FrameLimiter(double target_fps = 60.0, double sleep_precision_sec = 0.001);

        ALWAYS_INLINE void beginFrame() noexcept;
        ALWAYS_INLINE void endFrame() noexcept;

        ALWAYS_INLINE void SetFPS(double fps) noexcept;
        ALWAYS_INLINE double GetFPS() const noexcept;

    private:
        double frame_duration;
        double sleep_precision;
        clock::time_point last_frame_time;
    };
}

#include "FrameLimiter.tpp"

#endif //BLUEPRINT_FRAMELIMITER_H
