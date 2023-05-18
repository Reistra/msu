%include 'io.inc'

section .bss
    N equ 5
    a resd N
section .text
del:
    push ebp
    mov ebp, esp
        push esi
        push edi
    xor edi, edi    ; edi - counter
    mov ecx, dword[ebp + 12]    ; ecx - i
    mov ebx, dword[ebp + 8]     ;edx - a
    mov esi, 3
    .CYCLE:
        mov eax, dword[ebx + ecx*4 - 4]
        cdq
        div esi
        cmp edx, 0
        jne .NEXT
        inc edi
     .NEXT:
        loop .CYCLE
    mov eax, edi
    leave
    ret
    
global main
main:
    xor edx, edx    ; edx - i
    .CYCLE:
        mov eax, dword[a + edx*4]
        cmp edx, 4
        je .NEXT
        GET_DEC 4, eax
        inc edx
        jmp .CYCLE
    .NEXT:
        mov edx, dword[N]
        mov ebx, a
        push edx
        push ebx
        call del
        add esp, 8
        PRINT_DEC 4, eax              
    xor eax, eax
    ret