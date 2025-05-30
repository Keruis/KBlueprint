#include "../include/IP.h"

IP::IP &IP::IP::ConvertToGray() noexcept {
    if (m_data->getSizeChannel() != 3 && m_data->getSizeChannel() != 4) {
        m_data->setErrorCode(0x30FF); return *this;
    }

    const std::size_t width  = m_data->getSizeWidth();
    const std::size_t height = m_data->getSizeHeight();

    auto& uData = m_data->getUData();
    uData.resize(width * height);

    constexpr int PixelsPerIteration = 8;
    __m256 weight_r_avx = _mm256_set1_ps(0.299f);
    __m256 weight_g_avx = _mm256_set1_ps(0.587f);
    __m256 weight_b_avx = _mm256_set1_ps(0.114f);

    auto& rData = m_data->getRedData();
    auto& gData = m_data->getGreenData();
    auto& bData = m_data->getBlueData();

    constexpr const int tile_height = 64;
    for (int ii = 0; ii < height; ii += tile_height) {
        int block_end = ii + tile_height;
        block_end = block_end < height ? block_end : height;
        for (int i = ii; i < block_end; ++i) {
            const int index = i * width;
            int j = 0;
            for (; j <= width - PixelsPerIteration; j += PixelsPerIteration) {
                uc* r_ptr = &rData[index + j];
                uc* g_ptr = &gData[index + j];
                uc* b_ptr = &bData[index + j];
                uc* gray_ptr = &uData[index + j];

                __asm__ __volatile__ (
                        "prefetchnta 64(%[r_src])               \n\t"
                        "prefetchnta 64(%[g_src])               \n\t"
                        "prefetchnta 64(%[b_src])               \n\t"
                        "prefetchnta 64(%[dst])                 \n\t"
                        :
                        : [r_src] "r" (r_ptr),
                [g_src] "r" (g_ptr),
                [b_src] "r" (b_ptr),
                [dst] "r" (gray_ptr)
                : "memory"
                );

                __asm__ __volatile__ (
                        "vmovq (%[r_src]), %%xmm0               \n\t"
                        "vmovq (%[g_src]), %%xmm1               \n\t"
                        "vmovq (%[b_src]), %%xmm2               \n\t"

                        "vpmovzxbd %%xmm0, %%ymm3               \n\t"
                        "vpsrldq $4, %%xmm0, %%xmm4             \n\t"
                        "vpmovzxbd %%xmm4, %%ymm4               \n\t"
                        "vinserti128 $1, %%xmm4, %%ymm3, %%ymm3 \n\t"

                        "vpmovzxbd %%xmm1, %%ymm5               \n\t"
                        "vpsrldq $4, %%xmm1, %%xmm6             \n\t"
                        "vpmovzxbd %%xmm6, %%ymm6               \n\t"
                        "vinserti128 $1, %%xmm6, %%ymm5, %%ymm5 \n\t"

                        "vpmovzxbd %%xmm2, %%ymm7               \n\t"
                        "vpsrldq $4, %%xmm2, %%xmm8             \n\t"
                        "vpmovzxbd %%xmm8, %%ymm8               \n\t"
                        "vinserti128 $1, %%xmm8, %%ymm7, %%ymm7 \n\t"

                        "vcvtdq2ps %%ymm3, %%ymm3               \n\t"
                        "vcvtdq2ps %%ymm5, %%ymm5               \n\t"
                        "vcvtdq2ps %%ymm7, %%ymm7               \n\t"
                        "vmulps %[wr], %%ymm3, %%ymm3           \n\t"
                        "vmulps %[wg], %%ymm5, %%ymm5           \n\t"
                        "vmulps %[wb], %%ymm7, %%ymm7           \n\t"
                        "vaddps %%ymm5, %%ymm3, %%ymm3          \n\t"
                        "vaddps %%ymm7, %%ymm3, %%ymm3          \n\t"

                        "vcvtps2dq %%ymm3, %%ymm3               \n\t"

                        "vpackssdw %%ymm3, %%ymm3, %%ymm3       \n\t"
                        "vpermq $0b11011000, %%ymm3, %%ymm3     \n\t"
                        "vpackuswb %%xmm3, %%xmm3, %%xmm3       \n\t"

                        "vmovdqu %%xmm3, (%[dst])               \n\t"
                        "vzeroupper                             \n\t"

                        :
                        : [r_src] "r" (r_ptr),
                [g_src] "r" (g_ptr),
                [b_src] "r" (b_ptr),
                [dst] "r" (gray_ptr),
                [wr] "m" (weight_r_avx),
                [wg] "m" (weight_g_avx),
                [wb] "m" (weight_b_avx)
                : "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8",
                        "ymm3", "ymm4", "ymm5", "ymm6", "ymm7", "ymm8", "memory"
                );
            }

            for (; j < width; ++j) {
                uc gray;
                const int idx = index + j;
                const uc r = rData[idx];
                const uc g = gData[idx];
                const uc b = bData[idx];

                __asm__ __volatile__ (
                        "movzb   %[r], %%eax                    \n\t"
                        "imul    $299, %%eax, %%eax             \n\t"
                        "movzb   %[g], %%ecx                    \n\t"
                        "imul    $587, %%ecx, %%ecx             \n\t"
                        "add     %%ecx, %%eax                   \n\t"
                        "movzb   %[b], %%ecx                    \n\t"
                        "imul    $114, %%ecx, %%ecx             \n\t"
                        "add     %%ecx, %%eax                   \n\t"
                        "add     $500, %%eax                    \n\t"
                        "mov     $1000, %%ecx                   \n\t"
                        "cdq                                    \n\t"
                        "idiv    %%ecx                          \n\t"
                        "mov     %%al, %[gray]                  \n\t"
                        : [gray] "=r" (gray)
                : [r] "m" (r), [g] "m" (g), [b] "m" (b)
                : "eax", "ecx", "edx", "memory"
                );

                uData[idx] = gray;
            }

        }
    }

    m_data->setSize([](ImageSize size) -> ImageSize{ size.channel = 1; return size;}(m_data->getSize()));

    return *this;
}
