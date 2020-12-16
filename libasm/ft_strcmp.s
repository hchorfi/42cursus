section .text
    global _ft_strcmp

_ft_strcmp:
    xor rax, rax
    mov al, [rdi]
    mov bl, [rsi]
    cmp al, 0
    je exit
    cmp bl, 0
    je exit
    cmp al, bl
    jne exit
    inc rdi
    inc rsi
    jmp _ft_strcmp

exit:
    sub rax, rbx
    ret
