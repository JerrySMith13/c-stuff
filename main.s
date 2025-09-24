	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 15, 5
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #192
	stp	x29, x30, [sp, #176]            ; 16-byte Folded Spill
	add	x29, sp, #176
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	wzr, [x29, #-4]
	stur	w0, [x29, #-8]
	stur	x1, [x29, #-16]
	ldur	w8, [x29, #-8]
	subs	w8, w8, #2
	b.eq	LBB0_2
	b	LBB0_1
LBB0_1:
	ldur	x8, [x29, #-16]
	ldr	x8, [x8]
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	stur	wzr, [x29, #-4]
	b	LBB0_5
LBB0_2:
	ldur	x8, [x29, #-16]
	ldr	x0, [x8, #8]
	mov	w1, #0                          ; =0x0
	bl	_open
	stur	w0, [x29, #-20]
	ldur	w0, [x29, #-20]
	add	x1, sp, #8
	bl	_fstat
	cbz	w0, LBB0_4
	b	LBB0_3
LBB0_3:
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	mov	w8, #-1                         ; =0xffffffff
	stur	w8, [x29, #-4]
	b	LBB0_5
LBB0_4:
	ldur	x8, [x29, #-16]
	ldr	x8, [x8, #8]
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	stur	wzr, [x29, #-4]
	b	LBB0_5
LBB0_5:
	ldur	w0, [x29, #-4]
	ldp	x29, x30, [sp, #176]            ; 16-byte Folded Reload
	add	sp, sp, #192
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Usage: %s <filepath>"

l_.str.1:                               ; @.str.1
	.asciz	"Error: File was unable to be opened"

l_.str.2:                               ; @.str.2
	.asciz	"Info for: %s\n"

.subsections_via_symbols
