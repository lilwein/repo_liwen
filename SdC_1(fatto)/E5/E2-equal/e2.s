.globl list_equal

list_equal:
    push %esi
    push %edi
    push %ebx

    movl 16(%esp), %esi     # node_t* esi = l1
    movl 20(%esp), %edi     # node_t* edi = l2

L:  cmpl $0, %esi           # if (esi != 0) char dl = 1
    setne %dl               # else char dl = 0
    cmpl $0, %edi           # if (edi != 0) char bl = 1
    setne %bl               # else char bl = 0
    andb %dl, %bl           # bl = bl & dl
    cmpb $1, %bl            # if (bl != 1)
    movl $0, %eax
    jne R                   # goto R
    movl $0, %ecx
    movl $0, %edx
    movw (%esi), %cx        # short cx = *l1
    movw (%edi), %dx        # short dx = *l2
    cmpw %cx, %dx           # if (cx == dx)
    je E                    # goto E
    movl $0, %eax
    jmp R

E:  movl 8(%esi), %esi      
    movl 8(%edi), %edi
    # movl $0, %ecx
    # movl $0, %edx
    # movl $0, %eax
    cmpl $0, %esi
    sete %dl
    cmpl $0, %edi
    sete %al
    andb %dl, %al

R:  pop %ebx
    pop %edi
    pop %esi
    ret
    