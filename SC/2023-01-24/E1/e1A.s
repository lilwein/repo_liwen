# scrivere qui la soluzione...
.globl strings_are_upper
strings_are_upper:
    pushl %ebx
    pushl %ebp
    pushl %edi
    pushl %esi
    subl $4, %esp

    movl $0, %ecx
    cmpl $0, 24(%esp)
    je R
    cmpl $0, 28(%esp)
    jle R
    movl 24(%esp), %ebx
    movl 28(%esp), %edi
    leal 4(%edi), %eax
    movl %eax, (%esp)
    call malloc
    movl %eax, %ecx
    movl $0, %ebp
L1: cmpl %edi, %ebp
    jge R
    movl (%ebx, %ebp,4), %esi
    movl $1, (%ecx, %ebp, 4)
L2: cmpb $0, (%esi)
    je E1
    movsbl (%esi), %eax
    movl %eax, (%esp)
    call isupper
    cmpl $0, %eax
    je F
    incl %esi
    jmp L2
F:  movl $0, (%ecx, %ebp, 4)
E1: incl %ebp
    jmp L1

R:  movl %ecx, %eax
    addl $4, %esp
    popl %esi
    popl %edi
    popl %ebp
    popl %ebx
    ret
