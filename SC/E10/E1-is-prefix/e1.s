# scrivere la soluzione qui...
.globl is_prefix

is_prefix: # int is_prefix(const char* s1, const char* s2)
    pushl %ebx
    movl 8(%esp), %ecx              # const char* c = s1;
    movl 12(%esp), %edx             # const char* d = s2;
L:  movb (%ecx), %al                # char a = *c;
    testb %al, %al                  # if (a == 0)
    je E                            #     goto E;
    movb (%edx), %bl                # char b = *d;
    incl %ecx                       # c++;
    incl %edx                       # d++;
    cmpb %bl, %al                   # if (a != b)
    jne E                           #     goto E;
    jmp L                           # goto L;
E:  movb (%ecx), %al                # a = *c;
    testb %al, %al                  # a = a == 0;
    sete %al
    movsbl %al, %eax
    popl %ebx
    ret
