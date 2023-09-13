# scrivere la soluzione qui...
.globl f
f:
	movl 4(%esp), %eax
	imull %eax, %eax
	imull $2, %eax
	movl 4(%esp), %ecx
	imull $7, %ecx
	subl %ecx, %eax
	incl %eax
	ret
	