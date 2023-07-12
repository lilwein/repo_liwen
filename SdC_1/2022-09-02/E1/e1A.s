.globl div_vectors

div_vectors:
    push %edi
    push %esi
    push %ebx
    push %ebp
    subl $4, %esp

    movl 24(%esp), %ebx                 # unsigned int* ebx = a;
    movl 28(%esp), %ebp                 # unsigned int* ebp = b;

    xorl %eax, %eax
    cmpl $0, 24(%esp)
    je R
    cmpl $0, 28(%esp)
    je R
    cmpl $0, 32(%esp)
    je R

    movl 32(%esp), %ecx
    imull $4, %ecx                      # int ecx = 4*n;
    movl %ecx, (%esp)
    call malloc
    movl %eax, %esi                     # unsigned int* esi = out;

    xorl %edi, %edi                     # int edi = i = 0;

L:  cmpl 32(%esp), %edi
    jge E
    xorl %edx, %edx
    movl (%ebx, %edi, 4), %eax
    movl (%ebp, %edi, 4), %ecx
    idiv %ecx
    movl %eax, (%esi, %edi, 4)
    incl %edi
    jmp L

E:  movl %esi, %eax

R:
    addl $4, %esp
    pop %ebp
    pop %ebx
    pop %esi
    pop %edi
    ret
