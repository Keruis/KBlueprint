#ifndef BLUEPRINT_SIMD_H
#define BLUEPRINT_SIMD_H

#include <immintrin.h>

template<typename T> struct SimdTraits;

template<> struct SimdTraits<float> {
    using avx_type                  =           __m256;
    using avx_low_type              =           __m128;
    using load_arg                  =           const float*;
    using store_arg                 =           float*;
    static constexpr auto load      =           _mm256_load_ps;
    static constexpr auto loadu     =           _mm256_loadu_ps;
    static constexpr auto store     =           _mm256_store_ps;
    static constexpr auto storeu    =           _mm256_storeu_ps;
    static constexpr auto set       =           _mm256_set1_ps;
    static constexpr auto setr      =           _mm256_setr_ps;
    static constexpr auto add       =           _mm256_add_ps;
    static constexpr auto add128    =           _mm_add_ps;
    static constexpr auto sub       =           _mm256_sub_ps;
    static constexpr auto mul       =           _mm256_mul_ps;
    static constexpr auto div       =           _mm256_div_ps;
    static constexpr auto sqrt      =           _mm256_sqrt_ps;
    static constexpr auto cast      =           _mm256_castps256_ps128;
    static constexpr auto unpacklo  =           _mm256_unpacklo_ps;
    static constexpr auto unpackhi  =           _mm256_unpackhi_ps;
    #define shuffle_f(v1, v2, i) (_mm256_shuffle_ps(v1, v2, i));
    #define permute2_f(v1, v2, i) (_mm256_permute2f128_ps(v1, v2, i));
    static inline avx_low_type extractf(avx_type v) {
        return _mm256_extractf128_ps(v, 1);
    }
    static constexpr auto hadd      =           _mm_hadd_ps;
    static constexpr auto cvt       =           _mm_cvtss_f32;
};

template<> struct SimdTraits<double> {
    using avx_type                  =           __m256d;
    using avx_low_type              =           __m128d;
    using load_arg                  =           const double*;
    using store_arg                 =           double*;
    static constexpr auto load      =           _mm256_load_pd;
    static constexpr auto loadu     =           _mm256_loadu_pd;
    static constexpr auto store     =           _mm256_store_pd;
    static constexpr auto storeu    =           _mm256_storeu_pd;
    static constexpr auto set       =           _mm256_set1_pd;
    static constexpr auto setr      =           _mm256_setr_pd;
    static constexpr auto add       =           _mm256_add_pd;
    static constexpr auto add128    =           _mm_add_pd;
    static constexpr auto sub       =           _mm256_sub_pd;
    static constexpr auto mul       =           _mm256_mul_pd;
    static constexpr auto div       =           _mm256_div_pd;
    static constexpr auto sqrt      =           _mm256_sqrt_pd;
    static constexpr auto cast      =           _mm256_castpd256_pd128;
    static constexpr auto unpacklo  =           _mm256_unpacklo_pd;
    static constexpr auto unpachi   =           _mm256_unpackhi_pd;
    #define shuffle_d(v1, v2, i) (_mm256_shuffle_pd(v1, v2, i));
    #define permute2_d(v1, v2, i) (_mm256_permute2f128_pd(v1, v2, i));
    static inline avx_low_type extractf(avx_type v) {
        return _mm256_extractf128_pd(v, 1);
    }
    static constexpr auto hadd      =           _mm_hadd_pd;
    static constexpr auto cvt       =           _mm_cvtsd_f64;
};

template<> struct SimdTraits<int> {
    using avx_type                  =           __m256i;
    using avx_low_type              =           __m128i;
    using load_arg                  =           const __m256i*;
    using store_arg                 =           __m256i*;
    static constexpr auto load      =           _mm256_load_si256;
    static constexpr auto loadu     =           _mm256_loadu_si256;
    static constexpr auto store     =           _mm256_store_si256;
    static constexpr auto storeu    =           _mm256_storeu_si256;
    static constexpr auto set       =           _mm256_set1_epi32;
    static constexpr auto setr      =           _mm256_setr_epi32;
    static constexpr auto add       =           _mm256_add_epi32;
    static constexpr auto add128    =           _mm_add_epi32;
    static constexpr auto sub       =           _mm256_sub_epi32;
    static constexpr auto mul       =           _mm256_mullo_epi32;
    static constexpr auto bit_and   =           _mm256_and_si256;
    static constexpr auto bit_xor   =           _mm256_xor_si256;
    static constexpr auto bit_not   =           _mm256_andnot_si256;
    static constexpr auto bit_or    =           _mm256_or_si256;
    static constexpr auto cast      =           _mm256_castsi256_si128;
    static constexpr auto unpacklo  =           _mm256_unpacklo_epi32;
    static constexpr auto unpackhi  =           _mm256_unpackhi_epi32;
    #define shuffle_i(v1, i) (_mm256_shuffle_epi32(v1, i));
    #define permute2_i(v1, v2, i) (_mm256_permute2f128_si256(v1, v2, i));
    static inline avx_low_type extractf(avx_type v) {
        return _mm256_extractf128_si256(v, 1);
    }
    static constexpr auto hadd      =           _mm_hadd_epi32;
    static constexpr auto cvt       =           _mm_cvtsi128_si32;
};

#endif //BLUEPRINT_SIMD_H
