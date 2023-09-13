.globl binsearch

binsearch:
	push %ebx
	push %edi
	push %esi

	movl 16(%esp), %ebx			# int* ebx = v;
	movl 20(%esp), %edi			# int edi = n;
	movl 24(%esp), %esi			# int esi = x;

	xorl %edx, %edx				# int edx = i = 0;
L:	cmpl %edi, %edx
	movl $0, %eax
	jge R
	movl %edx, %ecx				# int ecx = i;
	addl %edi, %ecx				# ecx = i + n;
	sarl $1, %ecx				# ecx = (ecx>>1);
	movl (%ebx, %ecx, 4), %eax
	cmpl %esi, %eax
	jne C
	movl $1, %eax
	jmp R
C:	cmpl %esi, %eax
	jle E
	movl %ecx, %edi
	jmp L
E:	movl %ecx, %edx
	incl %edx
	jmp L


R:	pop %esi
	pop %edi
	pop %ebx
	ret
