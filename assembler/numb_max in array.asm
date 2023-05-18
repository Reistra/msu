%include 'io.inc'

section .bss
    N equ 5
    a resd N
    k resd 1
section .text
numb_max:
    push ebp
    mov ebp, esp
    mov ebx, dword[esp + 8]           ; ebx = a
    mov edx, dword[esp + 12]          ; edx = N
    xor ecx, ecx
    mov eax, dword[ebx + ecx*4]       ; eax = max; eax = a[0]
    inc ecx
    MAX:
        cmp ecx, edx
        je T
        cmp eax, dword[ebx + ecx*4]
        jge MOVE
        mov eax, dword[ebx + ecx*4]
        MOVE:
        inc ecx
        jmp MAX
    T:
        xor ecx, ecx
        mov esi, eax                 ; esi = max
    THEN:
        cmp ecx, edx
        je FIN
        cmp dword[ebx + ecx*4], esi
        jne M
        inc dword[k]
        M:
        inc ecx
        jmp THEN
    FIN:
    mov eax, dword[k]
    leave
    ret
global main
main:
    xor edx, edx
    INPUT:
        cmp edx, N
        je NEXT
        GET_DEC 4, eax
        mov dword[a + edx*4], eax
        inc edx
        jmp INPUT
    NEXT:
        mov ebx, a
        push edx
        push a
        call numb_max
        add esp, 8
        PRINT_DEC 4, eax
    xor eax, eax
    ret