# scrivere la soluzione qui...
.globl comp
comp:
movl 4(%esp), %eax
movl 8(%esp), %ecx
movl (%eax), %eax
subl (%ecx), %eax
ret
