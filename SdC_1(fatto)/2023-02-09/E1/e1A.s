.globl check_quiz

check_quiz:
    push %edi
    push %esi
    push %ebx
    push %ebp
    subl $4, %esp

    movl 24(%esp), %ebx             # char** ebx = answers;
    movl 28(%esp), %esi             # char* esi = solution;
    
    xorl %eax, %eax

    cmpl $0, %ebx
    je R
    cmpl $0, %esi
    je R
    cmpl $0, 28(%esp)
    jle R


I3: movl 32(%esp), %ecx
    imull $4, %ecx
    movl %ecx, (%esp)
    call malloc                     # int* eax = res;

    movl $0, %ecx
    xorl %edi, %edi                 # int edi = i = 0;

L1: cmpl 32(%esp), %edi
    jge R
    xorl %edx, %edx                 # int edx = j = 0;

L2: cmpl $4, %edx
    jge E2
    movl (%ebx, %edi, 4), %ebp      # char* ebp = answers[i];
    movb (%ebp, %edx, 1), %cl       # char al = answer[j];
    cmpb (%esi, %edx, 1), %cl
    jne NE
    incl (%eax, %edi, 4)

NE: incl %edx
    jmp L2

E2: incl %edi
    jmp L1


R:  
    addl $4, %esp
    pop %ebp
    pop %ebx
    pop %esi
    pop %edi
    ret
