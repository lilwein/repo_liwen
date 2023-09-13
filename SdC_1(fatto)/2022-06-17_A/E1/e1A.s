# scrivere qui la soluzione...
.globl crc32
crc32:
    
    pushl %ebx
    pushl %ebp
    pushl %esi
    pushl %edi

    movl $0, %ebx
    movl $0xFFFFFFFF, %esi
    movl 20(%esp), %ecx
L1: cmpl 24(%esp), %ebx
    jge R
    movzbl (%ecx, %ebx, 1), %edi
    xorl %edi, %esi
    movl $0, %ebp
L2: cmpl $8, %ebp
    jge E1
    movl %esi, %edx
    andl $1, %edx
    negl %edx
    sarl $1, %esi
    andl $0xEDB88320, %edx
    xorl %edx, %esi
    incl %ebp
    jmp L2
E1: incl %ebx
    jmp L1
R:  notl %esi
    movl %esi, %eax

    popl %edi
    popl %esi
    popl %ebp
    popl %ebx
    ret
