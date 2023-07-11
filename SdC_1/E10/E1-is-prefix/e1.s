.globl is_prefix

is_prefix:
    push %ebx
    push %esi
    push %edi

    movl 16(%esp), %esi
    movl 20(%esp), %edi
    movb (%esi), %cl
    movb (%edi), %dl

L:  cmpb $0, %cl
    je R
    cmpb %cl, %dl
    jne R
    incl %esi
    incl %edi
    movb (%esi), %cl
    movb (%edi), %dl
    jmp L

R:  xorl %eax, %eax
    cmpb $0, %cl
    sete %al
    pop %edi
    pop %esi
    pop %ebx
    ret
