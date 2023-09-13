.globl count_digits

count_digits:
    movl 4(%esp), %ecx
    xorl %eax, %eax
    
W:  movb (%ecx), %dl
    cmpb $0, %dl
    je R
    cmpb $48, %dl
    jl S
    cmpb $57, %dl
    jg S
    incl %eax

S:  incl %ecx
    jmp W

R:  ret
