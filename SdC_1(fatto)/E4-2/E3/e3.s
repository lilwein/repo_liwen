.globl my_strcmp

my_strcmp:
    movl 4(%esp), %ecx
    movl 8(%esp), %edx
    

L:  movb (%ecx), %al
    cmpb $0, %al
    je R
    cmpb (%edx), %al
    jne R
    incl %ecx
    incl %edx
    jmp L

R:  
    subb (%edx), %al
    ret
