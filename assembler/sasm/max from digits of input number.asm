%include 'io.inc'
section .data
    del dd 10
section .bss
    d resd 10
section .text
global main
main:
    GET_DEC 4, eax
    CYCLE:
        cdq
        cmp eax, 0                  ; is it the end of number?
        je NE
        div dword[del]              ; edx = a % 10
        inc dword[d + edx*4]        ; a[edx] += 1
        jmp CYCLE
     NE:
        mov edx, 9
        xor ebx, ebx
     CREATE:
        cmp dword[d + edx*4], 0     ; di = 0? (i = 9,...,0)
        je NEXT_NUMBER
        add ebx, edx
        imul ebx, dword[del]        ; ebx = edx*10
        dec dword[d + edx*4]        ; di--
        jmp CREATE
        NEXT_NUMBER:
            cmp edx, 0
            je FIN
            dec edx
            jmp CREATE
    FIN:
        mov eax, ebx
        cdq
        div dword[del]
        PRINT_DEC 4, eax
    xor eax, eax
    ret