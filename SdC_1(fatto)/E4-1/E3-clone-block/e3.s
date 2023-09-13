.globl clone

clone:
	push %esi
	push %edi
	push %ebx
	subl $12, %esp

	movl 28(%esp), %esi		# esi = src
	movl 32(%esp), %edi		# edi = n

	movl %edi, (%esp)
	call malloc
	movl %eax, %ebx			# esi = malloc(n)
	testl %ebx, %ebx
	jne ND
	movl $0, %eax
	jmp R

ND:	movl %ebx, (%esp)
	movl %esi, 4(%esp)
	movl %edi, 8(%esp)
	call memcpy
	movl %ebx, %eax
	jmp R

R:	addl $12, %esp
	pop %ebx
	pop %edi
	pop %esi
	ret
