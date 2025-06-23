#ifndef BLUEPRINT_VULKANCONSTEXPRUTILS_H
#define BLUEPRINT_VULKANCONSTEXPRUTILS_H

namespace Vulkan::Utils {
    template <bool Cond, typename ThenFn, typename ElseFn>
    constexpr void K_constexpr_if(ThenFn&& then_fn, ElseFn&& else_fn) {
        if constexpr (Cond) {
            then_fn();
        } else {
            else_fn();
        }
    }

    template <bool Cond, typename ThenFn>
    constexpr void K_constexpr_if(ThenFn&& then_fn) {
        if constexpr (Cond) {
            then_fn();
        }
    }
}

#endif //BLUEPRINT_VULKANCONSTEXPRUTILS_H
