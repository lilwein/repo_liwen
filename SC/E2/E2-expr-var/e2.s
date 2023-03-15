# scrivere la soluzione qui...
.globl f
f:
	movl 4(%esp), %eax
	movl %eax, %ecx		#c = a;
	movl %eax, %edx		#d = a;
	imull %eax, %ecx		#c *= a;
	imull $2, %ecx		#c *= 2;
	imull $7, %edx		#d *=7;
	subl %edx, %ecx		#c -=d;
	addl $1, %ecx		#c +=1;
	movl %ecx, %eax		#a = c;
	ret
