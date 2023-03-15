// scrivere la soluzione qui...
.globl my_strcmp
my_strcmp:
	movl 4(%esp), %ecx
	movl 8(%esp), %edx
L:	movb (%ecx), %al
	testb %al, %al
	je E
	cmpb (%edx), %al
	jne E
	incl %ecx
	incl %edx
	jmp L
E:	subb (%edx), %al
	ret
