.globl list_add_first

list_add_first:
	push %ebx
	push %esi
	push %edi
	subl $4, %esp

	movw 24(%esp), %di		# short edi = elem
	movl 20(%esp), %ebx		# node_t** ebx = l
	movl (%ebx), %esi		# node_t* esi = p = *l
	movl $16, (%esp)
	call malloc
	movl %eax, %ecx			# node_t* ecx = n
	cmpl $0, %ecx
	jne C
	movl $-1, %eax
	jmp R

C:	movw %di, (%ecx)
	movl %esi, 4(%ecx)
	movl %ecx, (%ebx)
	movl $0, %eax

R:	addl $4, %esp
	pop %edi
	pop %esi
	pop %ebx
	ret
