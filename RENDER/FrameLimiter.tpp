#include "FrameLimiter.h"

inline Render::utils::FrameLimiter::FrameLimiter(double target_fps, double sleep_precision_sec)
    : frame_duration(1.0 / target_fps),
      sleep_precision(sleep_precision_sec),
      last_frame_time(clock::now())
{

}

inline void Render::utils::FrameLimiter::beginFrame() noexcept {
    auto now = clock::now();
    delta_time = std::chrono::duration<double>(now - last_frame_time).count();
    current_frame_time = now;
}

inline void Render::utils::FrameLimiter::endFrame() noexcept {
    last_frame_time = current_frame_time;

    auto now = clock::now();
    duration elapsed = now - current_frame_time;
    double time_left = frame_duration - elapsed.count();

    if (time_left > sleep_precision) {
        std::this_thread::sleep_for(duration(time_left - sleep_precision));
    }

    while ((clock::now() - current_frame_time).count() < frame_duration) {

    }
}

inline void Render::utils::FrameLimiter::SetFPS(double fps) noexcept {
    frame_duration = 1.0 / fps;
}

inline double Render::utils::FrameLimiter::GetFPS() const noexcept {
    return 1.0 / frame_duration;
}

inline double Render::utils::FrameLimiter::GetDeltaTime() const noexcept {
    return delta_time;
}