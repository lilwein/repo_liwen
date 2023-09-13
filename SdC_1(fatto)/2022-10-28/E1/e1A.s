.globl str_to_upper

str_to_upper:
    push %edi
    push %esi
    push %ebx
    push %ebp
    subl $4, %esp

    movl 24(%esp), %ebx             # char* ebx = s;

    xorl %eax, %eax

    cmpl $0, %ebx
    je R

    movl %ebx, (%esp)
    call strdup                     # char* eax = s_copy = strdup(s);
    movl %eax, %edi                 # char* edi = s_copy;
    movl %eax, %esi                 # char* esi = copy;

L:  movb (%esi), %dl                # char dl = *copy;
    cmpb $0, %dl
    je E
    movsbl %dl, %eax
    movl %eax, (%esp)
    call toupper
    movb %al, (%esi)
    incl %esi
    jmp L

E:  movl %edi, %eax
    jmp R


R:
    addl $4, %esp
    pop %ebp
    pop %ebx
    pop %esi
    pop %edi
    ret
