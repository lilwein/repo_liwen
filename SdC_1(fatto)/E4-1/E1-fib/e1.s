.globl fib
fib:
    push %edi
    push %esi
    subl $4, %esp

    movl 16(%esp), %edi
    cmpl $2, %edi
    jge F
    movl $1, %eax
    jmp R

F:  decl %edi
    movl %edi, (%esp)
    call fib
    movl %eax, %esi

    decl %edi
    movl %edi, (%esp)
    call fib
    addl %esi, %eax

R:  addl $4, %esp
    pop %esi
    pop %edi

    ret
