# scrivere qui la soluzione...
.globl count_vars
count_vars:
    pushl %ebx
    pushl %ebp
    pushl %esi
    pushl %edi
    subl $4, %esp


    movl $0, %ebx       
    cmpl $0, 24(%esp)
    je R
    cmpl $0, 28(%esp)
    jle R
    movl 28(%esp), %eax
    imull $4, %eax
    movl %eax, (%esp)
    call malloc
    movl %eax, %ebx         #ebx = malloc
    movl $0, %ebp
    movl 24(%esp), %edi
L:  cmpl 28(%esp), %ebp
    jge R
    movl (%edi, %ebp, 4), %ecx
    movl %ecx, (%esp)
    call getenv
    cmpl $0, %eax
    je E
    movl $1, (%ebx, %ebp, 4)
    incl %ebp
    jmp L
E:  movl $0, (%ebx, %ebp, 4)
    incl %ebp
    jmp L
R:  movl %ebx, %eax

    addl $4, %esp
    popl %edi
    popl %esi
    popl %ebp
    popl %ebx
    ret
