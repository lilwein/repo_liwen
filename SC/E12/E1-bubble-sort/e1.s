# inserire la soluzione qui...
.globl bubble_sort
bubble_sort:
	pushl %edi				#v
	pushl %esi				#n
	pushl %ebx
	subl $8, %esp
	movl 24(%esp), %edi
	movl 28 (%esp), %esi
L1:	movl $0, %ecx			#again
	movl $1, %ebx			#i
L2:	cmpl %esi, %ebx
	jae E
	movw -2(%edi, %ebx, 2), %ax 
	cmpw (%edi, %ebx, 2), %ax
	jle	F
	leal -2(%edi, %ebx, 2), %eax
	movl %eax, (%esp)
	leal (%edi, %ebx, 2), %eax
	movl %eax, 4(%esp)
	call swap
	movl $1, %ecx
F:	incl %ebx
	jmp L2
E:	testl %ecx, %ecx
	jne L1
	addl $8, %esp
	popl %ebx
	popl %esi
	popl %edi
	ret
