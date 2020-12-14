section .data
        text db "hello, assembly!",10

section .text
        global _start

_start:
        mov rax, 0x02000004
        mov rdi, 1
        mov rsi, text
        mov rdx, 16
        syscall

        mov rax, 0x02000001
        mov rdi, 0
        syscall