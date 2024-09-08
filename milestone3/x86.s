		.section	.rodata
.LC0:
		.string	"%ld\n"
.LC1:
		.string	"%s\n"
.LC2:
		.string	"Grades:"
.LC3:
		.string	"Student ID:"
.LC4:
		.string	"Name:"
.LC5:
		.string	"S001"
.LC6:
		.string	"Alice Smith"
.LC7:
		.string	"S002"
.LC8:
		.string	"Bob Brown"
.LC9:
		.string	"S003"
.LC10:
		.string	"Carol Jones"
.LC11:
		.string	"S004"
.LC12:
		.string	"Dave Wilson"
.LC13:
		.string	"Highest Grade:"
.LC14:
		.string	"Lowest Grade:"
.LC15:
		.string	"__main__"
		.globl	main
		.text
		
# beginfunc Student.__init__
Student.__init__:
		pushq	%rbp
		movq	%rsp,	%rbp
		pushq	%rbx
		pushq	%rdi
		pushq	%rsi
		pushq	%r12
		pushq	%r13
		pushq	%r14
		pushq	%r15
		sub		$8,	%rsp
		
# *(self + 0) = student_id
		movq	16(%rbp),	%rdx
		addq	$0,	%rdx
		movq	24(%rbp),	%rcx
		movq	%rcx,	(%rdx)
		
# *(self + 8) = name
		movq	16(%rbp),	%rdx
		addq	$8,	%rdx
		movq	32(%rbp),	%rcx
		movq	%rcx,	(%rdx)
		
# *(self + 16) = grades
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	40(%rbp),	%rcx
		movq	%rcx,	(%rdx)
		
# endfunc__init__
		jmp		__init__.Student_.end
__init__.Student_.end:
		add		$8,	%rsp
		popq	%r15
		popq	%r14
		popq	%r13
		popq	%r12
		popq	%rsi
		popq	%rdi
		popq	%rbx
		popq	%rbp
		ret
		
# beginfunc Student.display_grades
Student.display_grades:
		pushq	%rbp
		movq	%rsp,	%rbp
		pushq	%rbx
		pushq	%rdi
		pushq	%rsi
		pushq	%r12
		pushq	%r13
		pushq	%r14
		pushq	%r15
		sub		$72,	%rsp
		
# #t0 = "Grades:"
		leaq	.LC2(%rip),	%rdx
		movq	%rdx,	-64(%rbp)
		
# print(#t0)
		movq	-64(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC1(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# i
		
# #t1 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16, %rdx
		movq	(%rdx),	%rcx
		movq	%rcx,	-80(%rbp)
		
# #t2 = len(#t1) = *(#t1)
		movq	-80(%rbp),	%rdx
		movq	(%rdx),	%rax
		cqto
		movq	$8,	%rbx
		idivq	%rbx
		subq	$1,	%rax
		movq	%rax,	-88(%rbp)
		
# leng = #t2
		movq	-88(%rbp),	%rdx
		movq	%rdx,	-96(%rbp)
		
# #t3= 0
		movq	$0,-104(%rbp)
		
# i = #t3
		movq	-104(%rbp),%rdx
		movq	%rdx,-72(%rbp)
		
# Goto .L1
		jmp		.L1
.L0:
		
# i += 1
		movq	-72(%rbp),	%rdx
		addq	$1,	%rdx
		movq	%rdx,-72(%rbp)
.L1:
		
# #t6= i<leng
		movq	-72(%rbp),	%rdx
		movq	-96(%rbp),	%rcx
		cmp		%rdx,	%rcx
		jg		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-112(%rbp)
		
# Ifz #t7 Goto .L2
		movq	-112(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L2
		
# #t8 = (i + 1) * 8
		movq	-72(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-120(%rbp)
		
# #t9 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t10 = *(#t9 + #t8)
		addq	-120(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-128(%rbp)
		
# print(#t10)
		movq	-128(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC0(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# Goto .L0
		jmp		.L0
.L2:
		
# endfuncdisplay_grades
		jmp		display_grades.Student_.end
display_grades.Student_.end:
		add		$72,	%rsp
		popq	%r15
		popq	%r14
		popq	%r13
		popq	%r12
		popq	%rsi
		popq	%rdi
		popq	%rbx
		popq	%rbp
		ret
		
# beginfunc Student.display_student
Student.display_student:
		pushq	%rbp
		movq	%rsp,	%rbp
		pushq	%rbx
		pushq	%rdi
		pushq	%rsi
		pushq	%r12
		pushq	%r13
		pushq	%r14
		pushq	%r15
		sub		$40,	%rsp
		
# #t11 = "Student ID:"
		leaq	.LC3(%rip),	%rdx
		movq	%rdx,	-64(%rbp)
		
# print(#t11)
		movq	-64(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC1(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# #t12 = *(self + 0)
		movq	16(%rbp),	%rdx
		addq	$0, %rdx
		movq	(%rdx),	%rcx
		movq	%rcx,	-72(%rbp)
		
# print(#t12)
		movq	-72(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC1(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# #t13 = "Name:"
		leaq	.LC4(%rip),	%rdx
		movq	%rdx,	-80(%rbp)
		
# print(#t13)
		movq	-80(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC1(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# #t14 = *(self + 8)
		movq	16(%rbp),	%rdx
		addq	$8, %rdx
		movq	(%rdx),	%rcx
		movq	%rcx,	-88(%rbp)
		
# print(#t14)
		movq	-88(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC1(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# funccall self
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# pushparam self
		movq	16(%rbp),	%rbx
		pushq	%rbx
		
# call Student.display_grades 1
		call	Student.display_grades
		add		$8,	%rsp
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		
# endfuncdisplay_student
		jmp		display_student.Student_.end
display_student.Student_.end:
		add		$40,	%rsp
		popq	%r15
		popq	%r14
		popq	%r13
		popq	%r12
		popq	%rsi
		popq	%rdi
		popq	%rbx
		popq	%rbp
		ret
		
# beginfunc Student.calculate_average
Student.calculate_average:
		pushq	%rbp
		movq	%rsp,	%rbp
		pushq	%rbx
		pushq	%rdi
		pushq	%rsi
		pushq	%r12
		pushq	%r13
		pushq	%r14
		pushq	%r15
		sub		$136,	%rsp
		
# #t15 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16, %rdx
		movq	(%rdx),	%rcx
		movq	%rcx,	-64(%rbp)
		
# #t16 = len(#t15) = *(#t15)
		movq	-64(%rbp),	%rdx
		movq	(%rdx),	%rax
		cqto
		movq	$8,	%rbx
		idivq	%rbx
		subq	$1,	%rax
		movq	%rax,	-72(%rbp)
		
# #t17 = 0
		movq	$0,	-80(%rbp)
		
# #t18 = #t16 == #t17
		movq	-72(%rbp),	%rdx
		movq	-80(%rbp),	%rcx
		cmp		%rdx,	%rcx
		je		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-88(%rbp)
		
# Ifz #t18 Goto .L3
		movq	-88(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L3
		
# #t19 = 0
		movq	$0,	-96(%rbp)
		
# %rax = #t19
		movq	-96(%rbp),	%rax
		
# endfunc
		jmp		calculate_average.Student_.end
		
# Goto .L4
		jmp		.L4
.L3:
.L4:
		
# #t20 = 0
		movq	$0,	-104(%rbp)
		
# total = #t20
		movq	-104(%rbp),	%rdx
		movq	%rdx,	-112(%rbp)
		
# i
		
# #t21 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16, %rdx
		movq	(%rdx),	%rcx
		movq	%rcx,	-128(%rbp)
		
# #t22 = len(#t21) = *(#t21)
		movq	-128(%rbp),	%rdx
		movq	(%rdx),	%rax
		cqto
		movq	$8,	%rbx
		idivq	%rbx
		subq	$1,	%rax
		movq	%rax,	-136(%rbp)
		
# leng = #t22
		movq	-136(%rbp),	%rdx
		movq	%rdx,	-144(%rbp)
		
# i = #t3
		movq	(%rbp),%rdx
		movq	%rdx,-120(%rbp)
		
# Goto .L6
		jmp		.L6
.L5:
		
# i += 1
		movq	-120(%rbp),	%rdx
		addq	$1,	%rdx
		movq	%rdx,-120(%rbp)
.L6:
		
# #t25= i<leng
		movq	-120(%rbp),	%rdx
		movq	-144(%rbp),	%rcx
		cmp		%rdx,	%rcx
		jg		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-160(%rbp)
		
# Ifz #t26 Goto .L7
		movq	-160(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L7
		
# #t27 = (i + 1) * 8
		movq	-120(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-168(%rbp)
		
# #t28 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t29 = *(#t28 + #t27)
		addq	-168(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-176(%rbp)
		
# total = #t29
		movq	-176(%rbp),	%rdx
		movq	-112(%rbp),	%rcx
		addq	%rcx,	%rdx
		movq	%rdx,	-112(%rbp)
		
# Goto .L5
		jmp		.L5
.L7:
		
# #t31 = total / leng
		movq	-112(%rbp),	%rax
		cqto
		movq	-144(%rbp),	%rbx
		idiv	%rbx
		movq	%rax,	%rdx
		movq	%rdx,	-184(%rbp)
		
# %rax = #t31
		movq	-184(%rbp),	%rax
		
# endfunc
		jmp		calculate_average.Student_.end
calculate_average.Student_.end:
		add		$136,	%rsp
		popq	%r15
		popq	%r14
		popq	%r13
		popq	%r12
		popq	%rsi
		popq	%rdi
		popq	%rbx
		popq	%rbp
		ret
		
# beginfunc Student.highest_grade
Student.highest_grade:
		pushq	%rbp
		movq	%rsp,	%rbp
		pushq	%rbx
		pushq	%rdi
		pushq	%rsi
		pushq	%r12
		pushq	%r13
		pushq	%r14
		pushq	%r15
		sub		$152,	%rsp
		
# i
		
# #t32 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16, %rdx
		movq	(%rdx),	%rcx
		movq	%rcx,	-72(%rbp)
		
# #t33 = len(#t32) = *(#t32)
		movq	-72(%rbp),	%rdx
		movq	(%rdx),	%rax
		cqto
		movq	$8,	%rbx
		idivq	%rbx
		subq	$1,	%rax
		movq	%rax,	-80(%rbp)
		
# leng = #t33
		movq	-80(%rbp),	%rdx
		movq	%rdx,	-88(%rbp)
		
# #t34 = 0
		movq	$0,	-96(%rbp)
		
# #t35 = (#t34 + 1) * 8
		movq	-96(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-104(%rbp)
		
# #t36 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t37 = *(#t36 + #t35)
		addq	-104(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-112(%rbp)
		
# highest = #t37
		movq	-112(%rbp),	%rdx
		movq	%rdx,	-120(%rbp)
		
# #t38= 0
		movq	$0,-128(%rbp)
		
# i = #t38
		movq	-128(%rbp),%rdx
		movq	%rdx,-64(%rbp)
		
# Goto .L9
		jmp		.L9
.L8:
		
# i += 1
		movq	-64(%rbp),	%rdx
		addq	$1,	%rdx
		movq	%rdx,-64(%rbp)
.L9:
		
# #t41= i<leng
		movq	-64(%rbp),	%rdx
		movq	-88(%rbp),	%rcx
		cmp		%rdx,	%rcx
		jg		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-136(%rbp)
		
# Ifz #t42 Goto .L10
		movq	-136(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L10
		
# #t43 = (i + 1) * 8
		movq	-64(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-144(%rbp)
		
# #t44 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t45 = *(#t44 + #t43)
		addq	-144(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-152(%rbp)
		
# #t46 = not #t45
		movq	-152(%rbp),	%rdx
		cmp		$0,	%rdx
		je		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-160(%rbp)
		
# Ifz #t46 Goto .L11
		movq	-160(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L11
		
# #t47 = 0
		movq	$0,	-168(%rbp)
		
# %rax = #t47
		movq	-168(%rbp),	%rax
		
# endfunc
		jmp		highest_grade.Student_.end
		
# Goto .L12
		jmp		.L12
.L11:
.L12:
		
# #t48 = (i + 1) * 8
		movq	-64(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-176(%rbp)
		
# #t49 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t50 = *(#t49 + #t48)
		addq	-176(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-184(%rbp)
		
# #t51 = #t50 > highest
		movq	-184(%rbp),	%rdx
		movq	-120(%rbp),	%rcx
		cmp		%rdx,	%rcx
		jl		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-192(%rbp)
		
# Ifz #t51 Goto .L13
		movq	-192(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L13
		
# #t52 = (i + 1) * 8
		movq	-64(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-200(%rbp)
		
# #t53 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t54 = *(#t53 + #t52)
		addq	-200(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-208(%rbp)
		
# highest = #t54
		movq	-208(%rbp),	%rdx
		movq	%rdx,	-120(%rbp)
		
# Goto .L14
		jmp		.L14
.L13:
.L14:
		
# Goto .L8
		jmp		.L8
.L10:
		
# %rax = highest
		movq	-120(%rbp),	%rax
		
# endfunc
		jmp		highest_grade.Student_.end
highest_grade.Student_.end:
		add		$152,	%rsp
		popq	%r15
		popq	%r14
		popq	%r13
		popq	%r12
		popq	%rsi
		popq	%rdi
		popq	%rbx
		popq	%rbp
		ret
		
# beginfunc Student.lowest_grade
Student.lowest_grade:
		pushq	%rbp
		movq	%rsp,	%rbp
		pushq	%rbx
		pushq	%rdi
		pushq	%rsi
		pushq	%r12
		pushq	%r13
		pushq	%r14
		pushq	%r15
		sub		$152,	%rsp
		
# #t55 = 0
		movq	$0,	-64(%rbp)
		
# #t56 = (#t55 + 1) * 8
		movq	-64(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-72(%rbp)
		
# #t57 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t58 = *(#t57 + #t56)
		addq	-72(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-80(%rbp)
		
# lowest = #t58
		movq	-80(%rbp),	%rdx
		movq	%rdx,	-88(%rbp)
		
# i
		
# #t59 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16, %rdx
		movq	(%rdx),	%rcx
		movq	%rcx,	-104(%rbp)
		
# #t60 = len(#t59) = *(#t59)
		movq	-104(%rbp),	%rdx
		movq	(%rdx),	%rax
		cqto
		movq	$8,	%rbx
		idivq	%rbx
		subq	$1,	%rax
		movq	%rax,	-112(%rbp)
		
# leng = #t60
		movq	-112(%rbp),	%rdx
		movq	%rdx,	-120(%rbp)
		
# #t61= 0
		movq	$0,-128(%rbp)
		
# i = #t61
		movq	-128(%rbp),%rdx
		movq	%rdx,-96(%rbp)
		
# Goto .L16
		jmp		.L16
.L15:
		
# i += 1
		movq	-96(%rbp),	%rdx
		addq	$1,	%rdx
		movq	%rdx,-96(%rbp)
.L16:
		
# #t64= i<leng
		movq	-96(%rbp),	%rdx
		movq	-120(%rbp),	%rcx
		cmp		%rdx,	%rcx
		jg		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-136(%rbp)
		
# Ifz #t65 Goto .L17
		movq	-136(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L17
		
# #t66 = (i + 1) * 8
		movq	-96(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-144(%rbp)
		
# #t67 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t68 = *(#t67 + #t66)
		addq	-144(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-152(%rbp)
		
# #t69 = not #t68
		movq	-152(%rbp),	%rdx
		cmp		$0,	%rdx
		je		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-160(%rbp)
		
# Ifz #t69 Goto .L18
		movq	-160(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L18
		
# #t70 = 0
		movq	$0,	-168(%rbp)
		
# %rax = #t70
		movq	-168(%rbp),	%rax
		
# endfunc
		jmp		lowest_grade.Student_.end
		
# Goto .L19
		jmp		.L19
.L18:
.L19:
		
# #t71 = (i + 1) * 8
		movq	-96(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-176(%rbp)
		
# #t72 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t73 = *(#t72 + #t71)
		addq	-176(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-184(%rbp)
		
# #t74 = #t73 < lowest
		movq	-184(%rbp),	%rdx
		movq	-88(%rbp),	%rcx
		cmp		%rdx,	%rcx
		jg		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-192(%rbp)
		
# Ifz #t74 Goto .L20
		movq	-192(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L20
		
# #t75 = (i + 1) * 8
		movq	-96(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-200(%rbp)
		
# #t76 = *(self + 16)
		movq	16(%rbp),	%rdx
		addq	$16,	%rdx
		movq	(%rdx),	%rcx
		
# #t77 = *(#t76 + #t75)
		addq	-200(%rbp),	%rcx
		movq	(%rcx),	%rdx
		movq	%rdx,	-208(%rbp)
		
# lowest = #t77
		movq	-208(%rbp),	%rdx
		movq	%rdx,	-88(%rbp)
		
# Goto .L21
		jmp		.L21
.L20:
.L21:
		
# Goto .L15
		jmp		.L15
.L17:
		
# %rax = lowest
		movq	-88(%rbp),	%rax
		
# endfunc
		jmp		lowest_grade.Student_.end
lowest_grade.Student_.end:
		add		$152,	%rsp
		popq	%r15
		popq	%r14
		popq	%r13
		popq	%r12
		popq	%rsi
		popq	%rdi
		popq	%rbx
		popq	%rbp
		ret
		
# beginfunc main
main:
		pushq	%rbp
		movq	%rsp,	%rbp
		pushq	%rbx
		pushq	%rdi
		pushq	%rsi
		pushq	%r12
		pushq	%r13
		pushq	%r14
		pushq	%r15
		sub		$488,	%rsp
		
# #t78 = "S001"
		leaq	.LC5(%rip),	%rdx
		movq	%rdx,	-64(%rbp)
		
# #t79 = "Alice Smith"
		leaq	.LC6(%rip),	%rdx
		movq	%rdx,	-72(%rbp)
		
# #t80 = 88
		movq	$88,	-80(%rbp)
		
# #t81 = 92
		movq	$92,	-88(%rbp)
		
# #t82 = 77
		movq	$77,	-96(%rbp)
		
# #t83 = 90
		movq	$90,	-104(%rbp)
		
# #t84 = 40
		movq	$40,	-112(%rbp)
		
# pushparam #t84
		movq	-112(%rbp),	%rdi
		call	malloc@PLT
		
# #t85 = %rax
		movq	%rax,	-120(%rbp)
		
# len of list  = #t84
		movq	-120(%rbp),	%rdx
		addq	$0,	%rdx
		movq	-112(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t85 + 8) = #t80
		movq	-120(%rbp),	%rdx
		addq	$8,	%rdx
		movq	-80(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t85 + 16) = #t81
		movq	-120(%rbp),	%rdx
		addq	$16,	%rdx
		movq	-88(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t85 + 24) = #t82
		movq	-120(%rbp),	%rdx
		addq	$24,	%rdx
		movq	-96(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t85 + 32) = #t83
		movq	-120(%rbp),	%rdx
		addq	$32,	%rdx
		movq	-104(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# #t86 = 24
		movq	$24,	-128(%rbp)
		
# call malloc 24
		movq	-128(%rbp),	%rdi
		call	malloc@PLT
		
# #t87 = %rax
		movq	%rax,	-136(%rbp)
		
# aligning stack
		pushq	$0
		
# funccall Student
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# pushparam #t85
		movq	-120(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t79
		movq	-72(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t78
		movq	-64(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t87
		movq	-136(%rbp),	%rbx
		pushq	%rbx
		
# call Student.__init__ 4
		call Student.__init__ 
		add		$32,	%rsp
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		add		$8,	%rsp
		
# student1 = #t87
		movq	-136(%rbp),	%rdx
		movq	%rdx,	-144(%rbp)
		
# #t88 = "S002"
		leaq	.LC7(%rip),	%rdx
		movq	%rdx,	-152(%rbp)
		
# #t89 = "Bob Brown"
		leaq	.LC8(%rip),	%rdx
		movq	%rdx,	-160(%rbp)
		
# #t90 = 84
		movq	$84,	-168(%rbp)
		
# #t91 = 76
		movq	$76,	-176(%rbp)
		
# #t92 = 88
		movq	$88,	-184(%rbp)
		
# #t93 = 85
		movq	$85,	-192(%rbp)
		
# #t94 = 40
		movq	$40,	-200(%rbp)
		
# pushparam #t94
		movq	-200(%rbp),	%rdi
		call	malloc@PLT
		
# #t95 = %rax
		movq	%rax,	-208(%rbp)
		
# len of list  = #t94
		movq	-208(%rbp),	%rdx
		addq	$0,	%rdx
		movq	-200(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t95 + 8) = #t90
		movq	-208(%rbp),	%rdx
		addq	$8,	%rdx
		movq	-168(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t95 + 16) = #t91
		movq	-208(%rbp),	%rdx
		addq	$16,	%rdx
		movq	-176(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t95 + 24) = #t92
		movq	-208(%rbp),	%rdx
		addq	$24,	%rdx
		movq	-184(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t95 + 32) = #t93
		movq	-208(%rbp),	%rdx
		addq	$32,	%rdx
		movq	-192(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# #t96 = 24
		movq	$24,	-216(%rbp)
		
# call malloc 24
		movq	-216(%rbp),	%rdi
		call	malloc@PLT
		
# #t97 = %rax
		movq	%rax,	-224(%rbp)
		
# aligning stack
		pushq	$0
		
# funccall Student
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# pushparam #t95
		movq	-208(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t89
		movq	-160(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t88
		movq	-152(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t97
		movq	-224(%rbp),	%rbx
		pushq	%rbx
		
# call Student.__init__ 4
		call Student.__init__ 
		add		$32,	%rsp
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		add		$8,	%rsp
		
# student2 = #t97
		movq	-224(%rbp),	%rdx
		movq	%rdx,	-232(%rbp)
		
# #t98 = "S003"
		leaq	.LC9(%rip),	%rdx
		movq	%rdx,	-240(%rbp)
		
# #t99 = "Carol Jones"
		leaq	.LC10(%rip),	%rdx
		movq	%rdx,	-248(%rbp)
		
# #t100 = 90
		movq	$90,	-256(%rbp)
		
# #t101 = 90
		movq	$90,	-264(%rbp)
		
# #t102 = 92
		movq	$92,	-272(%rbp)
		
# #t103 = 93
		movq	$93,	-280(%rbp)
		
# #t104 = 40
		movq	$40,	-288(%rbp)
		
# pushparam #t104
		movq	-288(%rbp),	%rdi
		call	malloc@PLT
		
# #t105 = %rax
		movq	%rax,	-296(%rbp)
		
# len of list  = #t104
		movq	-296(%rbp),	%rdx
		addq	$0,	%rdx
		movq	-288(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t105 + 8) = #t100
		movq	-296(%rbp),	%rdx
		addq	$8,	%rdx
		movq	-256(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t105 + 16) = #t101
		movq	-296(%rbp),	%rdx
		addq	$16,	%rdx
		movq	-264(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t105 + 24) = #t102
		movq	-296(%rbp),	%rdx
		addq	$24,	%rdx
		movq	-272(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t105 + 32) = #t103
		movq	-296(%rbp),	%rdx
		addq	$32,	%rdx
		movq	-280(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# #t106 = 24
		movq	$24,	-304(%rbp)
		
# call malloc 24
		movq	-304(%rbp),	%rdi
		call	malloc@PLT
		
# #t107 = %rax
		movq	%rax,	-312(%rbp)
		
# aligning stack
		pushq	$0
		
# funccall Student
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# pushparam #t105
		movq	-296(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t99
		movq	-248(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t98
		movq	-240(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t107
		movq	-312(%rbp),	%rbx
		pushq	%rbx
		
# call Student.__init__ 4
		call Student.__init__ 
		add		$32,	%rsp
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		add		$8,	%rsp
		
# student3 = #t107
		movq	-312(%rbp),	%rdx
		movq	%rdx,	-320(%rbp)
		
# #t108 = "S004"
		leaq	.LC11(%rip),	%rdx
		movq	%rdx,	-328(%rbp)
		
# #t109 = "Dave Wilson"
		leaq	.LC12(%rip),	%rdx
		movq	%rdx,	-336(%rbp)
		
# #t110 = 78
		movq	$78,	-344(%rbp)
		
# #t111 = 82
		movq	$82,	-352(%rbp)
		
# #t112 = 80
		movq	$80,	-360(%rbp)
		
# #t113 = 85
		movq	$85,	-368(%rbp)
		
# #t114 = 40
		movq	$40,	-376(%rbp)
		
# pushparam #t114
		movq	-376(%rbp),	%rdi
		call	malloc@PLT
		
# #t115 = %rax
		movq	%rax,	-384(%rbp)
		
# len of list  = #t114
		movq	-384(%rbp),	%rdx
		addq	$0,	%rdx
		movq	-376(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t115 + 8) = #t110
		movq	-384(%rbp),	%rdx
		addq	$8,	%rdx
		movq	-344(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t115 + 16) = #t111
		movq	-384(%rbp),	%rdx
		addq	$16,	%rdx
		movq	-352(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t115 + 24) = #t112
		movq	-384(%rbp),	%rdx
		addq	$24,	%rdx
		movq	-360(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t115 + 32) = #t113
		movq	-384(%rbp),	%rdx
		addq	$32,	%rdx
		movq	-368(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# #t116 = 24
		movq	$24,	-392(%rbp)
		
# call malloc 24
		movq	-392(%rbp),	%rdi
		call	malloc@PLT
		
# #t117 = %rax
		movq	%rax,	-400(%rbp)
		
# aligning stack
		pushq	$0
		
# funccall Student
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# pushparam #t115
		movq	-384(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t109
		movq	-336(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t108
		movq	-328(%rbp),	%rbx
		pushq	%rbx
		
# pushparam #t117
		movq	-400(%rbp),	%rbx
		pushq	%rbx
		
# call Student.__init__ 4
		call Student.__init__ 
		add		$32,	%rsp
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		add		$8,	%rsp
		
# student4 = #t117
		movq	-400(%rbp),	%rdx
		movq	%rdx,	-408(%rbp)
		
# #t118 = 40
		movq	$40,	-416(%rbp)
		
# pushparam #t118
		movq	-416(%rbp),	%rdi
		call	malloc@PLT
		
# #t119 = %rax
		movq	%rax,	-424(%rbp)
		
# len of list  = #t118
		movq	-424(%rbp),	%rdx
		addq	$0,	%rdx
		movq	-416(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t119 + 8) = student1
		movq	-424(%rbp),	%rdx
		addq	$8,	%rdx
		movq	-144(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t119 + 16) = student2
		movq	-424(%rbp),	%rdx
		addq	$16,	%rdx
		movq	-232(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t119 + 24) = student3
		movq	-424(%rbp),	%rdx
		addq	$24,	%rdx
		movq	-320(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# *(#t119 + 32) = student4
		movq	-424(%rbp),	%rdx
		addq	$32,	%rdx
		movq	-408(%rbp),	%rax
		movq	%rax,	(%rdx)
		
# list_of_students = #t119
		movq	-424(%rbp),	%rdx
		movq	%rdx,	-432(%rbp)
		
# #t120 = len(list_of_students) = *(list_of_students)
		movq	-432(%rbp),	%rdx
		movq	(%rdx),	%rax
		cqto
		movq	$8,	%rbx
		idivq	%rbx
		subq	$1,	%rax
		movq	%rax,	-440(%rbp)
		
# leng = #t120
		movq	-440(%rbp),	%rdx
		movq	%rdx,	-448(%rbp)
		
# i
		
# #t121= 0
		movq	$0,-464(%rbp)
		
# i = #t121
		movq	-464(%rbp),%rdx
		movq	%rdx,-456(%rbp)
		
# Goto .L23
		jmp		.L23
.L22:
		
# i += 1
		movq	-456(%rbp),	%rdx
		addq	$1,	%rdx
		movq	%rdx,-456(%rbp)
.L23:
		
# #t124= i<leng
		movq	-456(%rbp),	%rdx
		movq	-448(%rbp),	%rcx
		cmp		%rdx,	%rcx
		jg		1f
		movq	$0,	%rdx
		jmp		2f
1:
		movq	$1,	%rdx
2:
		movq	%rdx,	-472(%rbp)
		
# Ifz #t125 Goto .L24
		movq	-472(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L24
		
# #t126 = (i + 1) * 8
		movq	-456(%rbp),	%rdx
		addq	$1,	%rdx
		imulq	$8,	%rdx
		movq	%rdx,	-480(%rbp)
		
# #t127 = *(list_of_students + #t126)
		movq	-432(%rbp),	%rdx
		addq	-480(%rbp),	%rdx
		movq	(%rdx),	%rcx
		movq	%rcx,	-488(%rbp)
		
# temp_student = #t127
		movq	-488(%rbp),	%rdx
		movq	%rdx,	-496(%rbp)
		
# funccall temp_student
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# pushparam temp_student
		movq	-496(%rbp),	%rbx
		pushq	%rbx
		
# call Student.display_student 1
		call	Student.display_student
		add		$8,	%rsp
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		
# funccall temp_student.calculate_average
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# pushparam temp_student
		movq	-496(%rbp),	%rbx
		pushq	%rbx
		
# call Student.calculate_average 1
		call	Student.calculate_average
		add		$8,	%rsp
		
# #t128 = %rax
		movq	%rax,	-504(%rbp)
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		
# average = #t128
		movq	-504(%rbp),	%rdx
		movq	%rdx,	-512(%rbp)
		
# #t129 = "Highest Grade:"
		leaq	.LC13(%rip),	%rdx
		movq	%rdx,	-520(%rbp)
		
# print(#t129)
		movq	-520(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC1(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# funccall temp_student.highest_grade
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# pushparam temp_student
		movq	-496(%rbp),	%rbx
		pushq	%rbx
		
# call Student.highest_grade 1
		call	Student.highest_grade
		add		$8,	%rsp
		
# #t130 = %rax
		movq	%rax,	-528(%rbp)
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		
# print(#t130)
		movq	-528(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC0(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# #t131 = "Lowest Grade:"
		leaq	.LC14(%rip),	%rdx
		movq	%rdx,	-536(%rbp)
		
# print(#t131)
		movq	-536(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC1(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# funccall temp_student.lowest_grade
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# pushparam temp_student
		movq	-496(%rbp),	%rbx
		pushq	%rbx
		
# call Student.lowest_grade 1
		call	Student.lowest_grade
		add		$8,	%rsp
		
# #t132 = %rax
		movq	%rax,	-544(%rbp)
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		
# print(#t132)
		movq	-544(%rbp),	%rax
		movq	%rax,	%rsi
		leaq	.LC0(%rip),	%rax
		movq	%rax,	%rdi
		movq	$0,	%rax
		call	printf@PLT
		
# Goto .L22
		jmp		.L22
.L24:
		
# end main
		movq	$60,	%rax
		xor		%rdi,	%rdi
		syscall
		
# #t133 = "__main__"
		leaq	.LC15(%rip),	%rdx
		movq	%rdx,	-64(%rbp)
		
# #t134 = __name__ == #t133
		movq	(%rbp),	%rdx
		movq	-64(%rbp),	%rcx
		movq	%rdx,	%rdi
		movq	%rcx,	%rsi
		call	strcmp@PLT
		movsx	%eax,	%rax
		cmp		$0,	%rax
		jne		1f
		movq	$1,	%rdx
		jmp		2f
1:
		movq	$0,	%rdx
2:
		movq	%rdx,	-80(%rbp)
		
# Ifz #t134 Goto .L25
		movq	-80(%rbp),	%rdx
		cmp		$0,	%rdx
		je		.L25
		
# aligning stack
		pushq	$0
		
# funccall main
		pushq	%rax
		pushq	%rcx
		pushq	%rdx
		pushq	%r8
		pushq	%r9
		pushq	%r10
		pushq	%r11
		
# call main 0
		call	main
		add		$0,	%rsp
		popq	%r11
		popq	%r10
		popq	%r9
		popq	%r8
		popq	%rdx
		popq	%rcx
		popq	%rax
		add		$8,	%rsp
		
# Goto .L26
		jmp		.L26
.L25:
.L26:
