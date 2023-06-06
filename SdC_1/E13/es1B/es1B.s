# void interleave(const char* a, const char* b, char* c) {
#     do {
#         if (*a) *c++ = *a++;
#         if (*b) *c++ = *b++;
#     } while (*a || *b);
#     *c = '\0';
# }

# inserisci la soluzione qui...
.globl interleave
interleave:
	pushl %esi
	pushl %edi
	pushl %ebx
	subl $12, %esp
	movl 4(%esp), %esi		#a
	movl 8(%esp), %ebx		#b
	movl 12(%esp), %edi		#c
L:	movb (%esi), %al
	movb (%edi), %cl
	movb (%ebx), %dl
	cmpb %al, %al
	jne E
	movb %al, %cl
	incb %cl
	incb %al
E:	cmpb %dl, %dl
	jne F
	movb %bl, %cl
	incb %cl
	incb %bl
F:	cmpb %al, %al
	je E0
	jmp L
E0:	addl $12, %esp
	popl %ebx
	popl %edi
	popl %esi
	ret
	

	
