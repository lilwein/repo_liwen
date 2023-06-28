.globl counteq

counteq:
	push %esi
	push %edi
	push %ebx

	movl 16(%esp), %ecx	# short* ecx = v1;
	movl 20(%esp), %edx	# short* edx = v2;

	movl 24(%esp), %ebx	# int ebx = n;
	movl $0, %edi		# int edi = i = 0;
	movl $0, %eax		# int eax = cnt = 0

L: 	cmpl %ebx, %edi
	jge R
	movw (%ecx, %edi, 2), %si
	cmpw (%edx, %edi, 2), %si
	jne C
	incl %eax
C:	incl %edi
	jmp L

R:	pop %ebx
	pop %edi
	pop %esi

	ret
