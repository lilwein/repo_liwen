# scrivere la soluzione qui...
.globl find
find:
    movl 4(%esp), %ecx
    movl 8(%esp), %eax
    movl 12(%esp), %edx
    decl %eax
L:  cmpl $0, %eax
    jl R0
    cmpl %edx, (%ecx, %eax, 4)
    je R1
    decl %eax
    jmp L
R0: movl $0, %eax
    ret
R1: movl $1, %eax
    ret
