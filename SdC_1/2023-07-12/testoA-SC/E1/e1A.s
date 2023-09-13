.globl adler32

adler32:
    push %ebx
    push %ebp
    push %esi
    push %edi
    subl $8, %esp

    xorl %eax, %eax
    cmpl $0, 28(%esp)
    je R
    cmpl $0, 32(%esp)
    je R

    movl $1, %esi               # unsigned esi = 1;
    movl $0, %ebx               # unsigned ebx = 0;

    leal 4(%esp), %ecx
    movl %ecx, (%esp)
    call get_adler_constant

    movl 28(%esp), %ebp
    xorl %edi, %edi             # int edi = 0;
L:  cmpl 32(%esp), %edi
    jae E
    movzbl (%ebp, %edi, 1), %eax
    addl %esi, %eax
    xorl %edx, %edx
    divl 4(%esp)
    movl %edx, %esi
    
    movl %ebx, %eax
    addl %esi, %eax
    xorl %edx, %edx
    divl 4(%esp)
    movl %edx, %ebx
    
    incl %edi
    jmp L


E:  shll $16, %ebx
    orl %ebx, %esi
    movl %esi, %eax

R:  addl $8, %esp
    pop %edi
    pop %esi
    pop %ebp
    pop %ebx
    ret
