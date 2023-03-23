# scrivere qui la soluzione...
.globl count_matching_vars
count_matching_vars:
    pushl %ebp
    pushl %ebx
    pushl %edi
    pushl %esi
    subl $8, %esp

    
    movl $-1, %esi
    cmpl $0, 28(%esp)
    je R
    cmpl $0, 32(%esp)
    je R
    movl 28(%esp), %ebx
    movl $0, %esi
    
L:  movl (%ebx), %ecx
    cmpb $0, %cl
    je R
    movl %ecx, (%esp)
    call getenv
    cmpl $0, %eax
    je E
    movl %eax, (%esp)
    movl 32(%esp), %edi
    movl %edi, 4(%esp)
    call strstr
    cmpl $0, %eax
    je E
    incl %esi
E:  addl $4, %ebx
    jmp L
R:  movl %esi, %eax

    addl $8, %esp
    popl %esi
    popl %edi
    popl %ebx
    popl %ebp
    ret
