# Scrivere la soluzione qui...
.globl list_concat
list_concat:
	movl 8(%esp), %edx
	movl 4(%esp), %ecx
	movl (%ecx), %eax
	cmpl $0, %eax
	jnz L
	movl %edx, (%ecx)
	jmp F
L:	cmpl $0, 4(%eax)
	jz E;
	movl 4(%eax), %eax
	jmp L
E:	movl %edx, 4(%eax)
F:	ret
