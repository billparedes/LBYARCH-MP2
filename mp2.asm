section .text
bits 64
default rel
global asm_dot_product

asm_dot_product:
    ; Input: RCX = A, RDX = B, R8 = n (number of elements)
    ; Output: XMM0 = sdot (float result)

    xorps xmm0, xmm0         ; Clear XMM0 for accumulation

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