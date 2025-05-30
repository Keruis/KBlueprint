#ifndef BLUEPRINT_ATTRIBUTES_H
#define BLUEPRINT_ATTRIBUTES_H


#if defined(__GNUC__) && !defined(__clang__)
#define OPTIMIZE_O3 __attribute__((optimize("O3")))
#else
#define OPTIMIZE_O3
#endif

#define HOT_FUNCTION     __attribute__((hot))
#define FLATTEN_FUNCTION __attribute__((flatten))
#define TARGET_AVX2      __attribute__((target("avx2")))
#define ALWAYS_INLINE    __attribute__((always_inline))

#define NODISCARD        [[nodiscard]]
#define NORETURN         [[noreturn]]

#endif //BLUEPRINT_ATTRIBUTES_H
