global asm_fragrant_chicken_zclamp

section .text
align 16

; void asm_fragrant_chicken_zclamp(float* data, size_t count)
; rdi = data, rsi = count
asm_fragrant_chicken_zclamp:
    push rbx
    push r12

    vxorps ymm0, ymm0, ymm0        ; ymm0 = 0.0f

    cmp rsi, 16                    ; 少于16个元素走标量处理
    jb .scalar_loop

.vector_loop:
    mov rcx, rsi
    shr rcx, 4                    ; 每轮处理16个 float
    jz .tail

    xor rax, rax                  ; offset = 0

.loop:
    vmovups ymm1, [rdi + rax*4]
    vmovups ymm2, [rdi + rax*4 + 32]
    vmaxps ymm1, ymm1, ymm0
    vmaxps ymm2, ymm2, ymm0
    vmovups [rdi + rax*4], ymm1
    vmovups [rdi + rax*4 + 32], ymm2

    add rax, 16                   ; 16 floats processed
    loop .loop

.tail:
    mov rcx, rsi
    and rcx, 15                   ; 处理剩下的 (mod 16)
    test rcx, rcx
    jz .done

mov rbx, rsi
shl rbx, 2            ; rbx = rsi * 4
add rbx, rdi          ; rbx = data + count * 4
mov rdx, rcx
shl rdx, 2            ; rdx = rcx * 4
sub rbx, rdx          ; rbx = 尾部剩余数据起始地址

.tail_loop:
    movss xmm1, [rbx]
    maxss xmm1, xmm0
    movss [rbx], xmm1
    add rbx, 4
    dec rcx
    jnz .tail_loop

.done:
    vzeroupper
    pop r12
    pop rbx
    ret

.scalar_loop:
    xor rax, rax
.sloop:
    cmp rax, rsi
    jge .done
    movss xmm1, [rdi + rax*4]
    vxorps xmm0, xmm0, xmm0
    maxss xmm1, xmm0
    movss [rdi + rax*4], xmm1
    inc rax
    jmp .sloop