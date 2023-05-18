%include 'io.inc'

section .bss
    N equ 6
    a resd N
section .text

reverse:
    push ebp
    mov ebp, esp
    mov edx, dword[esp + 12]    ; edx = N
    mov ebx, dword[esp + 8]     ; ebx = a
    mov esi, 2                  ; esi = 2
    mov eax, edx
    cdq
    div esi                     ; eax = N div 2
    xor ecx, ecx
    mov edx, dword[esp + 12]
    .CYCLE:
        cmp ecx, eax            ; i = N div 2?
        je .NEXT
        mov edi, dword[ebx + ecx*4] ; edi = a[i]
        mov esi, dword[ebx + edx*4 - 4] ; esi = a[N-i-1]
        mov dword[ebx + ecx*4], esi
        mov dword[ebx + edx*4 - 4], edi   ; a[i] <=> a[N - i - 1]
        inc ecx
        dec edx
        jmp .CYCLE
    .NEXT:
    xor edi, edi
    mov edx, dword[esp + 12]
    .OUTPUT:
        cmp edi, edx
        je .FIN
        mov eax, dword[ebx + edi*4]
        PRINT_DEC 4, eax
        PRINT_CHAR ' '
        inc edi
        jmp .OUTPUT
    .FIN:
        leave
        ret
    
global CMAIN
CMAIN:
    xor edx, edx      ; edx - i
    .INPUT:
        cmp edx, N
        je .NEXT
        GET_DEC 4, eax
        mov dword[a + edx*4], eax
        inc edx
        jmp .INPUT
.NEXT:
   mov ebx, a
   push edx    ; edx - N
   push ebx    ; ebx - a
   call reverse
   add esp, 8
    xor eax, eax
    ret