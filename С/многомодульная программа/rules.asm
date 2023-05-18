section .text
global rule_one
global rule_two
rule_one:
    push ebp
    mov ebp, esp
        push edi
        push ebx
        push esi
    mov edx, dword[ebp + 12]        ; edx = N
    mov ebx, dword[ebp + 8]         ; ebx = string adress
    xor ecx, ecx                    ; ecx = i, ecx = 0.
    .CYCLE:
        cmp ecx, edx                ; i = N? if this the end of str
        je .FIN
        mov al,  byte[ebx + ecx*1]
        cmp al, '1'                 ; check if (str[i] >='0' && str[i] <= '9')
        jb .T  
        cmp al, '9'
        ja .T
        add al, '0'                 ; 1 -> 'a', 2 -> 'b', ... , 9 -> 'j' ; 'a' - '1'
        mov byte[ebx + ecx*1], al
        .T:
        inc ecx
        jmp .CYCLE
    .FIN:
        pop esi
        pop ebx
        pop edi
    leave
    ret
    
rule_two:
    push ebp
    mov ebp, esp
        push edi
        push ebx
        push esi
    mov edx, dword[ebp + 12]        ; edx = N
    mov edi, dword[ebp + 8]         ; edi = string adress
    movzx eax, byte[edi]            ; eax - first symbol of str
    mov ebx, eax                    ; ebx = eax
    push eax
    mov ecx, 1                      ; ecx = i, ecx = 1 (as first symbol was already processed)
    mov esi, 1                      ; counter of push'es
    .CYCLE:
        cmp ecx, edx                ; i = N?
        je .Z
        cmp byte[edi + ecx], bl     ; does another symbol = first symbol?
        je .M                       ; if yes - do nothing, go next
        movzx eax, byte[edi + ecx]  
        push eax                    ; if not - push str[i]
        inc esi
        .M:
        inc ecx
        jmp .CYCLE
    .Z:
     mov ecx, dword[ebp + 12]
    .ZEROS:
        mov byte[edi + ecx - 1], 0
        loop .ZEROS
    mov ecx, esi
    .OUT_POP:
        pop eax  
        mov byte[edi + ecx - 1], al 
        loop .OUT_POP
    pop esi
    pop ebx
    pop edi
    leave
    ret