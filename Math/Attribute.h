#ifndef BLUEPRINT_ATTRIBUTE_H
#define BLUEPRINT_ATTRIBUTE_H

#define OPTIMIZE_O3      [[gnu::optimize("O3")]]
#define HOT_FUNCTION     __attribute__((hot))
#define FLATTEN_FUNCTION __attribute__((flatten))
#define TARGET_AVX2      __attribute__((target("avx2")))
#define ALWAYS_INLINE    __attribute__((always_inline))

#define NODISCARD        [[nodiscard]]
#define NORETURN         [[noreturn]]

#endif //BLUEPRINT_ATTRIBUTE_H
