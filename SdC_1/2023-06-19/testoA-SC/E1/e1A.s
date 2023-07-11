.globl rc4_encrypt

rc4_encrypt:

    push %esi
    push %edi
    push %ebx
    push %ebp

    subl $20, %esp

    movl 40(%esp), %esi             # char* esi = sbox;
    movl 44(%esp), %edi             # char edi = pt;
    movl 48(%esp), %ebx             # char* ebx = ct;

    xorl %ecx, %ecx                 # unsigned int ecx = n = 0;
    xorl %ebp, %ebp                 # unsigned int ebp = i = 0;
    movb $0, %dl                    # unsigned char dl = j = 0;

L:  cmpb $0, (%edi)
    je R

    incl %ebp
    andl $255, %ebp

    addb (%esi, %ebp, 1), %dl
    
    movl %esi, (%esp)
    movl %ebp, 4(%esp)
    movb %dl, 8(%esp)
    leal 16(%esp), %eax
    movl %eax, 12(%esp)
    call rc4_helper

    xorl %eax, %eax
    movb (%edi), %al

    xorb 16(%esp), %al
    movb %al, (%ebx, %ecx, 1)
    
    incl %ecx
    incl %edi
    jmp L


R:  
    addl $20, %esp
    pop %ebp
    pop %ebx
    pop %edi
    pop %esi
    ret
