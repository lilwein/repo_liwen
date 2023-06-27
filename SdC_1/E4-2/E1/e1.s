.globl count

count:                                       # int count(const char *s1){
    xorl %eax, %eax                          # int a=0;
    movl 4(%esp), %ecx                       # const char* c = s1;
A:  cmpl $0, %ecx                            # if(!*c) goto E;
    jne E
    incl %eax                                # a++;
    incl %ecx                                # c++;
    jmp A                                    # goto A;
    
E:  ret