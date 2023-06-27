# scrivere la soluzione qui...
.globl counteq
counteq:
	pushl %esi
	pushl %edi
	pushl %ebx
	movl 16(%esp), %esi
	movl 20(%esp), %edi
	movl 24(%esp), %ecx
	movl $0, %eax
	decl %ecx
L:	testl %ecx, %ecx
	jl E
	movw (%esi, %ecx, 2), %bx
	movw (%edi, %ecx, 2), %dx
	cmpw %bx, %dx
	sete %dl
	movsbl %dl, %edx
	addl %edx, %eax
	decl %ecx
	jmp L
E:	popl %ebx
	popl %edi
	popl %esi
	ret
	
