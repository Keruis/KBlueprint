#ifndef BLUEPRINT_SIMD_H
#define BLUEPRINT_SIMD_H

#include <immintrin.h>

namespace Math::detail {

    template<typename T>
    struct SimdTraits;

    template<>
    struct SimdTraits<float> {
        using avx_type = __m256;
        using avx_low_type = __m128;
        using load_arg = const float *;
        using store_arg = float *;

        static constexpr auto load = _mm256_load_ps;
        static constexpr auto loadu = _mm256_loadu_ps;
        static constexpr auto store = _mm256_store_ps;
        static constexpr auto storeu = _mm256_storeu_ps;
        static constexpr auto set = _mm256_set1_ps;
        static constexpr auto setr = _mm256_setr_ps;
        static constexpr auto add = _mm256_add_ps;
        static constexpr auto sub = _mm256_sub_ps;
        static constexpr auto mul = _mm256_mul_ps;
        static constexpr auto div = _mm256_div_ps;
        static constexpr auto sqrt = _mm256_sqrt_ps;
        static constexpr auto cast = _mm256_castps256_ps128;
        static constexpr auto unpacklo = _mm256_unpacklo_ps;
        static constexpr auto unpackhi = _mm256_unpackhi_ps;
        static constexpr auto shuffle = [](avx_type v1, avx_type v2, int imm8) {
            return _mm256_shuffle_ps(v1, v2, imm8);
        };
        static constexpr auto permute2 = [](avx_type v1, avx_type v2, int imm8) {
            return _mm256_permute2f128_ps(v1, v2, imm8);
        };

        static inline avx_low_type extractf(avx_type v) {
            return _mm256_extractf128_ps(v, 1);
        }

        static constexpr auto hadd = _mm_hadd_ps;
        static constexpr auto cvt = _mm_cvtss_f32;

        struct sse_traits {
            using type = __m128;
            using load_arg = const float *;
            using store_arg = float *;

            static constexpr auto load = _mm_load_ps;
            static constexpr auto loadu = _mm_loadu_ps;
            static constexpr auto store = _mm_store_ps;
            static constexpr auto storeu = _mm_storeu_ps;
            static constexpr auto set = _mm_set1_ps;
            static constexpr auto setr = _mm_setr_ps;
            static constexpr auto add = _mm_add_ps;
            static constexpr auto sub = _mm_sub_ps;
            static constexpr auto mul = _mm_mul_ps;
            static constexpr auto div = _mm_div_ps;
            static constexpr auto sqrt = _mm_sqrt_ps;
            static constexpr auto shuffle = [](type v1, type v2, int imm8) {
                return _mm_shuffle_ps(v1, v2, imm8);
            };
            static constexpr auto unpacklo = _mm_unpacklo_ps;
            static constexpr auto unpackhi = _mm_unpackhi_ps;
            static constexpr auto hadd = _mm_hadd_ps;
            static constexpr auto cvt = _mm_cvtss_f32;
        };
    };

    template<>
    struct SimdTraits<double> {
        using avx_type = __m256d;
        using avx_low_type = __m128d;
        using load_arg = const double *;
        using store_arg = double *;

        static constexpr auto load = _mm256_load_pd;
        static constexpr auto loadu = _mm256_loadu_pd;
        static constexpr auto store = _mm256_store_pd;
        static constexpr auto storeu = _mm256_storeu_pd;
        static constexpr auto set = _mm256_set1_pd;
        static constexpr auto setr = _mm256_setr_pd;
        static constexpr auto add = _mm256_add_pd;
        static constexpr auto sub = _mm256_sub_pd;
        static constexpr auto mul = _mm256_mul_pd;
        static constexpr auto div = _mm256_div_pd;
        static constexpr auto sqrt = _mm256_sqrt_pd;
        static constexpr auto cast = _mm256_castpd256_pd128;
        static constexpr auto unpacklo = _mm256_unpacklo_pd;
        static constexpr auto unpackhi = _mm256_unpackhi_pd;
        static constexpr auto shuffle = [](avx_type v1, avx_type v2, int imm8) {
            return _mm256_shuffle_pd(v1, v2, imm8);
        };
        static constexpr auto permute2 = [](avx_type v1, avx_type v2, int imm8) {
            return _mm256_permute2f128_pd(v1, v2, imm8);
        };

        static inline avx_low_type extractf(avx_type v) {
            return _mm256_extractf128_pd(v, 1);
        }

        static constexpr auto hadd = _mm_hadd_pd;
        static constexpr auto cvt = _mm_cvtsd_f64;

        struct sse_traits {
            using type = __m128d;
            using load_arg = const double *;
            using store_arg = double *;

            static constexpr auto load = _mm_load_pd;
            static constexpr auto loadu = _mm_loadu_pd;
            static constexpr auto store = _mm_store_pd;
            static constexpr auto storeu = _mm_storeu_pd;
            static constexpr auto set = _mm_set1_pd;
            static constexpr auto setr = _mm_setr_pd;
            static constexpr auto add = _mm_add_pd;
            static constexpr auto sub = _mm_sub_pd;
            static constexpr auto mul = _mm_mul_pd;
            static constexpr auto div = _mm_div_pd;
            static constexpr auto sqrt = _mm_sqrt_pd;
            static constexpr auto shuffle = [](type v1, type v2, int imm8) {
                return _mm_shuffle_pd(v1, v2, imm8);
            };
            static constexpr auto unpacklo = _mm_unpacklo_pd;
            static constexpr auto unpackhi = _mm_unpackhi_pd;
            static constexpr auto hadd = _mm_hadd_pd;
            static constexpr auto cvt = _mm_cvtsd_f64;
        };
    };

    template<>
    struct SimdTraits<int> {
        using avx_type = __m256i;
        using avx_low_type = __m128i;
        using load_arg = const void *;
        using store_arg = void *;

        static constexpr auto load = _mm256_load_si256;
        static constexpr auto loadu = _mm256_loadu_si256;
        static constexpr auto store = _mm256_store_si256;
        static constexpr auto storeu = _mm256_storeu_si256;
        static constexpr auto set = _mm256_set1_epi32;
        static constexpr auto setr = _mm256_setr_epi32;
        static constexpr auto add = _mm256_add_epi32;
        static constexpr auto sub = _mm256_sub_epi32;
        static constexpr auto mul = _mm256_mullo_epi32;
        static constexpr auto bit_and = _mm256_and_si256;
        static constexpr auto bit_xor = _mm256_xor_si256;
        static constexpr auto bit_not = _mm256_andnot_si256;
        static constexpr auto bit_or = _mm256_or_si256;
        static constexpr auto cast = _mm256_castsi256_si128;
        static constexpr auto unpacklo = _mm256_unpacklo_epi32;
        static constexpr auto unpackhi = _mm256_unpackhi_epi32;
        static constexpr auto shuffle = [](avx_type v, int imm8) {
            return _mm256_shuffle_epi32(v, imm8);
        };
        static constexpr auto permute2 = [](avx_type v1, avx_type v2, int imm8) {
            return _mm256_permute2f128_si256(v1, v2, imm8);
        };

        static inline avx_low_type extractf(avx_type v) {
            return _mm256_extractf128_si256(v, 1);
        }

        static constexpr auto hadd = _mm_hadd_epi32;
        static constexpr auto cvt = _mm_cvtsi128_si32;

        struct sse_traits {
            using type = __m128i;
            using load_arg = const void *;
            using store_arg = void *;

            static constexpr auto load = _mm_load_si128;
            static constexpr auto loadu = _mm_loadu_si128;
            static constexpr auto store = _mm_store_si128;
            static constexpr auto storeu = _mm_storeu_si128;
            static constexpr auto set = _mm_set1_epi32;
            static constexpr auto setr = _mm_setr_epi32;
            static constexpr auto add = _mm_add_epi32;
            static constexpr auto sub = _mm_sub_epi32;
            static constexpr auto mul = _mm_mullo_epi32;
            static constexpr auto bit_and = _mm_and_si128;
            static constexpr auto bit_xor = _mm_xor_si128;
            static constexpr auto bit_not = _mm_andnot_si128;
            static constexpr auto bit_or = _mm_or_si128;
            static constexpr auto shuffle = [](type v, int imm8) {
                return _mm_shuffle_epi32(v, imm8);
            };
            static constexpr auto unpacklo = _mm_unpacklo_epi32;
            static constexpr auto unpackhi = _mm_unpackhi_epi32;
            static constexpr auto hadd = _mm_hadd_epi32;
            static constexpr auto cvt = _mm_cvtsi128_si32;
        };
    };

    template<> struct SimdTraits<int64_t> {
        using avx_type     = __m256i;
        using avx_low_type = __m128i;
        using load_arg     = const void*;
        using store_arg    = void*;

        static constexpr auto load      = _mm256_load_si256;
        static constexpr auto loadu     = _mm256_loadu_si256;
        static constexpr auto store     = _mm256_store_si256;
        static constexpr auto storeu    = _mm256_storeu_si256;
        static constexpr auto set       = _mm256_set1_epi64x;
        static constexpr auto setr      = _mm256_setr_epi64x;
        static constexpr auto add       = _mm256_add_epi64;
        static constexpr auto sub       = _mm256_sub_epi64;
        static inline __m256i mul(__m256i a, __m256i b) {
            __m256i a_lo = _mm256_and_si256(a, _mm256_set1_epi64x(0xFFFFFFFF));
            __m256i a_hi = _mm256_srli_epi64(a, 32);
            __m256i b_lo = _mm256_and_si256(b, _mm256_set1_epi64x(0xFFFFFFFF));
            __m256i b_hi = _mm256_srli_epi64(b, 32);

            __m256i lo_lo = _mm256_mul_epu32(a_lo, b_lo);
            __m256i hi_lo = _mm256_mul_epu32(a_hi, b_lo);
            __m256i lo_hi = _mm256_mul_epu32(a_lo, b_hi);

            hi_lo = _mm256_slli_epi64(hi_lo, 32);
            lo_hi = _mm256_slli_epi64(lo_hi, 32);

            __m256i result = _mm256_add_epi64(lo_lo, hi_lo);
            result = _mm256_add_epi64(result, lo_hi);
            return result;
        }
        static constexpr auto bit_and   = _mm256_and_si256;
        static constexpr auto bit_xor   = _mm256_xor_si256;
        static constexpr auto bit_not   = _mm256_andnot_si256;
        static constexpr auto bit_or    = _mm256_or_si256;
        static constexpr auto cast      = _mm256_castsi256_si128;
        static constexpr auto unpacklo  = _mm256_unpacklo_epi64;
        static constexpr auto unpackhi  = _mm256_unpackhi_epi64;
        static constexpr auto shuffle   = [](avx_type v, int imm8) {
            return _mm256_shuffle_epi32(v, imm8);
        };
        static constexpr auto permute2  = [](avx_type v1, avx_type v2, int imm8) {
            return _mm256_permute2x128_si256(v1, v2, imm8);
        };
        static inline avx_low_type extractf(avx_type v) {
            return _mm256_extractf128_si256(v, 1);
        }
        static inline __m256i hadd(__m256i v) {
            __m128i lo = _mm256_castsi256_si128(v);
            __m128i hi = _mm256_extracti128_si256(v, 1);

            __m128i sum_lo = _mm_add_epi64(lo, _mm_unpackhi_epi64(lo, lo));
            __m128i sum_hi = _mm_add_epi64(hi, _mm_unpackhi_epi64(hi, hi));

            return _mm256_inserti128_si256(_mm256_castsi128_si256(sum_lo), sum_hi, 1);
        }
        static constexpr auto cvt       = _mm_cvtsi128_si64;

        struct sse_traits {
            using type       = __m128i;
            using load_arg   = const void*;
            using store_arg  = void*;

            static constexpr auto load      = _mm_load_si128;
            static constexpr auto loadu     = _mm_loadu_si128;
            static constexpr auto store     = _mm_store_si128;
            static constexpr auto storeu    = _mm_storeu_si128;
            static constexpr auto set       = _mm_set1_epi64x;
            static inline type setr(int64_t a, int64_t b) {
                return _mm_unpacklo_epi64(_mm_cvtsi64_si128(a), _mm_cvtsi64_si128(b));
            }
            static constexpr auto add       = _mm_add_epi64;
            static constexpr auto sub       = _mm_sub_epi64;
            static constexpr auto bit_and   = _mm_and_si128;
            static constexpr auto bit_xor   = _mm_xor_si128;
            static constexpr auto bit_not   = _mm_andnot_si128;
            static constexpr auto bit_or    = _mm_or_si128;
            static constexpr auto shuffle   = [](type v, int imm8) {
                return _mm_shuffle_epi32(v, imm8);
            };
            static constexpr auto unpacklo  = _mm_unpacklo_epi64;
            static constexpr auto unpackhi  = _mm_unpackhi_epi64;
            static constexpr auto cvt       = _mm_cvtsi128_si64;
        };
    };
}
#endif //BLUEPRINT_SIMD_H
