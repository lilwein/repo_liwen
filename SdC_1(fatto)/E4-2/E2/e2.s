.globl find

find:
    movl 4(%esp), %ecx      # int* ecx = v
    movl 8(%esp), %edx
    movl 12(%esp), %eax     # int ebx = x
    decl %edx
L:  cmpl $0, %edx
    jl R0
    cmpl (%ecx,%edx,4), %eax
    je R1
    decl %edx
    jmp L


R0: movl $0, %eax
    jmp R
R1: movl $1, %eax
    jmp R
R:  ret
