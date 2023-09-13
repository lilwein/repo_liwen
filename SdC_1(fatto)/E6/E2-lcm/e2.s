.globl lcm

lcm:
    push %esi
    push %edi
    push %ebx

    movl 16(%esp), %esi
    movl 20(%esp), %edi
    movl %edi, %ebx

    cmpl %edi, %esi
    jle W
    movl %esi, %ebx

W:  movl $0, %edx
    movl %ebx, %eax
    idivl %esi
    cmpl $0, %edx
    jne N
    movl $0, %edx
    movl %ebx, %eax
    idivl %edi
    cmpl $0, %edx
    jne N
    movl %ebx, %eax
    jmp R
N:  incl %ebx
    jmp W

R:  pop %ebx
    pop %edi
    pop %esi
    ret
