# Inserisci qui la soluzione...
.globl list_add_first
list_add_first:							#int list_add_first(node_t **l, short elem) {
	pushl %ebx
	pushl %esi
	subl $4, %esp
	movl 16(%esp), %esi						#	node_t **si = l;
	movl (%esi), %ebx						#	node_t *b = si;
	movl $8, (%esp)		
	call malloc							#	node_t *a = malloc(sizeof(node_t));
	testl %eax, %eax						#	if(a != NULL)
	jnz E								#		goto E
	movl $1, %eax							#	return -1;
	jmp F
E:	movl 10(%esp), %edx						#	short d = elem;
	movw %dx, (%eax)						#	(*a).elem = d;
	movl %ebx, 4(%eax)						#	(*a).next = b;
	movl %eax, (%esi)						#	*si = a;
	xorl %eax, %eax							#	return 0;
F:	addl $4, %esp
	popl %esi
	popl %ebx
	ret
											#}
