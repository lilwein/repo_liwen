.globl fib
fib:
    pushl %ebx
    pushl %edi
    subl $4, %esp
    movl 16(%esp), %edi
    movl $1, %eax
    cmpl $2, %edi
    jl E
    decl %edi
    movl %edi, (%esp)
    call fib
    movl %eax, %ebx
    decl %edi
    movl %edi, (%esp)
    call fib
    addl %ebx, %eax
E:  addl $4, %esp
	popl %edi
	popl %ebx
    ret
