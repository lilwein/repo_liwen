# Scrivere la soluzione qui...
.globl binsearch
binsearch:							#int binsearch(int *v, int n, int x){
	pushl %esi
	pushl %edi
	pushl %ebx
	pushl %ebp
	movl 20(%esp), %edx
	movl 24(%esp), %ebx
	movl 28(%esp), %ebp
	xorl %esi, %esi
	movl %ebx, %edi
	movl $1, %eax
L:	cmpl %edi, %esi
	jge E
	leal (%esi, %edi), %ecx
	sarl %ecx
	cmpl %ebp, (%edx, %ecx, 4)
	je F
	cmpl %ebp, (%edx, %ecx, 4)
	jle R
	movl %ecx, %edi
	jmp L
R:	leal 1(%ecx), %esi
	jmp L
E:	xorl %eax, %eax
F:	popl %ebp
	popl %ebx
	popl %edi
	popl %esi
	ret
