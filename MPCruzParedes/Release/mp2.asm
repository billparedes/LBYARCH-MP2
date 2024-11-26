; Cruz, Jullian Gabriel || Paredes, Bill Jethro - S17

section .text
bits 64
default rel
global asm_dot_product

asm_dot_product:
    xorps xmm0, xmm0         ; Set xmm0 to 0

.loop:
    test r8, r8              ; Check if n == 0
    jz .done                 ; If n is zero, exit loop

    movss xmm1, [rcx]        ; Load A[i] into XMM1
    mulss xmm1, [rdx]        ; Multiply A[i] * B[i]
    addss xmm0, xmm1         ; Accumulate result in XMM0

    add rcx, 4               ; Move to the next float in A
    add rdx, 4               ; Move to the next float in B
    dec r8                   ; Decrement n
    jmp .loop

.done:
    ret