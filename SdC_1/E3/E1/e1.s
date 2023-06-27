.globl min
min:
    movl 4(%esp), %eax
    movl 8(%esp), %ecx
    movl 12(%esp), %edx
    cmpl %eax, %ecx
    jle E
    cmpl %eax, %edx
    jle Z
    jmp X
E:  cmpl %ecx, %edx
    jle Z
    jmp Y
X:  ret
Y:  movl %ecx, %eax
    ret
Z:  movl %edx, %eax
    ret
