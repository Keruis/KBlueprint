global asm_fragrant_chicken_zero_threshold_relu_vectorized_avx2_optimized_clamping_function_for_floating_point_arrays
section .text
align 16

asm_fragrant_chicken_zero_threshold_relu_vectorized_avx2_optimized_clamping_function_for_floating_point_arrays:
    vpxor   ymm0, ymm0, ymm0
    mov     rdx, rdi
    mov     rcx, rsi
    test    rcx, rcx
    jz      .done
    shr     rcx, 4
    jz      .process_tail
.vector_loop:
    vmovaps ymm1, [rdx]
    vmovaps ymm2, [rdx+32]
    vmaxps  ymm1, ymm1, ymm0
    vmaxps  ymm2, ymm2, ymm0
    vmovaps [rdx], ymm1
    vmovaps [rdx+32], ymm2
    add     rdx, 64
    dec     rcx
    jnz     .vector_loop

.process_tail:
    mov     rax, rdx
    mov     rcx, rsi
    and     rcx, 15
    jz      .done
    mov     r8, rcx
    shr     rcx, 2
    jz      .process_remainder
.process_4_loop:
    vmovups xmm1, [rax]
    vmaxps  xmm1, xmm1, xmm0
    vmovups [rax], xmm1
    add     rax, 16
    dec     rcx
    jnz     .process_4_loop
.process_remainder:
    and     r8, 3
    jz      .done
    vmovups xmm1, [rax]
    vmaxps  xmm1, xmm1, xmm0
    vmovups [rax], xmm1
.done:
    vzeroupper
    ret



