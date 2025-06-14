#ifndef BLUEPRINT_TYPE_TRAITS_H
#define BLUEPRINT_TYPE_TRAITS_H

namespace Math::detail {
    template<typename Ty_>
    struct align_selector {
        static constexpr std::size_t size = sizeof(Ty_);
        static constexpr std::size_t value =
                size == 4 ? 16 :
                size == 8 ? 32 :
                alignof(Ty_);
    };
}

#endif //BLUEPRINT_TYPE_TRAITS_H
