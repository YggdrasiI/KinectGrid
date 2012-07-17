	.file	"myblob.c"
	.text
.Ltext0:
	.local	Leaf
	.comm	Leaf,44,32
	.type	gen_redundant_information, @function
gen_redundant_information:
.LFB0:
	.file 1 "tree.h"
	.loc 1 35 0
	.cfi_startproc
	pushl	%ebp
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI1:
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 36 0
	movl	8(%ebp), %eax
	movl	$0, 16(%eax)
	.loc 1 37 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	.L2
.LBB2:
	.loc 1 38 0
	movl	$0, -12(%ebp)
	.loc 1 39 0
	movl	8(%ebp), %eax
	leal	16(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%edx, 8(%esp)
	leal	-12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	gen_redundant_information
	.loc 1 40 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$1, %edx
	cmpl	%edx, %eax
	jge	.L2
	.loc 1 40 0 is_stmt 0 discriminator 1
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
.L2:
.LBE2:
	.loc 1 42 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L1
	.loc 1 43 0
	addl	$4, 16(%ebp)
	.loc 1 44 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	16(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	gen_redundant_information
.L1:
	.loc 1 46 0
	leave
	.cfi_restore 5
.LCFI2:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	gen_redundant_information, .-gen_redundant_information
	.type	add_child, @function
add_child:
.LFB1:
	.loc 1 48 0
	.cfi_startproc
	pushl	%ebp
.LCFI3:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI4:
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 49 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	jne	.L5
	.loc 1 50 0
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 8(%eax)
	jmp	.L6
.L5:
.LBB3:
	.loc 1 52 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -12(%ebp)
	.loc 1 53 0
	jmp	.L7
.L8:
	.loc 1 54 0
	movl	-12(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -12(%ebp)
.L7:
	.loc 1 53 0 discriminator 1
	movl	-12(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	jne	.L8
	.loc 1 56 0
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%eax)
.L6:
.LBE3:
	.loc 1 59 0
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	.loc 1 62 0
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 16(%eax)
	.loc 1 63 0
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	.loc 1 64 0
	jmp	.L9
.L11:
	.loc 1 65 0
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	leal	1(%eax), %edx
	movl	-8(%ebp), %eax
	movl	%edx, 12(%eax)
	.loc 1 66 0
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	.loc 1 67 0
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -8(%ebp)
.L9:
	.loc 1 64 0 discriminator 1
	cmpl	$0, -8(%ebp)
	je	.L4
	.loc 1 64 0 is_stmt 0 discriminator 2
	movl	-8(%ebp), %eax
	movl	12(%eax), %edx
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	addl	$1, %eax
	cmpl	%eax, %edx
	jl	.L11
.L4:
	.loc 1 69 0 is_stmt 1
	leave
	.cfi_restore 5
.LCFI5:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	add_child, .-add_child
	.type	number_of_nodes, @function
number_of_nodes:
.LFB2:
	.loc 1 71 0
	.cfi_startproc
	pushl	%ebp
.LCFI6:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI7:
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 72 0
	movl	$1, -8(%ebp)
	.loc 1 73 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -4(%ebp)
	.loc 1 74 0
	jmp	.L13
.L19:
	.loc 1 75 0
	addl	$1, -8(%ebp)
	.loc 1 76 0
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	.L14
	.loc 1 76 0 is_stmt 0 discriminator 1
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	.L13
.L14:
	.loc 1 77 0 is_stmt 1
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L15
	.loc 1 77 0 is_stmt 0 discriminator 1
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	.L13
.L15:
	.loc 1 79 0 is_stmt 1
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	.loc 1 80 0
	jmp	.L16
.L18:
	.loc 1 80 0 is_stmt 0 discriminator 1
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
.L16:
	movl	-4(%ebp), %eax
	cmpl	8(%ebp), %eax
	je	.L17
	.loc 1 80 0 discriminator 2
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L18
.L17:
	.loc 1 81 0 is_stmt 1
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -4(%ebp)
.L13:
	.loc 1 74 0 discriminator 1
	cmpl	$0, -4(%ebp)
	jne	.L19
	.loc 1 84 0
	movl	-8(%ebp), %eax
	.loc 1 85 0
	leave
	.cfi_restore 5
.LCFI8:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	number_of_nodes, .-number_of_nodes
	.section	.rodata
.LC0:
	.string	"%2i (w%i,d%i) "
.LC1:
	.string	"\342\206\222"
.LC2:
	.string	"\342\206\230"
	.text
	.type	print_tree, @function
print_tree:
.LFB3:
	.loc 1 88 0
	.cfi_startproc
	pushl	%ebp
.LCFI9:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI10:
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.loc 1 90 0
	movl	$0, -12(%ebp)
	.loc 1 93 0
	movl	8(%ebp), %eax
	movl	12(%eax), %ebx
	.cfi_offset 3, -12
	movl	8(%ebp), %eax
	movl	16(%eax), %ecx
	movl	8(%ebp), %eax
	movl	20(%eax), %edx
	movl	$.LC0, %eax
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	.loc 1 94 0
	addl	$12, -12(%ebp)
	.loc 1 95 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	.L21
	.loc 1 96 0
	movl	$.LC1, %eax
	movl	%eax, (%esp)
	call	printf
	.loc 1 97 0
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	addl	%eax, %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	print_tree
	jmp	.L22
.L21:
	.loc 1 99 0
	movl	$10, (%esp)
	call	putchar
.L22:
	.loc 1 102 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L20
	.loc 1 104 0
	movl	$0, -16(%ebp)
	jmp	.L24
.L25:
	.loc 1 104 0 is_stmt 0 discriminator 2
	movl	$32, (%esp)
	call	putchar
	addl	$1, -16(%ebp)
.L24:
	.loc 1 104 0 discriminator 1
	movl	12(%ebp), %eax
	subl	$1, %eax
	cmpl	-16(%ebp), %eax
	jg	.L25
	.loc 1 105 0 is_stmt 1
	movl	$.LC2, %eax
	movl	%eax, (%esp)
	call	printf
	.loc 1 106 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	print_tree
.L20:
	.loc 1 107 0
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
.LCFI11:
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE3:
	.size	print_tree, .-print_tree
	.type	cmp, @function
cmp:
.LFB5:
	.loc 1 141 0
	.cfi_startproc
	pushl	%ebp
.LCFI12:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI13:
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 142 0
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	%eax, %edx
	jge	.L27
	.loc 1 142 0 is_stmt 0 discriminator 1
	movl	$0, %eax
	jmp	.L28
.L27:
	.loc 1 143 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	12(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	%eax, %edx
	jle	.L29
	.loc 1 143 0 is_stmt 0 discriminator 1
	movl	$1, %eax
	jmp	.L28
.L29:
	.loc 1 144 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	16(%eax), %edx
	movl	12(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	%eax, %edx
	jge	.L30
	.loc 1 144 0 is_stmt 0 discriminator 1
	movl	$0, %eax
	jmp	.L28
.L30:
	.loc 1 145 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	16(%eax), %edx
	movl	12(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	%eax, %edx
	jle	.L31
	.loc 1 145 0 is_stmt 0 discriminator 1
	movl	$1, %eax
	jmp	.L28
.L31:
	.loc 1 151 0 is_stmt 1
	movl	$0, -20(%ebp)
	.loc 1 152 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 153 0
	movl	12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -12(%ebp)
	.loc 1 154 0
	jmp	.L32
.L34:
	.loc 1 155 0
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	cmp
	movl	%eax, -20(%ebp)
	.loc 1 156 0
	movl	-16(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -16(%ebp)
	.loc 1 157 0
	movl	-12(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -12(%ebp)
.L32:
	.loc 1 154 0 discriminator 1
	cmpl	$0, -20(%ebp)
	jne	.L33
	.loc 1 154 0 is_stmt 0 discriminator 2
	cmpl	$0, -16(%ebp)
	jne	.L34
.L33:
	.loc 1 159 0 is_stmt 1
	movl	-20(%ebp), %eax
.L28:
	.loc 1 160 0
	leave
	.cfi_restore 5
.LCFI14:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	cmp, .-cmp
	.type	swap_pnode, @function
swap_pnode:
.LFB6:
	.loc 1 163 0
	.cfi_startproc
	pushl	%ebp
.LCFI15:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI16:
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 164 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	.loc 1 165 0
	movl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 166 0
	movl	12(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%edx, (%eax)
	.loc 1 167 0
	leave
	.cfi_restore 5
.LCFI17:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	swap_pnode, .-swap_pnode
	.type	quicksort_silbings, @function
quicksort_silbings:
.LFB7:
	.loc 1 170 0
	.cfi_startproc
	pushl	%ebp
.LCFI18:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI19:
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 173 0
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	cmpl	$7, %eax
	jle	.L41
.L37:
	.loc 1 175 0
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	.loc 1 176 0
	movl	8(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -12(%ebp)
	.loc 1 177 0
	jmp	.L39
.L40:
	.loc 1 179 0
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-16(%ebp), %eax
	movl	(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	cmp
	testl	%eax, %eax
	je	.L39
	.loc 1 180 0
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	swap_pnode
	.loc 1 181 0
	addl	$4, -12(%ebp)
.L39:
	.loc 1 177 0 discriminator 1
	addl	$4, -16(%ebp)
	movl	-16(%ebp), %eax
	cmpl	12(%ebp), %eax
	jne	.L40
	.loc 1 184 0
	movl	-12(%ebp), %eax
	subl	$4, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	swap_pnode
	.loc 1 185 0
	movl	-12(%ebp), %eax
	subl	$4, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	quicksort_silbings
	.loc 1 186 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	quicksort_silbings
	jmp	.L36
.L41:
	.loc 1 174 0
	nop
.L36:
	.loc 1 187 0
	leave
	.cfi_restore 5
.LCFI20:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	quicksort_silbings, .-quicksort_silbings
	.type	sort_tree, @function
sort_tree:
.LFB8:
	.loc 1 198 0
	.cfi_startproc
	pushl	%ebp
.LCFI21:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI22:
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 199 0
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	testl	%eax, %eax
	je	.L50
.L43:
	.loc 1 201 0
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -16(%ebp)
	.loc 1 202 0
	movl	-16(%ebp), %eax
	movl	%eax, -24(%ebp)
	.loc 1 203 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -20(%ebp)
	.loc 1 204 0
	jmp	.L45
.L46:
	.loc 1 205 0
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	sort_tree
	.loc 1 206 0
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%edx, (%eax)
	.loc 1 207 0
	movl	-20(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -20(%ebp)
	.loc 1 208 0
	addl	$4, -24(%ebp)
.L45:
	.loc 1 204 0 discriminator 1
	cmpl	$0, -20(%ebp)
	jne	.L46
	.loc 1 211 0
	movl	8(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	$1, %eax
	jle	.L47
.LBB4:
	.loc 1 212 0
	movl	-24(%ebp), %eax
	movl	%eax, -12(%ebp)
	.loc 1 214 0
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	quicksort_silbings
	.loc 1 217 0
	movl	-16(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	.loc 1 218 0
	movl	8(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%edx, 8(%eax)
	.loc 1 219 0
	movl	-16(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -24(%ebp)
	.loc 1 220 0
	jmp	.L48
.L49:
	.loc 1 221 0
	movl	-24(%ebp), %eax
	movl	(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 1 222 0
	movl	-24(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	.loc 1 223 0
	addl	$4, -24(%ebp)
.L48:
	.loc 1 220 0 discriminator 1
	movl	-24(%ebp), %eax
	cmpl	-12(%ebp), %eax
	jb	.L49
	.loc 1 225 0
	movl	-20(%ebp), %eax
	movl	$0, 4(%eax)
.L47:
.LBE4:
	.loc 1 228 0
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	jmp	.L42
.L50:
	.loc 1 199 0
	nop
.L42:
	.loc 1 229 0
	leave
	.cfi_restore 5
.LCFI23:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	sort_tree, .-sort_tree
	.type	_gen_tree_id, @function
_gen_tree_id:
.LFB9:
	.loc 1 238 0
	.cfi_startproc
	pushl	%ebp
.LCFI24:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI25:
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.loc 1 239 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	.L52
	.cfi_offset 3, -12
	.loc 1 241 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	movl	$0, (%eax)
	.loc 1 242 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	leal	4(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 243 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	16(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_gen_tree_id
	jmp	.L53
.L52:
	.loc 1 245 0
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
.L53:
	.loc 1 247 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L51
	.loc 1 250 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	movl	8(%ebp), %edx
	movl	12(%edx), %ecx
	movl	16(%ebp), %edx
	movl	(%edx), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 1 251 0
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	leal	4(%eax), %edx
	movl	12(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 252 0
	movl	8(%ebp), %eax
	movl	12(%eax), %edx
	movl	16(%ebp), %eax
	movl	%edx, (%eax)
	.loc 1 253 0
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	16(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_gen_tree_id
.L51:
	.loc 1 255 0
	addl	$20, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
.LCFI26:
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE9:
	.size	_gen_tree_id, .-_gen_tree_id
	.type	gen_tree_id, @function
gen_tree_id:
.LFB10:
	.loc 1 260 0
	.cfi_startproc
	pushl	%ebp
.LCFI27:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI28:
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 261 0
	movl	$0, -12(%ebp)
	.loc 1 263 0
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, (%eax)
	.loc 1 264 0
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	%eax, 12(%ebp)
	.loc 1 265 0
	leal	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_gen_tree_id
	.loc 1 266 0
	movl	$10, (%esp)
	call	putchar
	.loc 1 267 0
	leave
	.cfi_restore 5
.LCFI29:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE10:
	.size	gen_tree_id, .-gen_tree_id
	.section	.rodata
	.align 4
	.type	TREE_CHILDREN_MAX, @object
	.size	TREE_CHILDREN_MAX, 4
TREE_CHILDREN_MAX:
	.long	5
	.align 4
	.type	TREE_DEPTH_MAX, @object
	.size	TREE_DEPTH_MAX, 4
TREE_DEPTH_MAX:
	.long	5
	.text
	.type	tree_hashval, @function
tree_hashval:
.LFB11:
	.loc 1 279 0
	.cfi_startproc
	pushl	%ebp
.LCFI30:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI31:
	.cfi_def_cfa_register 5
	.loc 1 280 0
	movl	$-1, %eax
	.loc 1 281 0
	popl	%ebp
.LCFI32:
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE11:
	.size	tree_hashval, .-tree_hashval
	.type	sum_areas, @function
sum_areas:
.LFB12:
	.file 2 "myblob.c"
	.loc 2 44 0
	.cfi_startproc
	pushl	%ebp
.LCFI33:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI34:
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.loc 2 45 0
	movl	8(%ebp), %eax
	addl	$40, %eax
	movl	%eax, -12(%ebp)
	.loc 2 46 0
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	sall	$2, %eax
	addl	12(%ebp), %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 47 0
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	.L58
	.cfi_offset 3, -12
	.loc 2 47 0 is_stmt 0 discriminator 1
	movl	-12(%ebp), %eax
	movl	(%eax), %ebx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	sum_areas
	leal	(%ebx,%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, (%eax)
.L58:
	.loc 2 48 0 is_stmt 1
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L59
	.loc 2 48 0 is_stmt 0 discriminator 1
	movl	-12(%ebp), %eax
	movl	(%eax), %ebx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	sum_areas
	addl	%ebx, %eax
	jmp	.L60
.L59:
	.loc 2 49 0 is_stmt 1
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
.L60:
	.loc 2 50 0
	addl	$36, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
.LCFI35:
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE12:
	.size	sum_areas, .-sum_areas
	.type	find_connection_components, @function
find_connection_components:
.LFB13:
	.loc 2 57 0
	.cfi_startproc
	pushl	%ebp
.LCFI36:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI37:
	.cfi_def_cfa_register 5
	subl	$88, %esp
	movl	20(%ebp), %eax
	movb	%al, -28(%ebp)
	.loc 2 58 0
	movl	$0, -24(%ebp)
	movl	$0, -20(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -12(%ebp)
	.loc 2 59 0
	movzbl	-28(%ebp), %eax
	movl	24(%ebp), %edx
	movl	%edx, 32(%esp)
	movl	%eax, 28(%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 20(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 24(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	find_connection_components_with_roi
	.loc 2 60 0
	leave
	.cfi_restore 5
.LCFI38:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE13:
	.size	find_connection_components, .-find_connection_components
	.section	.rodata
	.align 4
.LC3:
	.string	"[blob.c] MyBlobRect not matching.\n"
	.align 4
.LC4:
	.string	"MyBlobRect of %i: x=%i y=%i w=%i h=%i\n"
	.text
	.type	find_connection_components_with_roi, @function
find_connection_components_with_roi:
.LFB14:
	.loc 2 69 0
	.cfi_startproc
	pushl	%ebp
.LCFI39:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI40:
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$204, %esp
	movl	36(%ebp), %eax
	movb	%al, -172(%ebp)
	.loc 2 71 0
	movl	20(%ebp), %eax
	movl	12(%ebp), %edx
	subl	%eax, %edx
	movl	28(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -88(%ebp)
	.loc 2 72 0
	movl	24(%ebp), %eax
	movl	16(%ebp), %edx
	subl	%eax, %edx
	movl	32(%ebp), %eax
	movl	%edx, %ebx
	.cfi_offset 3, -20
	.cfi_offset 6, -16
	.cfi_offset 7, -12
	subl	%eax, %ebx
	movl	%ebx, %eax
	movl	%eax, -84(%ebp)
	.loc 2 73 0
	cmpl	$0, -88(%ebp)
	js	.L63
	.loc 2 73 0 is_stmt 0 discriminator 1
	cmpl	$0, -84(%ebp)
	jns	.L64
.L63:
	.loc 2 74 0 is_stmt 1
	movl	stderr, %eax
	movl	%eax, %edx
	movl	$.LC3, %eax
	movl	%edx, 12(%esp)
	movl	$34, 8(%esp)
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	fwrite
	.loc 2 75 0
	movl	40(%ebp), %eax
	movl	$0, (%eax)
	.loc 2 76 0
	movl	$0, %eax
	jmp	.L65
.L64:
	.loc 2 79 0
	movl	$-1, -168(%ebp)
	.loc 2 82 0
	movl	16(%ebp), %eax
	movl	12(%ebp), %edx
	addl	%edx, %eax
	movl	%eax, -160(%ebp)
	.loc 2 84 0
	movl	12(%ebp), %eax
	imull	16(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -80(%ebp)
	.loc 2 86 0
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -156(%ebp)
	.loc 2 87 0
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -152(%ebp)
	.loc 2 88 0
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -148(%ebp)
	.loc 2 92 0
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -144(%ebp)
	.loc 2 93 0
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -140(%ebp)
	.loc 2 94 0
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -136(%ebp)
	.loc 2 95 0
	movl	20(%ebp), %eax
	movl	%eax, -132(%ebp)
	movl	24(%ebp), %eax
	movl	%eax, -128(%ebp)
	.loc 2 98 0
	movl	24(%ebp), %eax
	imull	12(%ebp), %eax
	movl	%eax, %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	addl	8(%ebp), %eax
	movl	%eax, -76(%ebp)
	.loc 2 99 0
	movl	28(%ebp), %eax
	addl	-76(%ebp), %eax
	movl	%eax, -124(%ebp)
	.loc 2 101 0
	movl	32(%ebp), %eax
	subl	$1, %eax
	imull	12(%ebp), %eax
	addl	-124(%ebp), %eax
	movl	%eax, -72(%ebp)
	.loc 2 104 0
	movl	-76(%ebp), %eax
	movl	%eax, -120(%ebp)
	.loc 2 105 0
	movl	-76(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	-80(%ebp), %eax
	movl	%eax, -116(%ebp)
	.loc 2 114 0
	addl	$1, -168(%ebp)
	movl	-116(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	-120(%ebp), %ecx
	movl	-76(%ebp), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$1, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	cmpl	-160(%ebp), %eax
	jl	.L66
	.loc 2 114 0 is_stmt 0 discriminator 1
	fildl	12(%ebp)
	fildl	16(%ebp)
	fmulp	%st, %st(1)
	fildl	-160(%ebp)
	fmulp	%st, %st(1)
	movl	-120(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -176(%ebp)
	fildl	-176(%ebp)
	fdivrp	%st, %st(1)
	fnstcw	-170(%ebp)
	movzwl	-170(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -178(%ebp)
	fldcw	-178(%ebp)
	fistpl	-160(%ebp)
	fldcw	-170(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -156(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -152(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -148(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -144(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -140(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -136(%ebp)
.L66:
	.loc 2 116 0 is_stmt 1
	addl	$4, -116(%ebp)
	addl	$1, -120(%ebp)
	.loc 2 119 0
	addl	$1, -132(%ebp)
	.loc 2 126 0
	jmp	.L67
.L72:
	.loc 2 127 0
	movl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L68
	.loc 2 128 0
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L69
	.loc 2 130 0
	movl	-116(%ebp), %eax
	movl	-4(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 132 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 135 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L70
.L69:
	.loc 2 138 0
	addl	$1, -168(%ebp)
	movl	-116(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	-120(%ebp), %ecx
	movl	-76(%ebp), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$1, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	cmpl	-160(%ebp), %eax
	jl	.L70
	.loc 2 138 0 is_stmt 0 discriminator 1
	fildl	12(%ebp)
	fildl	16(%ebp)
	fmulp	%st, %st(1)
	fildl	-160(%ebp)
	fmulp	%st, %st(1)
	movl	-120(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -176(%ebp)
	fildl	-176(%ebp)
	fdivrp	%st, %st(1)
	fnstcw	-170(%ebp)
	movzwl	-170(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -178(%ebp)
	fldcw	-178(%ebp)
	fistpl	-160(%ebp)
	fldcw	-170(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -156(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -152(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -148(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -144(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -140(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -136(%ebp)
	jmp	.L70
.L68:
	.loc 2 141 0 is_stmt 1
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L71
	.loc 2 143 0
	movl	-116(%ebp), %eax
	movl	-4(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 145 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 148 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L70
.L71:
	.loc 2 151 0
	addl	$1, -168(%ebp)
	movl	-116(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	-120(%ebp), %ecx
	movl	-76(%ebp), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$1, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	cmpl	-160(%ebp), %eax
	jl	.L70
	.loc 2 151 0 is_stmt 0 discriminator 1
	fildl	12(%ebp)
	fildl	16(%ebp)
	fmulp	%st, %st(1)
	fildl	-160(%ebp)
	fmulp	%st, %st(1)
	movl	-120(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -176(%ebp)
	fildl	-176(%ebp)
	fdivrp	%st, %st(1)
	fnstcw	-170(%ebp)
	movzwl	-170(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -178(%ebp)
	fldcw	-178(%ebp)
	fistpl	-160(%ebp)
	fldcw	-170(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -156(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -152(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -148(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -144(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -140(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -136(%ebp)
.L70:
	.loc 2 155 0 is_stmt 1
	addl	$1, -132(%ebp)
	.loc 2 126 0
	addl	$4, -116(%ebp)
	addl	$1, -120(%ebp)
.L67:
	.loc 2 126 0 is_stmt 0 discriminator 1
	movl	-120(%ebp), %eax
	cmpl	-124(%ebp), %eax
	jb	.L72
	.loc 2 163 0 is_stmt 1
	movl	20(%ebp), %eax
	addl	-88(%ebp), %eax
	addl	%eax, -120(%ebp)
	.loc 2 164 0
	movl	20(%ebp), %eax
	addl	-88(%ebp), %eax
	sall	$2, %eax
	addl	%eax, -116(%ebp)
	.loc 2 166 0
	movl	12(%ebp), %eax
	addl	%eax, -124(%ebp)
	.loc 2 168 0
	movl	20(%ebp), %eax
	movl	%eax, -132(%ebp)
	.loc 2 169 0
	addl	$1, -128(%ebp)
	.loc 2 174 0
	jmp	.L73
.L124:
	.loc 2 177 0
	movl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L74
	.loc 2 178 0
	movl	12(%ebp), %eax
	negl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L75
	.loc 2 179 0
	movl	12(%ebp), %eax
	sall	$2, %eax
	negl	%eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 180 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 183 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L76
.L75:
	.loc 2 186 0
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L77
	.loc 2 187 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 188 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 191 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 192 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	(%eax), %edx
	subl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L76
.L77:
	.loc 2 196 0
	addl	$1, -168(%ebp)
	movl	-116(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	-120(%ebp), %ecx
	movl	-76(%ebp), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$1, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	cmpl	-160(%ebp), %eax
	jl	.L76
	.loc 2 196 0 is_stmt 0 discriminator 1
	fildl	12(%ebp)
	fildl	16(%ebp)
	fmulp	%st, %st(1)
	fildl	-160(%ebp)
	fmulp	%st, %st(1)
	movl	-120(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -176(%ebp)
	fildl	-176(%ebp)
	fdivrp	%st, %st(1)
	fnstcw	-170(%ebp)
	movzwl	-170(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -178(%ebp)
	fldcw	-178(%ebp)
	fistpl	-160(%ebp)
	fldcw	-170(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -156(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -152(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -148(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -144(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -140(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -136(%ebp)
	jmp	.L76
.L74:
	.loc 2 199 0 is_stmt 1
	movl	12(%ebp), %eax
	negl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L78
	.loc 2 200 0
	movl	12(%ebp), %eax
	sall	$2, %eax
	negl	%eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 201 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 204 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L76
.L78:
	.loc 2 207 0
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L79
	.loc 2 208 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 209 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 212 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 213 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	(%eax), %edx
	subl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L76
.L79:
	.loc 2 217 0
	addl	$1, -168(%ebp)
	movl	-116(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	-120(%ebp), %ecx
	movl	-76(%ebp), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$1, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	cmpl	-160(%ebp), %eax
	jl	.L76
	.loc 2 217 0 is_stmt 0 discriminator 1
	fildl	12(%ebp)
	fildl	16(%ebp)
	fmulp	%st, %st(1)
	fildl	-160(%ebp)
	fmulp	%st, %st(1)
	movl	-120(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -176(%ebp)
	fildl	-176(%ebp)
	fdivrp	%st, %st(1)
	fnstcw	-170(%ebp)
	movzwl	-170(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -178(%ebp)
	fldcw	-178(%ebp)
	fistpl	-160(%ebp)
	fldcw	-170(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -156(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -152(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -148(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -144(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -140(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -136(%ebp)
.L76:
	.loc 2 222 0 is_stmt 1
	addl	$4, -116(%ebp)
	addl	$1, -120(%ebp)
	.loc 2 224 0
	addl	$1, -132(%ebp)
	.loc 2 229 0
	jmp	.L80
.L109:
	.loc 2 230 0
	movl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L81
	.loc 2 231 0
	movl	12(%ebp), %eax
	negl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L82
	.loc 2 232 0
	movl	12(%ebp), %eax
	sall	$2, %eax
	negl	%eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 233 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 236 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L83
	.loc 2 236 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L83:
	.loc 2 243 0 is_stmt 1
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L84
	.loc 2 244 0
	movl	-116(%ebp), %eax
	subl	$4, %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -68(%ebp)
	.loc 2 245 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -64(%ebp)
	.loc 2 246 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jge	.L85
	.loc 2 247 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L85:
	.loc 2 248 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jle	.L84
	.loc 2 249 0
	movl	-116(%ebp), %eax
	subl	$4, %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L82:
	.loc 2 252 0
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L86
	.loc 2 253 0
	movl	-116(%ebp), %eax
	movl	-4(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 254 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 257 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jge	.L87
	.loc 2 257 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L87:
	.loc 2 263 0 is_stmt 1
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L84
	.loc 2 264 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -68(%ebp)
	.loc 2 265 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -64(%ebp)
	.loc 2 266 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jge	.L88
	.loc 2 267 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L88:
	.loc 2 268 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jle	.L84
	.loc 2 269 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L86:
	.loc 2 275 0
	movl	12(%ebp), %eax
	notl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L89
	.loc 2 276 0
	movl	12(%ebp), %eax
	notl	%eax
	sall	$2, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 277 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 280 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jge	.L90
	.loc 2 280 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L90:
	.loc 2 281 0 is_stmt 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L91
	.loc 2 281 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L91:
	.loc 2 285 0 is_stmt 1
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L84
	.loc 2 286 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -68(%ebp)
	.loc 2 287 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -64(%ebp)
	.loc 2 288 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jge	.L92
	.loc 2 289 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L92:
	.loc 2 290 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jle	.L84
	.loc 2 291 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L89:
	.loc 2 297 0
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L93
	.loc 2 298 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 301 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jle	.L94
	.loc 2 301 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	(%eax), %edx
	subl	$1, %edx
	movl	%edx, (%eax)
.L94:
	.loc 2 302 0 is_stmt 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L95
	.loc 2 302 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L95:
	.loc 2 304 0 is_stmt 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L84
.L93:
	.loc 2 307 0
	addl	$1, -168(%ebp)
	movl	-116(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	-120(%ebp), %ecx
	movl	-76(%ebp), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$1, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	cmpl	-160(%ebp), %eax
	jl	.L84
	.loc 2 307 0 is_stmt 0 discriminator 1
	fildl	12(%ebp)
	fildl	16(%ebp)
	fmulp	%st, %st(1)
	fildl	-160(%ebp)
	fmulp	%st, %st(1)
	movl	-120(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -176(%ebp)
	fildl	-176(%ebp)
	fdivrp	%st, %st(1)
	fnstcw	-170(%ebp)
	movzwl	-170(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -178(%ebp)
	fldcw	-178(%ebp)
	fistpl	-160(%ebp)
	fldcw	-170(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -156(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -152(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -148(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -144(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -140(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -136(%ebp)
	jmp	.L84
.L81:
	.loc 2 310 0 is_stmt 1
	movl	12(%ebp), %eax
	negl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L96
	.loc 2 311 0
	movl	12(%ebp), %eax
	sall	$2, %eax
	negl	%eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 312 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 315 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L97
	.loc 2 315 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L97:
	.loc 2 322 0 is_stmt 1
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L84
	.loc 2 323 0
	movl	-116(%ebp), %eax
	subl	$4, %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -68(%ebp)
	.loc 2 324 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -64(%ebp)
	.loc 2 325 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jge	.L98
	.loc 2 326 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L98:
	.loc 2 327 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jle	.L84
	.loc 2 328 0
	movl	-116(%ebp), %eax
	subl	$4, %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L96:
	.loc 2 331 0
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L99
	.loc 2 332 0
	movl	-116(%ebp), %eax
	movl	-4(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 333 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 336 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jge	.L100
	.loc 2 336 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L100:
	.loc 2 342 0 is_stmt 1
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L84
	.loc 2 343 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -68(%ebp)
	.loc 2 344 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -64(%ebp)
	.loc 2 345 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jge	.L101
	.loc 2 346 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L101:
	.loc 2 347 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jle	.L84
	.loc 2 348 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L99:
	.loc 2 354 0
	movl	12(%ebp), %eax
	notl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L102
	.loc 2 355 0
	movl	12(%ebp), %eax
	notl	%eax
	sall	$2, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 356 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 359 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jge	.L103
	.loc 2 359 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L103:
	.loc 2 360 0 is_stmt 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L104
	.loc 2 360 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L104:
	.loc 2 364 0 is_stmt 1
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L84
	.loc 2 365 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -68(%ebp)
	.loc 2 366 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -64(%ebp)
	.loc 2 367 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jge	.L105
	.loc 2 368 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L105:
	.loc 2 369 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jle	.L84
	.loc 2 370 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L84
.L102:
	.loc 2 376 0
	movl	12(%ebp), %eax
	movl	$1, %edx
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L106
	.loc 2 377 0
	movl	12(%ebp), %edx
	movl	$0, %eax
	subl	%edx, %eax
	sall	$2, %eax
	addl	$4, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 380 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jle	.L107
	.loc 2 380 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	(%eax), %edx
	subl	$1, %edx
	movl	%edx, (%eax)
.L107:
	.loc 2 381 0 is_stmt 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L108
	.loc 2 381 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L108:
	.loc 2 383 0 is_stmt 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L84
.L106:
	.loc 2 386 0
	addl	$1, -168(%ebp)
	movl	-116(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	-120(%ebp), %ecx
	movl	-76(%ebp), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$1, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	cmpl	-160(%ebp), %eax
	jl	.L84
	.loc 2 386 0 is_stmt 0 discriminator 1
	fildl	12(%ebp)
	fildl	16(%ebp)
	fmulp	%st, %st(1)
	fildl	-160(%ebp)
	fmulp	%st, %st(1)
	movl	-120(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -176(%ebp)
	fildl	-176(%ebp)
	fdivrp	%st, %st(1)
	fnstcw	-170(%ebp)
	movzwl	-170(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -178(%ebp)
	fldcw	-178(%ebp)
	fistpl	-160(%ebp)
	fldcw	-170(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -156(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -152(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -148(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -144(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -140(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -136(%ebp)
.L84:
	.loc 2 390 0 is_stmt 1
	addl	$1, -132(%ebp)
	.loc 2 229 0
	addl	$4, -116(%ebp)
	addl	$1, -120(%ebp)
.L80:
	.loc 2 229 0 is_stmt 0 discriminator 1
	movl	-124(%ebp), %eax
	subl	$1, %eax
	cmpl	-120(%ebp), %eax
	ja	.L109
	.loc 2 396 0 is_stmt 1
	movl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L110
	.loc 2 397 0
	movl	12(%ebp), %eax
	negl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L111
	.loc 2 398 0
	movl	12(%ebp), %eax
	sall	$2, %eax
	negl	%eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 399 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 402 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L112
	.loc 2 402 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L112:
	.loc 2 409 0 is_stmt 1
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L113
	.loc 2 410 0
	movl	-116(%ebp), %eax
	subl	$4, %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -68(%ebp)
	.loc 2 411 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -64(%ebp)
	.loc 2 412 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jge	.L114
	.loc 2 413 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L113
.L114:
	.loc 2 414 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jle	.L113
	.loc 2 415 0
	movl	-116(%ebp), %eax
	subl	$4, %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L113
.L111:
	.loc 2 418 0
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L115
	.loc 2 419 0
	movl	-116(%ebp), %eax
	movl	-4(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 420 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 423 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jge	.L113
	.loc 2 423 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L113
.L115:
	.loc 2 426 0 is_stmt 1
	movl	12(%ebp), %eax
	notl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	jbe	.L116
	.loc 2 427 0
	movl	12(%ebp), %eax
	notl	%eax
	sall	$2, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 428 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 431 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jge	.L117
	.loc 2 431 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L117:
	.loc 2 432 0 is_stmt 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L113
	.loc 2 432 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L113
.L116:
	.loc 2 436 0 is_stmt 1
	addl	$1, -168(%ebp)
	movl	-116(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	-120(%ebp), %ecx
	movl	-76(%ebp), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$1, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	cmpl	-160(%ebp), %eax
	jl	.L113
	.loc 2 436 0 is_stmt 0 discriminator 1
	fildl	12(%ebp)
	fildl	16(%ebp)
	fmulp	%st, %st(1)
	fildl	-160(%ebp)
	fmulp	%st, %st(1)
	movl	-120(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -176(%ebp)
	fildl	-176(%ebp)
	fdivrp	%st, %st(1)
	fnstcw	-170(%ebp)
	movzwl	-170(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -178(%ebp)
	fldcw	-178(%ebp)
	fistpl	-160(%ebp)
	fldcw	-170(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -156(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -152(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -148(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -144(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -140(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -136(%ebp)
	jmp	.L113
.L110:
	.loc 2 439 0 is_stmt 1
	movl	12(%ebp), %eax
	negl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L118
	.loc 2 440 0
	movl	12(%ebp), %eax
	sall	$2, %eax
	negl	%eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 441 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 444 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L119
	.loc 2 444 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L119:
	.loc 2 451 0 is_stmt 1
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L113
	.loc 2 452 0
	movl	-116(%ebp), %eax
	subl	$4, %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -68(%ebp)
	.loc 2 453 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -64(%ebp)
	.loc 2 454 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jge	.L120
	.loc 2 455 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L113
.L120:
	.loc 2 456 0
	movl	-68(%ebp), %eax
	cmpl	-64(%ebp), %eax
	jle	.L113
	.loc 2 457 0
	movl	-116(%ebp), %eax
	subl	$4, %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-64(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L113
.L118:
	.loc 2 460 0
	movl	-120(%ebp), %eax
	subl	$1, %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L121
	.loc 2 461 0
	movl	-116(%ebp), %eax
	movl	-4(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 462 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 465 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jge	.L113
	.loc 2 465 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L113
.L121:
	.loc 2 468 0 is_stmt 1
	movl	12(%ebp), %eax
	notl	%eax
	addl	-120(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	-172(%ebp), %al
	ja	.L122
	.loc 2 469 0
	movl	12(%ebp), %eax
	notl	%eax
	sall	$2, %eax
	addl	-116(%ebp), %eax
	movl	(%eax), %edx
	movl	-116(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 470 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-116(%ebp), %edx
	movl	(%edx), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	.loc 2 473 0
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-132(%ebp), %eax
	jge	.L123
	.loc 2 473 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
.L123:
	.loc 2 474 0 is_stmt 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-128(%ebp), %eax
	jge	.L113
	.loc 2 474 0 is_stmt 0 discriminator 1
	movl	-116(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	addl	$1, %edx
	movl	%edx, (%eax)
	jmp	.L113
.L122:
	.loc 2 478 0 is_stmt 1
	addl	$1, -168(%ebp)
	movl	-116(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	-120(%ebp), %ecx
	movl	-76(%ebp), %edx
	movl	%ecx, %ebx
	subl	%edx, %ebx
	movl	%ebx, %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	-168(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$1, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-132(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	%edx, (%eax)
	movl	-168(%ebp), %eax
	cmpl	-160(%ebp), %eax
	jl	.L113
	.loc 2 478 0 is_stmt 0 discriminator 1
	fildl	12(%ebp)
	fildl	16(%ebp)
	fmulp	%st, %st(1)
	fildl	-160(%ebp)
	fmulp	%st, %st(1)
	movl	-120(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, -176(%ebp)
	fildl	-176(%ebp)
	fdivrp	%st, %st(1)
	fnstcw	-170(%ebp)
	movzwl	-170(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -178(%ebp)
	fldcw	-178(%ebp)
	fistpl	-160(%ebp)
	fldcw	-170(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -156(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -152(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -148(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -144(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -140(%ebp)
	movl	-160(%ebp), %eax
	sall	$2, %eax
	movl	%eax, 4(%esp)
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	realloc
	movl	%eax, -136(%ebp)
.L113:
	.loc 2 482 0 is_stmt 1
	addl	$4, -116(%ebp)
	addl	$1, -120(%ebp)
	.loc 2 484 0
	movl	20(%ebp), %eax
	movl	%eax, -132(%ebp)
	.loc 2 485 0
	addl	$1, -128(%ebp)
	.loc 2 174 0
	movl	20(%ebp), %eax
	addl	-88(%ebp), %eax
	addl	%eax, -120(%ebp)
	movl	20(%ebp), %eax
	addl	-88(%ebp), %eax
	sall	$2, %eax
	addl	%eax, -116(%ebp)
	movl	12(%ebp), %eax
	addl	%eax, -124(%ebp)
.L73:
	.loc 2 174 0 is_stmt 0 discriminator 1
	movl	-120(%ebp), %eax
	cmpl	-72(%ebp), %eax
	jb	.L124
	.loc 2 505 0 is_stmt 1
	movl	-168(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -60(%ebp)
	.loc 2 506 0
	movl	$0, -104(%ebp)
	.loc 2 508 0
	movl	-60(%ebp), %eax
	movl	$4, 4(%esp)
	movl	%eax, (%esp)
	call	calloc
	movl	%eax, -56(%ebp)
	.loc 2 509 0
	movl	-60(%ebp), %eax
	movl	$4, 4(%esp)
	movl	%eax, (%esp)
	call	calloc
	movl	%eax, -52(%ebp)
	.loc 2 511 0
	movl	$0, -164(%ebp)
	jmp	.L125
.L136:
	.loc 2 512 0
	movl	-164(%ebp), %eax
	movl	%eax, -112(%ebp)
	.loc 2 513 0
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -108(%ebp)
	.loc 2 514 0
	jmp	.L126
.L130:
	.loc 2 516 0
	movl	-108(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	-108(%ebp), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %ecx
	movl	-112(%ebp), %edx
	sall	$2, %edx
	addl	-152(%ebp), %edx
	movl	(%edx), %edx
	addl	%ecx, %edx
	movl	%edx, (%eax)
	.loc 2 517 0
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-152(%ebp), %eax
	movl	$0, (%eax)
	.loc 2 520 0
	movl	-108(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	(%eax), %edx
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jle	.L127
	.loc 2 521 0
	movl	-108(%ebp), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	-112(%ebp), %edx
	sall	$2, %edx
	addl	-144(%ebp), %edx
	movl	(%edx), %edx
	movl	%edx, (%eax)
.L127:
	.loc 2 522 0
	movl	-108(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jge	.L128
	.loc 2 523 0
	movl	-108(%ebp), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	-112(%ebp), %edx
	sall	$2, %edx
	addl	-140(%ebp), %edx
	movl	(%edx), %edx
	movl	%edx, (%eax)
.L128:
	.loc 2 524 0
	movl	-108(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jge	.L129
	.loc 2 525 0
	movl	-108(%ebp), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	-112(%ebp), %edx
	sall	$2, %edx
	addl	-136(%ebp), %edx
	movl	(%edx), %edx
	movl	%edx, (%eax)
.L129:
	.loc 2 527 0
	movl	-108(%ebp), %eax
	movl	%eax, -112(%ebp)
	.loc 2 528 0
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -108(%ebp)
.L126:
	.loc 2 514 0 discriminator 1
	movl	-108(%ebp), %eax
	cmpl	-112(%ebp), %eax
	jne	.L130
	.loc 2 532 0
	movl	$0, -96(%ebp)
	.loc 2 533 0
	movl	$0, -100(%ebp)
	jmp	.L131
.L134:
	.loc 2 534 0
	movl	-100(%ebp), %eax
	sall	$2, %eax
	addl	-56(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-112(%ebp), %eax
	jne	.L132
	.loc 2 535 0
	movl	$1, -96(%ebp)
	.loc 2 536 0
	jmp	.L133
.L132:
	.loc 2 533 0
	addl	$1, -100(%ebp)
.L131:
	.loc 2 533 0 is_stmt 0 discriminator 1
	movl	-100(%ebp), %eax
	cmpl	-104(%ebp), %eax
	jl	.L134
.L133:
	.loc 2 539 0 is_stmt 1
	cmpl	$0, -96(%ebp)
	jne	.L135
	.loc 2 540 0
	movl	-104(%ebp), %eax
	sall	$2, %eax
	addl	-56(%ebp), %eax
	movl	-112(%ebp), %edx
	movl	%edx, (%eax)
	.loc 2 541 0
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-52(%ebp), %eax
	movl	-104(%ebp), %edx
	movl	%edx, (%eax)
	.loc 2 542 0
	addl	$1, -104(%ebp)
.L135:
	.loc 2 511 0
	addl	$1, -164(%ebp)
.L125:
	.loc 2 511 0 is_stmt 0 discriminator 1
	movl	-164(%ebp), %eax
	cmpl	-60(%ebp), %eax
	jl	.L136
	.loc 2 552 0 is_stmt 1
	movl	-104(%ebp), %eax
	addl	$1, %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -48(%ebp)
	.loc 2 554 0
	movl	-104(%ebp), %eax
	addl	$1, %eax
	imull	$44, %eax, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -44(%ebp)
	.loc 2 556 0
	movl	$0, -100(%ebp)
	jmp	.L137
.L138:
	.loc 2 556 0 is_stmt 0 discriminator 2
	movl	-100(%ebp), %eax
	imull	$44, %eax, %eax
	addl	-44(%ebp), %eax
	movl	Leaf, %edx
	movl	%edx, (%eax)
	movl	Leaf+4, %edx
	movl	%edx, 4(%eax)
	movl	Leaf+8, %edx
	movl	%edx, 8(%eax)
	movl	Leaf+12, %edx
	movl	%edx, 12(%eax)
	movl	Leaf+16, %edx
	movl	%edx, 16(%eax)
	movl	Leaf+20, %edx
	movl	%edx, 20(%eax)
	movl	Leaf+24, %edx
	movl	%edx, 24(%eax)
	movl	Leaf+28, %edx
	movl	%edx, 28(%eax)
	movl	Leaf+32, %edx
	movl	%edx, 32(%eax)
	movl	Leaf+36, %edx
	movl	%edx, 36(%eax)
	movl	Leaf+40, %edx
	movl	%edx, 40(%eax)
	addl	$1, -100(%ebp)
.L137:
	.loc 2 556 0 discriminator 1
	movl	-104(%ebp), %eax
	addl	$1, %eax
	cmpl	-100(%ebp), %eax
	jg	.L138
	.loc 2 558 0 is_stmt 1
	movl	-44(%ebp), %eax
	movl	%eax, -40(%ebp)
	.loc 2 559 0
	movl	-44(%ebp), %eax
	movl	%eax, -92(%ebp)
	.loc 2 561 0
	movl	12(%ebp), %eax
	imull	16(%ebp), %eax
	movl	%eax, -36(%ebp)
	.loc 2 562 0
	movl	-40(%ebp), %eax
	movl	$-1, 20(%eax)
	.loc 2 565 0
	movl	$0, -100(%ebp)
	jmp	.L139
.L144:
	.loc 2 566 0
	addl	$44, -92(%ebp)
	.loc 2 567 0
	movl	-92(%ebp), %eax
	addl	$24, %eax
	movl	%eax, -32(%ebp)
	.loc 2 569 0
	movl	-100(%ebp), %eax
	sall	$2, %eax
	addl	-56(%ebp), %eax
	movl	(%eax), %edx
	movl	-92(%ebp), %eax
	movl	%edx, 20(%eax)
	.loc 2 571 0
	movl	-100(%ebp), %eax
	sall	$2, %eax
	addl	-56(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-156(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -28(%ebp)
	.loc 2 573 0
	movl	-28(%ebp), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	12(%ebp)
	movl	%eax, %edx
	movl	24(%ebp), %eax
	addl	%eax, %edx
	movl	-32(%ebp), %eax
	movl	%edx, 4(%eax)
	.loc 2 574 0
	movl	-100(%ebp), %eax
	sall	$2, %eax
	addl	-56(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-136(%ebp), %eax
	movl	(%eax), %edx
	movl	-32(%ebp), %eax
	movl	4(%eax), %eax
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	leal	1(%eax), %edx
	movl	-32(%ebp), %eax
	movl	%edx, 12(%eax)
	.loc 2 575 0
	movl	-100(%ebp), %eax
	sall	$2, %eax
	addl	-56(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-144(%ebp), %eax
	movl	(%eax), %edx
	movl	-32(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 576 0
	movl	-100(%ebp), %eax
	sall	$2, %eax
	addl	-56(%ebp), %eax
	movl	(%eax), %eax
	sall	$2, %eax
	addl	-140(%ebp), %eax
	movl	(%eax), %edx
	movl	-32(%ebp), %eax
	movl	(%eax), %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	leal	1(%eax), %edx
	movl	-32(%ebp), %eax
	movl	%edx, 8(%eax)
	.loc 2 579 0
	movl	-32(%ebp), %eax
	.loc 2 577 0
	movl	12(%eax), %edi
	.loc 2 579 0
	movl	-32(%ebp), %eax
	.loc 2 577 0
	movl	8(%eax), %esi
	.loc 2 578 0
	movl	-32(%ebp), %eax
	.loc 2 577 0
	movl	4(%eax), %ebx
	.loc 2 578 0
	movl	-32(%ebp), %eax
	.loc 2 577 0
	movl	(%eax), %ecx
	movl	-92(%ebp), %eax
	movl	20(%eax), %edx
	movl	$.LC4, %eax
	movl	%edi, 20(%esp)
	movl	%esi, 16(%esp)
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	.loc 2 585 0
	movl	28(%ebp), %eax
	cmpl	-28(%ebp), %eax
	jle	.L140
	.loc 2 589 0
	movl	-92(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-40(%ebp), %eax
	movl	%eax, (%esp)
	call	add_child
	jmp	.L141
.L140:
	.loc 2 592 0
	movl	-28(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	sall	$2, %eax
	addl	-80(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -112(%ebp)
	.loc 2 594 0
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -108(%ebp)
	.loc 2 595 0
	jmp	.L142
.L143:
	.loc 2 596 0
	movl	-108(%ebp), %eax
	movl	%eax, -112(%ebp)
	.loc 2 597 0
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-148(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -108(%ebp)
.L142:
	.loc 2 595 0 discriminator 1
	movl	-112(%ebp), %eax
	cmpl	-108(%ebp), %eax
	jne	.L143
	.loc 2 601 0
	movl	-112(%ebp), %eax
	sall	$2, %eax
	addl	-52(%ebp), %eax
	movl	(%eax), %eax
	addl	$1, %eax
	imull	$44, %eax, %eax
	addl	-40(%ebp), %eax
	movl	-92(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	add_child
.L141:
	.loc 2 565 0
	addl	$1, -100(%ebp)
.L139:
	.loc 2 565 0 is_stmt 0 discriminator 1
	movl	-100(%ebp), %eax
	cmpl	-104(%ebp), %eax
	jl	.L144
	.loc 2 608 0 is_stmt 1
	movl	-40(%ebp), %eax
	movl	8(%eax), %eax
	movl	-152(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	sum_areas
	.loc 2 610 0
	movl	-40(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, (%esp)
	call	sort_tree
	.loc 2 613 0
	movl	-48(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 615 0
	movl	-56(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 616 0
	movl	-52(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 617 0
	movl	-148(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 618 0
	movl	-152(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 619 0
	movl	-156(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 620 0
	movl	-80(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 621 0
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 622 0
	movl	-140(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 623 0
	movl	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 626 0
	movl	-104(%ebp), %eax
	leal	1(%eax), %edx
	movl	40(%ebp), %eax
	movl	%edx, (%eax)
	.loc 2 627 0
	movl	-44(%ebp), %eax
.L65:
	.loc 2 628 0
	addl	$204, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
.LCFI41:
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE14:
	.size	find_connection_components_with_roi, .-find_connection_components_with_roi
	.globl	myblob_create
	.type	myblob_create, @function
myblob_create:
.LFB15:
	.loc 2 635 0
	.cfi_startproc
	pushl	%ebp
.LCFI42:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI43:
	.cfi_def_cfa_register 5
	subl	$56, %esp
	.loc 2 636 0
	movl	$32, (%esp)
	call	malloc
	movl	%eax, -12(%ebp)
	.loc 2 637 0
	movl	-12(%ebp), %eax
	movl	$0, (%eax)
	.loc 2 638 0
	movl	-12(%ebp), %eax
	movl	$0, 4(%eax)
	.loc 2 639 0
	movl	$0, -28(%ebp)
	movl	$2147483647, -24(%ebp)
	movl	$0, -20(%ebp)
	movl	$2147483647, -16(%ebp)
	.loc 2 640 0
	movl	-12(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-24(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	-20(%ebp), %edx
	movl	%edx, 16(%eax)
	movl	-16(%ebp), %edx
	movl	%edx, 20(%eax)
	.loc 2 641 0
	movl	-12(%ebp), %eax
	.loc 2 642 0
	leave
	.cfi_restore 5
.LCFI44:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE15:
	.size	myblob_create, .-myblob_create
	.globl	myblob_destroy
	.type	myblob_destroy, @function
myblob_destroy:
.LFB16:
	.loc 2 644 0
	.cfi_startproc
	pushl	%ebp
.LCFI45:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI46:
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 2 645 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	.L147
	.loc 2 646 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 647 0
	movl	8(%ebp), %eax
	movl	$0, (%eax)
	.loc 2 648 0
	movl	8(%ebp), %eax
	movl	$0, 4(%eax)
.L147:
	.loc 2 650 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 651 0
	leave
	.cfi_restore 5
.LCFI47:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE16:
	.size	myblob_destroy, .-myblob_destroy
	.globl	myblob_set_filter
	.type	myblob_set_filter, @function
myblob_set_filter:
.LFB17:
	.loc 2 653 0
	.cfi_startproc
	pushl	%ebp
.LCFI48:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI49:
	.cfi_def_cfa_register 5
	.loc 2 654 0
	movl	12(%ebp), %eax
	cmpl	$2, %eax
	je	.L151
	cmpl	$2, %eax
	ja	.L154
	cmpl	$1, %eax
	je	.L150
	jmp	.L148
.L154:
	cmpl	$4, %eax
	je	.L152
	cmpl	$8, %eax
	je	.L153
	jmp	.L148
.L150:
	.loc 2 655 0
	movl	8(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 8(%eax)
	.loc 2 656 0
	jmp	.L148
.L151:
	.loc 2 657 0
	movl	8(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 12(%eax)
	.loc 2 658 0
	jmp	.L148
.L152:
	.loc 2 659 0
	movl	8(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 16(%eax)
	.loc 2 660 0
	jmp	.L148
.L153:
	.loc 2 661 0
	movl	8(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 20(%eax)
	.loc 2 662 0
	nop
.L148:
	.loc 2 664 0
	popl	%ebp
.LCFI50:
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE17:
	.size	myblob_set_filter, .-myblob_set_filter
	.globl	myblob_find_blobs
	.type	myblob_find_blobs, @function
myblob_find_blobs:
.LFB18:
	.loc 2 666 0
	.cfi_startproc
	pushl	%ebp
.LCFI51:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI52:
	.cfi_def_cfa_register 5
	subl	$72, %esp
	movl	40(%ebp), %eax
	movb	%al, -12(%ebp)
	.loc 2 668 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	.L156
	.loc 2 669 0
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	free
	.loc 2 670 0
	movl	8(%ebp), %eax
	movl	$0, (%eax)
	.loc 2 671 0
	movl	8(%ebp), %eax
	movl	$0, 4(%eax)
.L156:
	.loc 2 674 0
	movl	8(%ebp), %eax
	leal	4(%eax), %edx
	movzbl	-12(%ebp), %eax
	movl	%edx, 32(%esp)
	movl	%eax, 28(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	28(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	32(%ebp), %eax
	movl	%eax, 20(%esp)
	movl	36(%ebp), %eax
	movl	%eax, 24(%esp)
	movl	20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	find_connection_components_with_roi
	movl	8(%ebp), %edx
	movl	%eax, (%edx)
	.loc 2 675 0
	leave
	.cfi_restore 5
.LCFI53:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE18:
	.size	myblob_find_blobs, .-myblob_find_blobs
	.globl	myblob_first
	.type	myblob_first, @function
myblob_first:
.LFB19:
	.loc 2 677 0
	.cfi_startproc
	pushl	%ebp
.LCFI54:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI55:
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 2 678 0
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 2 679 0
	movl	8(%ebp), %eax
	movl	$-1, 28(%eax)
	.loc 2 680 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	myblob_next
	.loc 2 681 0
	leave
	.cfi_restore 5
.LCFI56:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE19:
	.size	myblob_first, .-myblob_first
	.globl	myblob_next
	.type	myblob_next, @function
myblob_next:
.LFB20:
	.loc 2 683 0
	.cfi_startproc
	pushl	%ebp
.LCFI57:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI58:
	.cfi_def_cfa_register 5
	.loc 2 685 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	.L159
	.loc 2 686 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	8(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 2 687 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	jmp	.L160
.L159:
	.loc 2 688 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L161
	.loc 2 689 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	jmp	.L160
.L161:
	.loc 2 691 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 2 692 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
.L160:
	.loc 2 697 0
	movl	8(%ebp), %eax
	movl	28(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	%eax, %edx
	jl	.L162
	.loc 2 698 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	40(%eax), %edx
	movl	8(%ebp), %eax
	movl	20(%eax), %eax
	cmpl	%eax, %edx
	jle	.L163
.L162:
	.loc 2 699 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	.L164
	.loc 2 700 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	8(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 2 701 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 2 702 0
	jmp	.L165
.L164:
	.loc 2 704 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L166
	.loc 2 705 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 2 706 0
	jmp	.L165
.L166:
	.loc 2 708 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 2 709 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 2 710 0
	jmp	.L165
.L163:
	.loc 2 712 0
	movl	8(%ebp), %eax
	movl	28(%eax), %edx
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	%eax, %edx
	jle	.L167
	.loc 2 713 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 2 714 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 2 715 0
	jmp	.L165
.L167:
	.loc 2 717 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	40(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	%eax, %edx
	jge	.L168
	.loc 2 718 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	.L169
	.loc 2 719 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 2 720 0
	jmp	.L165
.L169:
	.loc 2 722 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 24(%eax)
	.loc 2 723 0
	movl	8(%ebp), %eax
	movl	28(%eax), %eax
	leal	-1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, 28(%eax)
	.loc 2 724 0
	jmp	.L165
.L168:
	.loc 2 727 0
	movl	8(%ebp), %eax
	movl	24(%eax), %eax
	jmp	.L170
.L165:
	.loc 2 729 0
	movl	8(%ebp), %eax
	movl	24(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jne	.L160
	.loc 2 731 0
	movl	$0, %eax
.L170:
	.loc 2 732 0
	popl	%ebp
.LCFI59:
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE20:
	.size	myblob_next, .-myblob_next
.Letext0:
	.file 3 "/usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h"
	.file 4 "/usr/include/i386-linux-gnu/bits/types.h"
	.file 5 "/usr/include/libio.h"
	.file 6 "myblob.h"
	.file 7 "/usr/include/stdio.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xd53
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF126
	.byte	0x1
	.long	.LASF127
	.long	.LASF128
	.long	.Ltext0
	.long	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0xd4
	.long	0x30
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF0
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.byte	0x4
	.long	0x37
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.long	.LASF1
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF2
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF3
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF4
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF5
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF8
	.uleb128 0x2
	.long	.LASF10
	.byte	0x4
	.byte	0x38
	.long	0x4b
	.uleb128 0x2
	.long	.LASF11
	.byte	0x4
	.byte	0x8d
	.long	0x44
	.uleb128 0x2
	.long	.LASF12
	.byte	0x4
	.byte	0x8e
	.long	0x7c
	.uleb128 0x6
	.byte	0x4
	.uleb128 0x5
	.byte	0x4
	.long	0xa5
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF13
	.uleb128 0x7
	.long	.LASF43
	.byte	0x94
	.byte	0x5
	.value	0x111
	.long	0x26d
	.uleb128 0x8
	.long	.LASF14
	.byte	0x5
	.value	0x112
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.long	.LASF15
	.byte	0x5
	.value	0x117
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF16
	.byte	0x5
	.value	0x118
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.long	.LASF17
	.byte	0x5
	.value	0x119
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x8
	.long	.LASF18
	.byte	0x5
	.value	0x11a
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x8
	.long	.LASF19
	.byte	0x5
	.value	0x11b
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x8
	.long	.LASF20
	.byte	0x5
	.value	0x11c
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.long	.LASF21
	.byte	0x5
	.value	0x11d
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x8
	.long	.LASF22
	.byte	0x5
	.value	0x11e
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x8
	.long	.LASF23
	.byte	0x5
	.value	0x120
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x8
	.long	.LASF24
	.byte	0x5
	.value	0x121
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.long	.LASF25
	.byte	0x5
	.value	0x122
	.long	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x8
	.long	.LASF26
	.byte	0x5
	.value	0x124
	.long	0x2ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x8
	.long	.LASF27
	.byte	0x5
	.value	0x126
	.long	0x2b1
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0x8
	.long	.LASF28
	.byte	0x5
	.value	0x128
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x8
	.long	.LASF29
	.byte	0x5
	.value	0x12c
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x8
	.long	.LASF30
	.byte	0x5
	.value	0x12e
	.long	0x87
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x8
	.long	.LASF31
	.byte	0x5
	.value	0x132
	.long	0x59
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0x8
	.long	.LASF32
	.byte	0x5
	.value	0x133
	.long	0x67
	.byte	0x2
	.byte	0x23
	.uleb128 0x46
	.uleb128 0x8
	.long	.LASF33
	.byte	0x5
	.value	0x134
	.long	0x2b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x47
	.uleb128 0x8
	.long	.LASF34
	.byte	0x5
	.value	0x138
	.long	0x2c7
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x8
	.long	.LASF35
	.byte	0x5
	.value	0x141
	.long	0x92
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0x8
	.long	.LASF36
	.byte	0x5
	.value	0x14a
	.long	0x9d
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0x8
	.long	.LASF37
	.byte	0x5
	.value	0x14b
	.long	0x9d
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x8
	.long	.LASF38
	.byte	0x5
	.value	0x14c
	.long	0x9d
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0x8
	.long	.LASF39
	.byte	0x5
	.value	0x14d
	.long	0x9d
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0x8
	.long	.LASF40
	.byte	0x5
	.value	0x14e
	.long	0x25
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0x8
	.long	.LASF41
	.byte	0x5
	.value	0x150
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0x8
	.long	.LASF42
	.byte	0x5
	.value	0x152
	.long	0x2cd
	.byte	0x2
	.byte	0x23
	.uleb128 0x6c
	.byte	0
	.uleb128 0x9
	.long	.LASF129
	.byte	0x5
	.byte	0xb6
	.uleb128 0xa
	.long	.LASF44
	.byte	0xc
	.byte	0x5
	.byte	0xbc
	.long	0x2ab
	.uleb128 0xb
	.long	.LASF45
	.byte	0x5
	.byte	0xbd
	.long	0x2ab
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.long	.LASF46
	.byte	0x5
	.byte	0xbe
	.long	0x2b1
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.long	.LASF47
	.byte	0x5
	.byte	0xc2
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x274
	.uleb128 0x5
	.byte	0x4
	.long	0xac
	.uleb128 0xc
	.long	0xa5
	.long	0x2c7
	.uleb128 0xd
	.long	0x30
	.byte	0
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x26d
	.uleb128 0xc
	.long	0xa5
	.long	0x2dd
	.uleb128 0xd
	.long	0x30
	.byte	0x27
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x2e3
	.uleb128 0xe
	.long	0x37
	.uleb128 0xf
	.byte	0x10
	.byte	0x1
	.byte	0x8
	.long	0x325
	.uleb128 0x10
	.string	"x"
	.byte	0x1
	.byte	0x9
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x10
	.string	"y"
	.byte	0x1
	.byte	0x9
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.long	.LASF48
	.byte	0x1
	.byte	0x9
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.long	.LASF49
	.byte	0x1
	.byte	0x9
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0x2
	.long	.LASF50
	.byte	0x1
	.byte	0xa
	.long	0x2e8
	.uleb128 0xa
	.long	.LASF51
	.byte	0x18
	.byte	0x1
	.byte	0xd
	.long	0x366
	.uleb128 0x10
	.string	"id"
	.byte	0x1
	.byte	0xe
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x10
	.string	"roi"
	.byte	0x1
	.byte	0xf
	.long	0x325
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.long	.LASF52
	.byte	0x1
	.byte	0x12
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.byte	0
	.uleb128 0x2
	.long	.LASF51
	.byte	0x1
	.byte	0x13
	.long	0x330
	.uleb128 0x2
	.long	.LASF53
	.byte	0x1
	.byte	0x16
	.long	0x37c
	.uleb128 0xa
	.long	.LASF53
	.byte	0x2c
	.byte	0x1
	.byte	0x17
	.long	0x3dd
	.uleb128 0xb
	.long	.LASF54
	.byte	0x1
	.byte	0x18
	.long	0x3dd
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.long	.LASF55
	.byte	0x1
	.byte	0x19
	.long	0x3dd
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.long	.LASF56
	.byte	0x1
	.byte	0x1a
	.long	0x3dd
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.long	.LASF49
	.byte	0x1
	.byte	0x1b
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xb
	.long	.LASF48
	.byte	0x1
	.byte	0x1c
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xb
	.long	.LASF57
	.byte	0x1
	.byte	0x1d
	.long	0x366
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x371
	.uleb128 0x11
	.byte	0x4
	.byte	0x6
	.byte	0x2e
	.long	0x404
	.uleb128 0x12
	.long	.LASF58
	.sleb128 1
	.uleb128 0x12
	.long	.LASF59
	.sleb128 2
	.uleb128 0x12
	.long	.LASF60
	.sleb128 4
	.uleb128 0x12
	.long	.LASF61
	.sleb128 8
	.byte	0
	.uleb128 0x2
	.long	.LASF62
	.byte	0x6
	.byte	0x2e
	.long	0x3e3
	.uleb128 0xf
	.byte	0x10
	.byte	0x6
	.byte	0x30
	.long	0x450
	.uleb128 0xb
	.long	.LASF63
	.byte	0x6
	.byte	0x31
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.long	.LASF64
	.byte	0x6
	.byte	0x32
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.long	.LASF65
	.byte	0x6
	.byte	0x33
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.long	.LASF66
	.byte	0x6
	.byte	0x34
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0x2
	.long	.LASF67
	.byte	0x6
	.byte	0x35
	.long	0x40f
	.uleb128 0xf
	.byte	0x20
	.byte	0x6
	.byte	0x37
	.long	0x4a9
	.uleb128 0xb
	.long	.LASF68
	.byte	0x6
	.byte	0x38
	.long	0x3dd
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.long	.LASF69
	.byte	0x6
	.byte	0x39
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.long	.LASF70
	.byte	0x6
	.byte	0x3a
	.long	0x450
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x10
	.string	"it"
	.byte	0x6
	.byte	0x3b
	.long	0x3dd
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xb
	.long	.LASF71
	.byte	0x6
	.byte	0x3c
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.byte	0
	.uleb128 0x2
	.long	.LASF72
	.byte	0x6
	.byte	0x3d
	.long	0x45b
	.uleb128 0x13
	.long	.LASF76
	.byte	0x1
	.byte	0x23
	.byte	0x1
	.long	.LFB0
	.long	.LFE0
	.long	.LLST0
	.long	0x50f
	.uleb128 0x14
	.long	.LASF73
	.byte	0x1
	.byte	0x23
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x14
	.long	.LASF74
	.byte	0x1
	.byte	0x23
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x14
	.long	.LASF75
	.byte	0x1
	.byte	0x23
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x15
	.long	.LBB2
	.long	.LBE2
	.uleb128 0x16
	.long	.LASF78
	.byte	0x1
	.byte	0x26
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x13
	.long	.LASF77
	.byte	0x1
	.byte	0x30
	.byte	0x1
	.long	.LFB1
	.long	.LFE1
	.long	.LLST1
	.long	0x574
	.uleb128 0x14
	.long	.LASF54
	.byte	0x1
	.byte	0x30
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x14
	.long	.LASF56
	.byte	0x1
	.byte	0x30
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x17
	.string	"p"
	.byte	0x1
	.byte	0x3f
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x17
	.string	"c"
	.byte	0x1
	.byte	0x3f
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x15
	.long	.LBB3
	.long	.LBE3
	.uleb128 0x17
	.string	"cur"
	.byte	0x1
	.byte	0x34
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x18
	.long	.LASF82
	.byte	0x1
	.byte	0x47
	.byte	0x1
	.long	0x37
	.long	.LFB2
	.long	.LFE2
	.long	.LLST2
	.long	0x5b9
	.uleb128 0x14
	.long	.LASF73
	.byte	0x1
	.byte	0x47
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x17
	.string	"n"
	.byte	0x1
	.byte	0x48
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.uleb128 0x17
	.string	"cur"
	.byte	0x1
	.byte	0x49
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x13
	.long	.LASF79
	.byte	0x1
	.byte	0x58
	.byte	0x1
	.long	.LFB3
	.long	.LFE3
	.long	.LLST3
	.long	0x608
	.uleb128 0x14
	.long	.LASF73
	.byte	0x1
	.byte	0x58
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x14
	.long	.LASF80
	.byte	0x1
	.byte	0x58
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x17
	.string	"i"
	.byte	0x1
	.byte	0x59
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x16
	.long	.LASF81
	.byte	0x1
	.byte	0x5a
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x19
	.string	"cmp"
	.byte	0x1
	.byte	0x8d
	.byte	0x1
	.long	0x37
	.long	.LFB5
	.long	.LFE5
	.long	.LLST4
	.long	0x665
	.uleb128 0x1a
	.string	"a"
	.byte	0x1
	.byte	0x8d
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1a
	.string	"b"
	.byte	0x1
	.byte	0x8d
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x17
	.string	"ret"
	.byte	0x1
	.byte	0x97
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x17
	.string	"ca"
	.byte	0x1
	.byte	0x98
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x17
	.string	"cb"
	.byte	0x1
	.byte	0x99
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x13
	.long	.LASF83
	.byte	0x1
	.byte	0xa2
	.byte	0x1
	.long	.LFB6
	.long	.LFE6
	.long	.LLST5
	.long	0x6a4
	.uleb128 0x1a
	.string	"a"
	.byte	0x1
	.byte	0xa2
	.long	0x6a4
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1a
	.string	"b"
	.byte	0x1
	.byte	0xa2
	.long	0x6a4
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x17
	.string	"tmp"
	.byte	0x1
	.byte	0xa4
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x3dd
	.uleb128 0x13
	.long	.LASF84
	.byte	0x1
	.byte	0xa9
	.byte	0x1
	.long	.LFB7
	.long	.LFE7
	.long	.LLST6
	.long	0x6fb
	.uleb128 0x14
	.long	.LASF85
	.byte	0x1
	.byte	0xa9
	.long	0x6a4
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1a
	.string	"end"
	.byte	0x1
	.byte	0xa9
	.long	0x6a4
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x17
	.string	"ptr"
	.byte	0x1
	.byte	0xab
	.long	0x6a4
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x16
	.long	.LASF86
	.byte	0x1
	.byte	0xac
	.long	0x6a4
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x13
	.long	.LASF87
	.byte	0x1
	.byte	0xc6
	.byte	0x1
	.long	.LFB8
	.long	.LFE8
	.long	.LLST7
	.long	0x762
	.uleb128 0x14
	.long	.LASF73
	.byte	0x1
	.byte	0xc6
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x16
	.long	.LASF88
	.byte	0x1
	.byte	0xc9
	.long	0x6a4
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x16
	.long	.LASF89
	.byte	0x1
	.byte	0xca
	.long	0x6a4
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x17
	.string	"c"
	.byte	0x1
	.byte	0xcb
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x15
	.long	.LBB4
	.long	.LBE4
	.uleb128 0x17
	.string	"end"
	.byte	0x1
	.byte	0xd4
	.long	0x6a4
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x13
	.long	.LASF90
	.byte	0x1
	.byte	0xee
	.byte	0x1
	.long	.LFB9
	.long	.LFE9
	.long	.LLST8
	.long	0x7a2
	.uleb128 0x14
	.long	.LASF73
	.byte	0x1
	.byte	0xee
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1a
	.string	"id"
	.byte	0x1
	.byte	0xee
	.long	0x7a2
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1a
	.string	"d"
	.byte	0x1
	.byte	0xee
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x3e
	.uleb128 0x1b
	.long	.LASF91
	.byte	0x1
	.value	0x104
	.byte	0x1
	.long	.LFB10
	.long	.LFE10
	.long	.LLST9
	.long	0x7fd
	.uleb128 0x1c
	.long	.LASF73
	.byte	0x1
	.value	0x104
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1d
	.string	"id"
	.byte	0x1
	.value	0x104
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1c
	.long	.LASF92
	.byte	0x1
	.value	0x104
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x1e
	.long	.LASF93
	.byte	0x1
	.value	0x105
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x1f
	.long	.LASF94
	.byte	0x1
	.value	0x117
	.byte	0x1
	.long	0x37
	.long	.LFB11
	.long	.LFE11
	.long	.LLST10
	.long	0x82a
	.uleb128 0x1c
	.long	.LASF73
	.byte	0x1
	.value	0x117
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x18
	.long	.LASF95
	.byte	0x2
	.byte	0x2c
	.byte	0x1
	.long	0x37
	.long	.LFB12
	.long	.LFE12
	.long	.LLST11
	.long	0x871
	.uleb128 0x14
	.long	.LASF73
	.byte	0x2
	.byte	0x2c
	.long	0x871
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x14
	.long	.LASF96
	.byte	0x2
	.byte	0x2c
	.long	0x2dd
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x17
	.string	"val"
	.byte	0x2
	.byte	0x2d
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x877
	.uleb128 0xe
	.long	0x371
	.uleb128 0x18
	.long	.LASF97
	.byte	0x2
	.byte	0x34
	.byte	0x1
	.long	0x3dd
	.long	.LFB13
	.long	.LFE13
	.long	.LLST12
	.long	0x8e9
	.uleb128 0x14
	.long	.LASF57
	.byte	0x2
	.byte	0x35
	.long	0x8e9
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1a
	.string	"w"
	.byte	0x2
	.byte	0x36
	.long	0x2e3
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1a
	.string	"h"
	.byte	0x2
	.byte	0x36
	.long	0x2e3
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x14
	.long	.LASF98
	.byte	0x2
	.byte	0x37
	.long	0x8ef
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x14
	.long	.LASF69
	.byte	0x2
	.byte	0x38
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x17
	.string	"roi"
	.byte	0x2
	.byte	0x3a
	.long	0x8f4
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x8ef
	.uleb128 0xe
	.long	0x52
	.uleb128 0xe
	.long	0x325
	.uleb128 0x18
	.long	.LASF99
	.byte	0x2
	.byte	0x3f
	.byte	0x1
	.long	0x3dd
	.long	.LFB14
	.long	.LFE14
	.long	.LLST13
	.long	0xb84
	.uleb128 0x14
	.long	.LASF57
	.byte	0x2
	.byte	0x40
	.long	0x8e9
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1a
	.string	"w"
	.byte	0x2
	.byte	0x41
	.long	0x2e3
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1a
	.string	"h"
	.byte	0x2
	.byte	0x41
	.long	0x2e3
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x1a
	.string	"roi"
	.byte	0x2
	.byte	0x42
	.long	0x8f4
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x14
	.long	.LASF98
	.byte	0x2
	.byte	0x43
	.long	0x8ef
	.byte	0x3
	.byte	0x91
	.sleb128 -180
	.uleb128 0x14
	.long	.LASF69
	.byte	0x2
	.byte	0x44
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 32
	.uleb128 0x17
	.string	"r"
	.byte	0x2
	.byte	0x47
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0x17
	.string	"b"
	.byte	0x2
	.byte	0x48
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -92
	.uleb128 0x17
	.string	"id"
	.byte	0x2
	.byte	0x4f
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -176
	.uleb128 0x17
	.string	"a1"
	.byte	0x2
	.byte	0x50
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0x17
	.string	"a2"
	.byte	0x2
	.byte	0x50
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x17
	.string	"k"
	.byte	0x2
	.byte	0x51
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -172
	.uleb128 0x16
	.long	.LASF100
	.byte	0x2
	.byte	0x52
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -168
	.uleb128 0x17
	.string	"ids"
	.byte	0x2
	.byte	0x54
	.long	0x3e
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x16
	.long	.LASF101
	.byte	0x2
	.byte	0x56
	.long	0x3e
	.byte	0x3
	.byte	0x91
	.sleb128 -164
	.uleb128 0x16
	.long	.LASF96
	.byte	0x2
	.byte	0x57
	.long	0x3e
	.byte	0x3
	.byte	0x91
	.sleb128 -160
	.uleb128 0x16
	.long	.LASF102
	.byte	0x2
	.byte	0x58
	.long	0x3e
	.byte	0x3
	.byte	0x91
	.sleb128 -156
	.uleb128 0x16
	.long	.LASF103
	.byte	0x2
	.byte	0x5c
	.long	0x3e
	.byte	0x3
	.byte	0x91
	.sleb128 -152
	.uleb128 0x16
	.long	.LASF104
	.byte	0x2
	.byte	0x5d
	.long	0x3e
	.byte	0x3
	.byte	0x91
	.sleb128 -148
	.uleb128 0x16
	.long	.LASF105
	.byte	0x2
	.byte	0x5e
	.long	0x3e
	.byte	0x3
	.byte	0x91
	.sleb128 -144
	.uleb128 0x17
	.string	"s"
	.byte	0x2
	.byte	0x5f
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -140
	.uleb128 0x17
	.string	"z"
	.byte	0x2
	.byte	0x5f
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -136
	.uleb128 0x17
	.string	"dS"
	.byte	0x2
	.byte	0x62
	.long	0x8e9
	.byte	0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0x17
	.string	"dR"
	.byte	0x2
	.byte	0x63
	.long	0xb84
	.byte	0x3
	.byte	0x91
	.sleb128 -132
	.uleb128 0x17
	.string	"dE"
	.byte	0x2
	.byte	0x65
	.long	0x8e9
	.byte	0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x17
	.string	"dPi"
	.byte	0x2
	.byte	0x68
	.long	0xb84
	.byte	0x3
	.byte	0x91
	.sleb128 -128
	.uleb128 0x17
	.string	"iPi"
	.byte	0x2
	.byte	0x69
	.long	0x3e
	.byte	0x3
	.byte	0x91
	.sleb128 -124
	.uleb128 0x1e
	.long	.LASF106
	.byte	0x2
	.value	0x1f9
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x1e
	.long	.LASF107
	.byte	0x2
	.value	0x1fa
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -120
	.uleb128 0x1e
	.long	.LASF108
	.byte	0x2
	.value	0x1fa
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -116
	.uleb128 0x1e
	.long	.LASF109
	.byte	0x2
	.value	0x1fa
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x20
	.string	"l"
	.byte	0x2
	.value	0x1fa
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -108
	.uleb128 0x1e
	.long	.LASF110
	.byte	0x2
	.value	0x1fb
	.long	0x37
	.byte	0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x1e
	.long	.LASF111
	.byte	0x2
	.value	0x1fc
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1e
	.long	.LASF112
	.byte	0x2
	.value	0x1fd
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x1e
	.long	.LASF113
	.byte	0x2
	.value	0x228
	.long	0x3e
	.byte	0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1e
	.long	.LASF68
	.byte	0x2
	.value	0x22a
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x1e
	.long	.LASF73
	.byte	0x2
	.value	0x22e
	.long	0x3dd
	.byte	0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x20
	.string	"cur"
	.byte	0x2
	.value	0x22f
	.long	0x3dd
	.byte	0x3
	.byte	0x91
	.sleb128 -100
	.uleb128 0x1e
	.long	.LASF114
	.byte	0x2
	.value	0x230
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x21
	.long	.LASF130
	.byte	0x2
	.value	0x230
	.long	0x37
	.uleb128 0x20
	.string	"end"
	.byte	0x2
	.value	0x231
	.long	0x37
	.byte	0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x1e
	.long	.LASF115
	.byte	0x2
	.value	0x233
	.long	0xb8a
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x52
	.uleb128 0x5
	.byte	0x4
	.long	0x325
	.uleb128 0x22
	.byte	0x1
	.long	.LASF117
	.byte	0x2
	.value	0x27b
	.long	0xbcc
	.long	.LFB15
	.long	.LFE15
	.long	.LLST14
	.long	0xbcc
	.uleb128 0x1e
	.long	.LASF116
	.byte	0x2
	.value	0x27c
	.long	0xbcc
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1e
	.long	.LASF70
	.byte	0x2
	.value	0x27f
	.long	0x450
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x4a9
	.uleb128 0x23
	.byte	0x1
	.long	.LASF118
	.byte	0x2
	.value	0x284
	.byte	0x1
	.long	.LFB16
	.long	.LFE16
	.long	.LLST15
	.long	0xbfc
	.uleb128 0x1c
	.long	.LASF116
	.byte	0x2
	.value	0x284
	.long	0xbcc
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x23
	.byte	0x1
	.long	.LASF119
	.byte	0x2
	.value	0x28d
	.byte	0x1
	.long	.LFB17
	.long	.LFE17
	.long	.LLST16
	.long	0xc42
	.uleb128 0x1c
	.long	.LASF116
	.byte	0x2
	.value	0x28d
	.long	0xbcc
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1d
	.string	"f"
	.byte	0x2
	.value	0x28d
	.long	0xc42
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1d
	.string	"val"
	.byte	0x2
	.value	0x28d
	.long	0x2e3
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0xe
	.long	0x404
	.uleb128 0x23
	.byte	0x1
	.long	.LASF120
	.byte	0x2
	.value	0x29a
	.byte	0x1
	.long	.LFB18
	.long	.LFE18
	.long	.LLST17
	.long	0xcb8
	.uleb128 0x1c
	.long	.LASF116
	.byte	0x2
	.value	0x29a
	.long	0xbcc
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1c
	.long	.LASF57
	.byte	0x2
	.value	0x29a
	.long	0x8e9
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1d
	.string	"w"
	.byte	0x2
	.value	0x29a
	.long	0x2e3
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x1d
	.string	"h"
	.byte	0x2
	.value	0x29a
	.long	0x2e3
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x1d
	.string	"roi"
	.byte	0x2
	.value	0x29a
	.long	0x8f4
	.byte	0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x1c
	.long	.LASF98
	.byte	0x2
	.value	0x29a
	.long	0x8ef
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x24
	.byte	0x1
	.long	.LASF121
	.byte	0x2
	.value	0x2a5
	.byte	0x1
	.long	0x3dd
	.long	.LFB19
	.long	.LFE19
	.long	.LLST18
	.long	0xce6
	.uleb128 0x1c
	.long	.LASF116
	.byte	0x2
	.value	0x2a5
	.long	0xbcc
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x24
	.byte	0x1
	.long	.LASF122
	.byte	0x2
	.value	0x2ab
	.byte	0x1
	.long	0x3dd
	.long	.LFB20
	.long	.LFE20
	.long	.LLST19
	.long	0xd14
	.uleb128 0x1c
	.long	.LASF116
	.byte	0x2
	.value	0x2ab
	.long	0xbcc
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.long	.LASF123
	.byte	0x1
	.byte	0x20
	.long	0x37c
	.byte	0x5
	.byte	0x3
	.long	Leaf
	.uleb128 0x1e
	.long	.LASF124
	.byte	0x1
	.value	0x114
	.long	0x2e3
	.byte	0x5
	.byte	0x3
	.long	TREE_CHILDREN_MAX
	.uleb128 0x1e
	.long	.LASF125
	.byte	0x1
	.value	0x115
	.long	0x2e3
	.byte	0x5
	.byte	0x3
	.long	TREE_DEPTH_MAX
	.uleb128 0x25
	.long	.LASF131
	.byte	0x7
	.byte	0xab
	.long	0x2b1
	.byte	0x1
	.byte	0x1
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB0-.Ltext0
	.long	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI0-.Ltext0
	.long	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI1-.Ltext0
	.long	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI2-.Ltext0
	.long	.LFE0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST1:
	.long	.LFB1-.Ltext0
	.long	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI3-.Ltext0
	.long	.LCFI4-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI4-.Ltext0
	.long	.LCFI5-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI5-.Ltext0
	.long	.LFE1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST2:
	.long	.LFB2-.Ltext0
	.long	.LCFI6-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI6-.Ltext0
	.long	.LCFI7-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI7-.Ltext0
	.long	.LCFI8-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI8-.Ltext0
	.long	.LFE2-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST3:
	.long	.LFB3-.Ltext0
	.long	.LCFI9-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI9-.Ltext0
	.long	.LCFI10-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI10-.Ltext0
	.long	.LCFI11-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI11-.Ltext0
	.long	.LFE3-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST4:
	.long	.LFB5-.Ltext0
	.long	.LCFI12-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI12-.Ltext0
	.long	.LCFI13-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI13-.Ltext0
	.long	.LCFI14-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI14-.Ltext0
	.long	.LFE5-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST5:
	.long	.LFB6-.Ltext0
	.long	.LCFI15-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI15-.Ltext0
	.long	.LCFI16-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI16-.Ltext0
	.long	.LCFI17-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI17-.Ltext0
	.long	.LFE6-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST6:
	.long	.LFB7-.Ltext0
	.long	.LCFI18-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI18-.Ltext0
	.long	.LCFI19-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI19-.Ltext0
	.long	.LCFI20-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI20-.Ltext0
	.long	.LFE7-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST7:
	.long	.LFB8-.Ltext0
	.long	.LCFI21-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI21-.Ltext0
	.long	.LCFI22-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI22-.Ltext0
	.long	.LCFI23-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI23-.Ltext0
	.long	.LFE8-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST8:
	.long	.LFB9-.Ltext0
	.long	.LCFI24-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI24-.Ltext0
	.long	.LCFI25-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI25-.Ltext0
	.long	.LCFI26-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI26-.Ltext0
	.long	.LFE9-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST9:
	.long	.LFB10-.Ltext0
	.long	.LCFI27-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI27-.Ltext0
	.long	.LCFI28-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI28-.Ltext0
	.long	.LCFI29-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI29-.Ltext0
	.long	.LFE10-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST10:
	.long	.LFB11-.Ltext0
	.long	.LCFI30-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI30-.Ltext0
	.long	.LCFI31-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI31-.Ltext0
	.long	.LCFI32-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI32-.Ltext0
	.long	.LFE11-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST11:
	.long	.LFB12-.Ltext0
	.long	.LCFI33-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI33-.Ltext0
	.long	.LCFI34-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI34-.Ltext0
	.long	.LCFI35-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI35-.Ltext0
	.long	.LFE12-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST12:
	.long	.LFB13-.Ltext0
	.long	.LCFI36-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI36-.Ltext0
	.long	.LCFI37-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI37-.Ltext0
	.long	.LCFI38-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI38-.Ltext0
	.long	.LFE13-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST13:
	.long	.LFB14-.Ltext0
	.long	.LCFI39-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI39-.Ltext0
	.long	.LCFI40-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI40-.Ltext0
	.long	.LCFI41-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI41-.Ltext0
	.long	.LFE14-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST14:
	.long	.LFB15-.Ltext0
	.long	.LCFI42-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI42-.Ltext0
	.long	.LCFI43-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI43-.Ltext0
	.long	.LCFI44-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI44-.Ltext0
	.long	.LFE15-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST15:
	.long	.LFB16-.Ltext0
	.long	.LCFI45-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI45-.Ltext0
	.long	.LCFI46-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI46-.Ltext0
	.long	.LCFI47-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI47-.Ltext0
	.long	.LFE16-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST16:
	.long	.LFB17-.Ltext0
	.long	.LCFI48-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI48-.Ltext0
	.long	.LCFI49-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI49-.Ltext0
	.long	.LCFI50-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI50-.Ltext0
	.long	.LFE17-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST17:
	.long	.LFB18-.Ltext0
	.long	.LCFI51-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI51-.Ltext0
	.long	.LCFI52-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI52-.Ltext0
	.long	.LCFI53-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI53-.Ltext0
	.long	.LFE18-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST18:
	.long	.LFB19-.Ltext0
	.long	.LCFI54-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI54-.Ltext0
	.long	.LCFI55-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI55-.Ltext0
	.long	.LCFI56-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI56-.Ltext0
	.long	.LFE19-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST19:
	.long	.LFB20-.Ltext0
	.long	.LCFI57-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI57-.Ltext0
	.long	.LCFI58-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI58-.Ltext0
	.long	.LCFI59-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI59-.Ltext0
	.long	.LFE20-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF94:
	.string	"tree_hashval"
.LASF33:
	.string	"_shortbuf"
.LASF74:
	.string	"pheight"
.LASF129:
	.string	"_IO_lock_t"
.LASF105:
	.string	"bottom_index"
.LASF131:
	.string	"stderr"
.LASF22:
	.string	"_IO_buf_end"
.LASF55:
	.string	"silbing"
.LASF117:
	.string	"myblob_create"
.LASF107:
	.string	"tmp_id"
.LASF121:
	.string	"myblob_first"
.LASF20:
	.string	"_IO_write_end"
.LASF0:
	.string	"unsigned int"
.LASF89:
	.string	"next"
.LASF100:
	.string	"max_comp"
.LASF14:
	.string	"_flags"
.LASF103:
	.string	"left_index"
.LASF124:
	.string	"TREE_CHILDREN_MAX"
.LASF26:
	.string	"_markers"
.LASF110:
	.string	"found"
.LASF118:
	.string	"myblob_destroy"
.LASF69:
	.string	"tree_size"
.LASF127:
	.string	"myblob.c"
.LASF47:
	.string	"_pos"
.LASF62:
	.string	"FILTER"
.LASF25:
	.string	"_IO_save_end"
.LASF80:
	.string	"shift"
.LASF86:
	.string	"split"
.LASF108:
	.string	"tmp_id2"
.LASF101:
	.string	"anchors"
.LASF8:
	.string	"long long unsigned int"
.LASF82:
	.string	"number_of_nodes"
.LASF102:
	.string	"comp_same"
.LASF53:
	.string	"Node"
.LASF24:
	.string	"_IO_backup_base"
.LASF115:
	.string	"rect"
.LASF35:
	.string	"_offset"
.LASF56:
	.string	"child"
.LASF120:
	.string	"myblob_find_blobs"
.LASF28:
	.string	"_fileno"
.LASF93:
	.string	"last_height"
.LASF95:
	.string	"sum_areas"
.LASF9:
	.string	"size_t"
.LASF116:
	.string	"blob"
.LASF48:
	.string	"width"
.LASF68:
	.string	"tree"
.LASF67:
	.string	"Filter"
.LASF17:
	.string	"_IO_read_base"
.LASF71:
	.string	"it_depth"
.LASF130:
	.string	"parent_id"
.LASF106:
	.string	"nids"
.LASF45:
	.string	"_next"
.LASF111:
	.string	"real_ids"
.LASF78:
	.string	"height2"
.LASF61:
	.string	"F_AREA_MAX"
.LASF76:
	.string	"gen_redundant_information"
.LASF91:
	.string	"gen_tree_id"
.LASF13:
	.string	"char"
.LASF41:
	.string	"_mode"
.LASF44:
	.string	"_IO_marker"
.LASF15:
	.string	"_IO_read_ptr"
.LASF57:
	.string	"data"
.LASF58:
	.string	"F_DEPTH_MIN"
.LASF52:
	.string	"area"
.LASF50:
	.string	"MyBlobRect"
.LASF18:
	.string	"_IO_write_base"
.LASF2:
	.string	"long long int"
.LASF23:
	.string	"_IO_save_base"
.LASF90:
	.string	"_gen_tree_id"
.LASF119:
	.string	"myblob_set_filter"
.LASF128:
	.string	"/opt/kinect/MyBlobDetection"
.LASF64:
	.string	"max_depth"
.LASF113:
	.string	"tree_id_relation"
.LASF10:
	.string	"__quad_t"
.LASF92:
	.string	"size"
.LASF81:
	.string	"shift2"
.LASF36:
	.string	"__pad1"
.LASF37:
	.string	"__pad2"
.LASF38:
	.string	"__pad3"
.LASF39:
	.string	"__pad4"
.LASF40:
	.string	"__pad5"
.LASF66:
	.string	"max_area"
.LASF49:
	.string	"height"
.LASF122:
	.string	"myblob_next"
.LASF32:
	.string	"_vtable_offset"
.LASF109:
	.string	"real_ids_size"
.LASF97:
	.string	"find_connection_components"
.LASF73:
	.string	"root"
.LASF16:
	.string	"_IO_read_end"
.LASF54:
	.string	"parent"
.LASF84:
	.string	"quicksort_silbings"
.LASF7:
	.string	"short int"
.LASF1:
	.string	"long int"
.LASF114:
	.string	"anchor"
.LASF83:
	.string	"swap_pnode"
.LASF70:
	.string	"filter"
.LASF72:
	.string	"Myblob"
.LASF99:
	.string	"find_connection_components_with_roi"
.LASF75:
	.string	"psilbings"
.LASF77:
	.string	"add_child"
.LASF104:
	.string	"right_index"
.LASF34:
	.string	"_lock"
.LASF5:
	.string	"long unsigned int"
.LASF30:
	.string	"_old_offset"
.LASF43:
	.string	"_IO_FILE"
.LASF63:
	.string	"min_depth"
.LASF126:
	.string	"GNU C 4.6.3"
.LASF3:
	.string	"unsigned char"
.LASF125:
	.string	"TREE_DEPTH_MAX"
.LASF46:
	.string	"_sbuf"
.LASF19:
	.string	"_IO_write_ptr"
.LASF51:
	.string	"Blob"
.LASF60:
	.string	"F_AREA_MIN"
.LASF11:
	.string	"__off_t"
.LASF87:
	.string	"sort_tree"
.LASF6:
	.string	"signed char"
.LASF4:
	.string	"short unsigned int"
.LASF85:
	.string	"begin"
.LASF65:
	.string	"min_area"
.LASF123:
	.string	"Leaf"
.LASF88:
	.string	"children"
.LASF59:
	.string	"F_DEPTH_MAX"
.LASF27:
	.string	"_chain"
.LASF29:
	.string	"_flags2"
.LASF31:
	.string	"_cur_column"
.LASF96:
	.string	"comp_size"
.LASF12:
	.string	"__off64_t"
.LASF42:
	.string	"_unused2"
.LASF21:
	.string	"_IO_buf_base"
.LASF79:
	.string	"print_tree"
.LASF98:
	.string	"thresh"
.LASF112:
	.string	"real_ids_inv"
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
