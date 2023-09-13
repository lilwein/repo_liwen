# scrivere la soluzione qui...
.globl f
f:
	movl $2, %eax
	addl $3, %eax
	movl $4, %ecx
	subl $2, %ecx
	imull %ecx, %eax
	movl $2, %ecx
	addl $3, %ecx
	subl %ecx, %eax
	imull $3, %eax
	incl %eax
	ret
