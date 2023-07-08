.globl charfreq

charfreq:
    push %esi
    push %edi
    push %ebx
    subl $1036, %esp

    movl 1052(%esp), %ebx               # const char* ebx = s;

    leal 12(%esp), %esi                 # unsigned esi = freq;
    movl %esi, (%esp)
    movl $0, 4(%esp)
    movl $1024, 8(%esp)
    call memset

L:  movb (%ebx), %cl                    # char cl = *s;
    cmpb $0, %cl
    je EL
    incl (%esi, %ecx, 4)                # unsigned edx = freq[*s];
    incl %ebx                           # ebx++;
    jmp L

EL: xorl %eax, %eax                     # unsigned eax = maxi = 0;
    movl (%esi), %edx                   # unsigned edx = maxf = freq[0];
    movl $1, %edi                       # int edi = 1;

F:  cmpl $256, %edi
    jge R
    cmpl %edx, (%esi, %edi, 4)
    jle IN
    movl %edi, %eax
    movl (%esi, %edi, 4), %edx
IN: incl %edi 
    jmp F

R:  addl $1036, %esp
    pop %ebx
    pop %edi
    pop %esi
    ret
