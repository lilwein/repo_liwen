.globl f

f:
	movl 4(%esp), %ecx
	movl 8(%esp), %edx
	movl %ecx, %eax
	addl %edx, %eax
	subl %edx, %ecx
	imull %ecx, %eax
	ret
