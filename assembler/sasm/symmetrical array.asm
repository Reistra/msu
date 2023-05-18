%include 'io.inc'
section .bss
    N equ 5
    a resd N
section .text
sim:
    push ebp
    mov ebp, esp
        ;push ebx
        ;push esi
        ;push edi
    mov edx, dword[esp + 12]    ; edx = N
    mov ebx, dword[esp + 8]     ; ebx = a
    mov esi, 2                  ; esi = 2
    mov eax, edx
    cdq
    div esi                     ; eax = N div 2
    xor ecx, ecx                ; ecx = 0, ecx = i
    xor edi, edi                ; edi = 0, edi = k
    mov edx, dword[esp + 12]
    CYCLE:
        cmp ecx, eax
        je YES
        mov esi, dword[ebx + edx*4 - 4]      ; esi = a[N-i-1]
        PRINT_STRING ' esi = '
        PRINT_DEC 4, esi
        NEWLINE
        cmp dword[ebx + ecx*4], esi          ; a[i] = a[N-i-1]?
        jne NO                               ; a[i] <> a[N-i-1]
            inc ecx
            dec edx
        jmp CYCLE
  YES:
    mov eax, 1
    jmp FIN
  NO:
    mov eax, 0
  FIN:
        ;pop ebx
        ;pop esi
        ;pop edi
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
        push edx        ; edx = N
        push ebx        ; ebx = a
        call sim
        add esp, 8
    PRINT_DEC 4, eax
    xor eax, eax
    ret