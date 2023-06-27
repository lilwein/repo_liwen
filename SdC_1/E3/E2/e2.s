.globl fib

fib:
    movl 4(%esp), %eax
    movl $0, %ecx
    movl $1, %edx
    testl %eax, %eax
    je F1
    cmpl %eax, %edx
    je F2

L:  cmpl $1, %eax
    jbe F3
    addl %edx, %ecx
    addl %edx, %ecx

    negl %edx
    addl %ecx, %edx

    subl %edx, %ecx

    decl %eax
    jmp L

F3: movl %edx, %eax
    jmp R
F1: movl %ecx, %eax
    jmp R
F2: movl %edx, %eax
    jmp R

R: ret
