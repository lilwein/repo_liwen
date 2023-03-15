.globl f
f:
	movl 4(%esp), %eax
	movl 8(%esp), %ecx
	movl %eax, %edx
	addl %ecx, %edx
	subl %ecx, %eax
	imull %edx, %eax
	ret
