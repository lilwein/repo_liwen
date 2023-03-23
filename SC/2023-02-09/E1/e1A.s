# scrivere qui la soluzione...
.globl check_quiz
check_quiz:
    pushl %ebp
    pushl %ebx
    pushl %edi
    pushl %esi
    subl $4, %esp


    movl $0, %eax
    cmpl $0, 24(%esp)
    je R
    cmpl $0, 28(%esp) 
    je R
    cmpl $0, 32(%esp)
    jle R
    movl 32(%esp), %eax
    imull $4, %eax
    movl %eax, (%esp)
    call malloc
    movl $0, %esi       #i
    movl 24(%esp), %ebx
    movl 28(%esp), %ebp
    
L1: cmpl 32(%esp), %esi
    jge R
    movl $0, (%eax, %esi, 4)
    movl $0, %edx       #j
L2: cmpl $4, %edx
    jge E1
    movl (%ebx, %esi, 4), %edi  #answer = answers[i]
    movb (%ebp, %edx, 1), %cl
    cmpb %cl, (%edi, %edx, 1) 
    jne E2
    incl (%eax, %esi, 4)
E2: incl %edx
    jmp L2

E1: incl %esi
    jmp L1

R:  addl $4, %esp
    popl %esi
    popl %edi
    popl %ebx
    popl %ebp
    ret
