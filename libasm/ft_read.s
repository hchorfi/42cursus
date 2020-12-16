extern ___error
section .text
    global _ft_read

_ft_read:
    mov rax, 0x02000003
    syscall
    jc error
    ret

error:
    push rax
    call ___error
    pop r8
    mov [rax], r8
    mov rax, -1
    ret