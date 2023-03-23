#scrivere qui la soluzione...
.globl crc32b
crc32b:
    pushl %ebx
    pushl %ebp
    pushl %esi
    pushl %edi
    subl $8, %esp

    movl $0, %ecx
    notl %ecx
    movl %ecx, %esi
L:  cmpl $0, 32(%esp)
    je E
    movl 28(%esp), %edi
    movsbl (%edi), %ebp
    incb (%edi)
    xorl %ebp, %esi
    andl $0xFF, %esi
    movl (%ebx), %edx
    leal 8(%edx), %esp
    movl %edx, (%esp)
    movl %esi, 4(%esp)
    call get_constant
    sarl $8, %esi
    xorl %ebx, %esi
    decl 32(%esp)
    jmp L
E:  xorl %ecx, %esi
    movl %esi, %eax
    addl $8, %esp
    popl %edi
    popl %esi
    popl %ebp
    popl %ebx
    ret
