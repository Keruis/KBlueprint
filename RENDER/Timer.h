#ifndef BLUEPRINT_TIMER_H
#define BLUEPRINT_TIMER_H

#include <chrono>
#include <iostream>
#include <string>
#include <mutex>

template <typename Precision = std::chrono::milliseconds>
class Timer {
public:
    Timer();

    void start();
    void stop();
    void reset();
    Precision elapsed() const;
    void print_elapsed(const std::string& label = "") const;

    template <typename Func>
    auto measure(Func&& func, const std::string& label = "", bool auto_print = true);

    class ScopedGuard {
    public:
        ScopedGuard(Timer& timer, std::string label = "", bool auto_print = true);
        ~ScopedGuard();

    private:
        Timer& timer;
        std::string label;
        bool auto_print;
    };

    ScopedGuard scoped(const std::string& label = "", bool auto_print = true);

private:
    using clock = std::chrono::high_resolution_clock;
    typename clock::time_point start_time;
    Precision accumulated;
    bool running;
    mutable std::mutex mtx;

    std::string unit_name() const {
        if constexpr (std::is_same_v<Precision, std::chrono::nanoseconds>) return "ns";
        else if constexpr (std::is_same_v<Precision, std::chrono::microseconds>) return "us";
        else if constexpr (std::is_same_v<Precision, std::chrono::milliseconds>) return "ms";
        else if constexpr (std::is_same_v<Precision, std::chrono::seconds>) return "s";
        else return "?";
    }
};

template <typename Precision>
std::ostream& operator<<(std::ostream& os, const Timer<Precision>& timer) {
    os << "Elapsed time: " << timer.elapsed().count();

    if constexpr (std::is_same_v<Precision, std::chrono::nanoseconds>) os << " ns";
    else if constexpr (std::is_same_v<Precision, std::chrono::microseconds>) os << " us";
    else if constexpr (std::is_same_v<Precision, std::chrono::milliseconds>) os << " ms";
    else if constexpr (std::is_same_v<Precision, std::chrono::seconds>) os << " s";
    else os << " ?";

    return os;
}

#include "Timer.tpp"

#endif //BLUEPRINT_TIMER_H
