#ifndef BLUEPRINT_TYPE_TRAITS_H
#define BLUEPRINT_TYPE_TRAITS_H

#include "simd.h"
#include <type_traits>

namespace Math::detail {
    template<typename Ty_>
    struct align_selector {
        static constexpr std::size_t size = sizeof(Ty_);
        static constexpr std::size_t value =
                size == 4 ? 16 :
                size == 8 ? 32 :
                alignof(Ty_);
    };

    template <typename, typename = void>
    inline constexpr bool has_simd_trait = false;

    template <typename T>
    inline constexpr bool has_simd_trait<T, std::void_t<typename SimdTraits<T>::avx_type>> = true;
}

#endif //BLUEPRINT_TYPE_TRAITS_H
