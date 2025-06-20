#include "Timer.h"

template <typename Precision>
Timer<Precision>::Timer()
    : accumulated(0),
      running(false)
{

}

template <typename Precision>
void Timer<Precision>::start() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!running) {
        start_time = clock::now();
        running = true;
    }
}

template <typename Precision>
void Timer<Precision>::stop() {
    std::lock_guard<std::mutex> lock(mtx);
    if (running) {
        auto end_time = clock::now();
        accumulated += std::chrono::duration_cast<Precision>(end_time - start_time);
        running = false;
    }
}

template <typename Precision>
void Timer<Precision>::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    accumulated = Precision::zero();
    running = false;
}

template <typename Precision>
Precision Timer<Precision>::elapsed() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (running) {
        auto now = clock::now();
        return accumulated + std::chrono::duration_cast<Precision>(now - start_time);
    } else {
        return accumulated;
    }
}

template <typename Precision>
void Timer<Precision>::print_elapsed(const std::string& label) const {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << label << "Elapsed time: " << elapsed().count() << " " << unit_name() << '\n';
}

template <typename Precision>
template <typename Func>
auto Timer<Precision>::measure(Func &&func, const std::string &label, bool auto_print) {
    start();
    if constexpr (std::is_void_v<decltype(func())>) {
        func();
        stop();
        if (auto_print) print_elapsed(label);
    } else {
        auto result = func();
        stop();
        if (auto_print) print_elapsed(label);
        return result;
    }
}

template <typename Precision>
Timer<Precision>::ScopedGuard::ScopedGuard(Timer<Precision> &timer, std::string label, bool auto_print)
    : timer(timer), label(std::move(label)), auto_print(auto_print)
{
    timer.start();
}

template <typename Precision>
Timer<Precision>::ScopedGuard::~ScopedGuard() {
    timer.stop();
    if (auto_print) {
        timer.print_elapsed(label);
    }
}

template <typename Precision>
Timer<Precision>::ScopedGuard Timer<Precision>::scoped(const std::string &label, bool auto_print) {
    return ScopedGuard(*this, label, auto_print);
}