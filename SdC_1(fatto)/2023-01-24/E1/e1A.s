.globl strings_are_upper

strings_are_upper:
    
    push %edi
    push %esi
    push %ebx
    push %ebp
    subl $4, %esp

    movl 24(%esp), %ebx             # char** ebx = array;
    # movl 28(%esp), %ebp             # int ebp = n;

    xorl %eax, %eax
    cmpl $0, %ebx
    je R
    cmpl $0, 28(%esp)
    jle R

    movl 28(%esp), %esi
    imull $4, %esi
    movl %esi, (%esp)
    call malloc

    movl $0, %esi                   # int esi = i = 0;
F:  cmpl %esi, 28(%esp)
    jle R
    movl (%ebx, %esi, 4), %ebp      # char* ebp = s = array[i];
    movl $1, (%eax, %esi, 4)        # eax[esi] = 1;

W:  movb (%ebp), %cl                # char cl = *ebp;
    cmpb $0, %cl
    je EW
    
    movl %eax, %edi  
    movl $0, (%esp)
    movb %cl, (%esp)
    call isupper
    movl %eax, %ecx
    movl %edi, %eax
    cmpl $0, %ecx
    jne C
    movl $0, (%eax, %esi, 4)        # eax[esi] = 1;
    jmp EW

C:  incl %ebp
    jmp W

EW: incl %esi
    jmp F

R:  
    addl $4, %esp
    pop %ebp
    pop %ebx
    pop %esi
    pop %edi
    ret
