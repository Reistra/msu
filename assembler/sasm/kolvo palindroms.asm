%include 'io.inc'
section .data
    del dd 10
    del2 dw 2
section .bss
    N equ 5
    a resd N
    K resd 1
section .text
pal:
    push ebp
    mov ebp, esp
    mov ebx, dword[esp + 8]     ; ebx = a[i]
    mov eax, ebx                ; eax = a[i]
    HM:                         ; number of numbers = K
        cdq
        div dword[del]
        cmp eax, 0
        je P
        inc dword[K]
        jmp HM
   P:                          ; go and find palindroms! preparations.
        mov eax, ebx           ; eax = a[i]
        mov esi, ebx           ; esi = a[i]
        xor ecx, ecx           ; ecx = i
        xor ebx, ebx
        GO:
            cmp ecx, dword[K]  ; turn the whole nubmer
            je EX
            inc ecx
            div dword[del]
            add ebx, edx
            mul dword[del]
            jmp GO
    EX:
        cmp esi, ebx
        je YES
        mov eax, 0
        leave 
        ret
     YES:
        mov eax, 1
        leave
        ret
        
palindrom:
    push ebp
    mov ebp, esp
    mov edx, dword[esp + 12]        ; edx = N
    mov ebx, dword[esp + 8]         ; ebx = a
    xor ecx, ecx
        C:
        cmp ecx, edx
        je E
        mov eax, dword[ebx + ecx*4]
        inc ecx
        push eax
        call pal
        add esp, 4
        jmp C
    E:
    leave
    ret
    
global main
main:
    xor ecx, ecx
    INPUT:
        cmp ecx, N
        je NE
        GET_DEC 4, eax
        mov dword[a + ecx*4], eax
        inc ecx
        jmp INPUT
    NE:
        push ecx
        push a
        call palindrom
        add esp, 8
        PRINT_DEC 4, eax
    xor eax, eax
    ret