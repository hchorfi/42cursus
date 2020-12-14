section .text
    global _ft_strcpy

_ft_strcpy:
    mov rax, rdi
    mov rbx, 0

copy:
    cmp byte[rsi + rbx], 0
    je exit
    mov bpl, byte[rsi + rbx]
    mov byte[rdi + rbx], bpl
    add rbx, 1
    jmp copy

exit:
    ret