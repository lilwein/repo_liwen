# scrivere qui la soluzione...
.globl div_vectors
div_vectors:
    pushl %esi
    pushl %edi
    pushl %ebx
    pushl %ebp
    subl $4, %esp

    movl $0, %edi
    cmpl $0, 24(%esp)               
    je R                            
    cmpl $0, 28(%esp)               
    je R                            
    cmpl $0, 32(%esp)               
    je R                            
    movl $4, %edi                   
    imull 32(%esp), %edi            
    movl %edi, (%esp)
    call malloc             
    movl %eax, %edi         
    movl $0, %ebx           
    movl 24(%esp), %esi    
    movl 28(%esp), %ecx    
L:  cmpl 32(%esp), %ebx    
    jge R                  
    movl (%esi, %ebx,4), %eax       
    xorl %edx, %edx
    movl (%ecx, %ebx, 4), %ebp      
    idivl %ebp                      
    movl %eax, (%edi, %ebx, 4)
    incl %ebx
    jmp L
R:  movl %edi, %eax
    
    addl $4, %esp
    popl %ebp
    popl %ebx
    popl %edi
    popl %esi
    ret
