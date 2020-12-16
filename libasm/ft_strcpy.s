section .text
    global _ft_strcpy

_ft_strcpy:
    xor rdx, rdx

copy:
    mov r12b, byte[rsi + rdx]
    mov byte[rdi + rdx], r12b
    add rdx, 1
    cmp byte[rsi + rdx], 0
    jne copy
    mov byte [rdi + rdx], 0

exit:
    mov rax, rdi
    ret
