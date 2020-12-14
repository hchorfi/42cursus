section .text
    global _ft_strcmp

_ft_strcmp:
    mov rax, 0
    mov rbx, 0

compar:
    mov bpl, byte[rdi + rbx]
    cmp bpl, byte[rsi + rbx]
    jg greater
    jl less
    je next

next:
    cmp bpl, 0
    je exit
    add rbx, 1
    jmp compar

greater:
    mov rax, 1
    jmp exit

less:
    mov rax, -1
    jmp exit

exit:
    ret