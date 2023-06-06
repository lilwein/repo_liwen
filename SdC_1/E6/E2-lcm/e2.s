# Scrivere la soluzione qui...
.globl lcm
lcm:							#int lcm(int x, int y){
	pushl %esi
	pushl %edi
	pushl %ebx
	movl 16(%esp), %esi				#	int si = x;
	movl 20 (%esp), %edi			#	int di = y;
	movl %edi, %ecx					#	int c = di;
	cmpl %edi, %esi					#	if (si <= di)
	jbe L							#	goto L;
	movl %esi, %ecx					#	c = si;
L:	movl %ecx, %eax					#	int a = c;
	movl %eax, %edx					#	int d = a
	sarl $31, %edx
	idivl %esi						#	d = c % si;
	testl %edx, %edx				#			  d == 0;
	setzb %bl						#	char bl = 
	movl %ecx, %eax
	movl %eax, %edx					#	d = a;
	sarl $31, %edx					
	idivl %edi						#	d = c % di;
	testl %edx, %edx				#				d == 0;
	setzb %bh						#	char bh = 
	andb %bh, %bl					#	bl = bl & bh  \  if (bl == 0)
	jz F							#	goto F;
	movl %ecx, %eax					#	a = c;
	popl %ebx
	popl %edi
	popl %esi
	ret								#	return a;
F:	incl %ecx						#	c++;
	jmp L							#	goto L;
									#}
