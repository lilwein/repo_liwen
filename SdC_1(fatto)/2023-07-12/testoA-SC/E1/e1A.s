.globl adler32

adler32:
    push %edi
    push %esi
    push %ebx
    push %ebp
    subl $8, %esp

    xorl %eax, %eax
    cmpl $0, 28(%esp)
    je R
    cmpl $0, 32(%esp)
    je R

    movl 28(%esp), %esi         # unsigned char* esi = data;

    movl $1, %ebp               # unsigned ebp = a = 0;
    movl $0, %ebx               # unsigned ebx = b = 0;

    leal 4(%esp), %eax
    movl %eax, (%esp)
    call get_adler_constant

    xorl %edi, %edi             # int edi = i = 0;
L:  cmpl 32(%esp), %edi
    jae RA
    xorl %edx, %edx

    movzbl (%esi, %edi, 1), %eax
    addl %ebp, %eax
    divl 4(%esp)
    movl %edx, %ebp

    xorl %edx, %edx
    movl %ebx, %eax
    addl %ebp, %eax
    divl 4(%esp)
    movl %edx, %ebx

    incl %edi
    jmp L

RA: movl %ebx, %eax
    shll $16, %eax
    orl %ebp, %eax
    jmp R


R:  addl $8, %esp
    pop %ebp
    pop %ebx
    pop %esi
    pop %edi
    ret
