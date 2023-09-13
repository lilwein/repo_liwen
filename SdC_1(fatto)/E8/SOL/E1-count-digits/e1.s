.globl count_digits
count_digits:
	movl 4(%esp), %ecx
	movl $0, %eax
L:	movb (%ecx), %dl
	testb %dl, %dl
	je E
	cmpb $'0', %dl
	jl F
	cmpb $'9', %dl
	jg F
	incl %eax
F:	incl %ecx
	jmp L
E:	ret
