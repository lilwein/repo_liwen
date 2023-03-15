# scrivere la soluzione qui...
.globl clone
clone:
	pushl %esi
	pushl %edi
	pushl %ebx
	subl $12, %esp
	movl 28(%esp), %esi
	movl 32(%esp), %ebx
	movl %ebx, (%esp)
	call malloc
	movl %eax, %edi
	xorl %eax, %eax
L:	testl %edi, %edi
	je E
	movl %edi, (%esp)
	movl %esi, 4(%esp)
	movl %ebx, 8(%esp)
	call memcpy
	movl %edi, %eax
E:	addl $12, %esp
	popl %ebx
	popl %edi
	popl %esi
	ret
