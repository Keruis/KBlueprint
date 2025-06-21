#ifndef BLUEPRINT_VULKANBOOLUTILS_H
#define BLUEPRINT_VULKANBOOLUTILS_H

#include <cstdint>
#include <utility>

namespace Vulkan::Utils {
    class BoolConditionResult {
        bool result_;

    public:
        constexpr explicit BoolConditionResult(bool result) : result_(result) {}

        template<typename Callback>
        constexpr BoolConditionResult&& then(Callback&& cb) && {
            if (result_) {
                std::forward<Callback>(cb)();
            }
            return std::move(*this);
        }

        template<typename Callback>
        constexpr BoolConditionResult&& otherwise(Callback&& cb) && {
            if (!result_) {
                std::forward<Callback>(cb)();
            }
            return std::move(*this);
        }

        constexpr explicit operator bool() const { return result_; }
    };

    template<typename... Args>
    constexpr BoolConditionResult K_MixedAll(Args&&... args) {
        return BoolConditionResult{(... && static_cast<bool>(args))};
    }

    template<typename... Args>
    constexpr BoolConditionResult K_MixedAny(Args&&... args) {
        return BoolConditionResult{(... || static_cast<bool>(args))};
    }

    template<typename... Args>
    constexpr BoolConditionResult K_MixedNone(Args&&... args) {
        return BoolConditionResult{!(... || static_cast<bool>(args))};
    }
}

#endif //BLUEPRINT_VULKANBOOLUTILS_H
