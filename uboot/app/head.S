
	.globl ReadPage512

ReadPage512:
	stmfd	sp!, {r2-r7}
	mov	r2, #0x200
1:
	ldr	r4, [r1]
	ldr	r5, [r1]
	ldr	r6, [r1]
	ldr	r7, [r1]
	stmia	r0!, {r4-r7}
	ldr	r4, [r1]
	ldr	r5, [r1]
	ldr	r6, [r1]
	ldr	r7, [r1]
	stmia	r0!, {r4-r7}
	ldr	r4, [r1]
	ldr	r5, [r1]
	ldr	r6, [r1]
	ldr	r7, [r1]
	stmia	r0!, {r4-r7}
	ldr	r4, [r1]
	ldr	r5, [r1]
	ldr	r6, [r1]
	ldr	r7, [r1]
	stmia	r0!, {r4-r7}
	subs	r2, r2, #64
	bne	1b;
	ldmfd	sp!, {r2-r7}
	mov	pc,lr
