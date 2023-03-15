# Scrivere la soluzione qui...
.globl charfreq
charfreq:								#char charfreq(const char* s) {
	pushl %edi
	pushl %esi
	pushl %ebx
	subl $1036, %esp					#	unsigned freq[256];
	
	leal 12(%esp), %ebx
	movl %ebx, (%esp)
	movl $0, 4(%esp)
	movl $1024, 8(%esp)
	call memset							#   memset(freq, 0, 256*sizeof(unsigned));
	movl 1052(%esp), %esi
L1:	movb (%esi), %cl					#	char c = *s;
	movsbl %cl, %ecx
	testl %ecx, %ecx					#	if (c == 0)
	jz F								#		goto F;
	incl (%ebx, %ecx, 4)				#	freq[c]++;
	incl %esi							# 	s++;
	jmp L1								#	goto L1;
F:	xorl %eax, %eax						#	unsigned maxi = 0;
	movl (%ebx), %edx					#   unsigned maxf = freq[0];
	movl $1, %edi						#	int i = 0;
L2:	cmpl $256, %edi						#	if(i >= 256)
	jge E								#		goto E;
	cmpl %edx, (%ebx, %edi, 4)			#	if (freq[i] <= maxf)
	jbe E0								#		goto E0;
	movl %edi, %eax						#	maxi = i;
	movl (%ebx, %edi, 4), %edx			#	maxf = freq[i];
E0:	incl %edi							# ++i;
	jmp L2								#	goto L2;

E:	addl $1036, %esp					#	return maxi;
	popl %ebx
	popl %esi
	popl %edi
	ret
#}
