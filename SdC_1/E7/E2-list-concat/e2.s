.globl list_concat

list_concat:
	push %ebx
	push %esi
	push %edi

	movl 16(%esp), %esi			# node_t** esi = l1;
	movl 20(%esp), %edi			# node_t* edi = l2;
	movl (%esi), %ebx			# node_t* ebx = p = *l1;

	cmpl $0, %ebx
	jne W
	movl %edi, (%esi)
	jmp R

W:	movl 4(%ebx),%ecx 
	cmpl $0, %ecx
	je EW
	movl %ecx, %ebx
	jmp W

EW:	movl %edi, 4(%ebx) 

R:	pop %edi
	pop %esi
	pop %ebx
	ret
	