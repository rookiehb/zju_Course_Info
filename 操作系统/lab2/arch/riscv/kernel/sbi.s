	.file	"sbi.c"
	.option nopic
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.sbi_ecall,"ax",@progbits
	.align	2
	.globl	sbi_ecall
	.type	sbi_ecall, @function
sbi_ecall:
.LFB0:
	.file 1 "sbi.c"
	.loc 1 9 0
	.cfi_startproc
	add	sp,sp,-112
	.cfi_def_cfa_offset 112
	sd	s0,104(sp)
	.cfi_offset 8, -8
	add	s0,sp,112
	.cfi_def_cfa 8, 0
	sd	a2,-64(s0)
	sd	a3,-72(s0)
	sd	a4,-80(s0)
	sd	a5,-88(s0)
	sd	a6,-96(s0)
	sd	a7,-104(s0)
	mv	a5,a0
	sw	a5,-52(s0)
	mv	a5,a1
	sw	a5,-56(s0)
	.loc 1 11 0
	ld	a0,-64(s0)
	.loc 1 12 0
	ld	a1,-72(s0)
	.loc 1 13 0
	ld	a2,-80(s0)
	.loc 1 14 0
	ld	a3,-88(s0)
	.loc 1 15 0
	ld	a4,-96(s0)
	.loc 1 16 0
	ld	a5,-104(s0)
	.loc 1 17 0
	lw	a6,-56(s0)
	.loc 1 18 0
	lw	a7,-52(s0)
	.loc 1 20 0
#APP
# 20 "sbi.c" 1
	ecall
# 0 "" 2
	.loc 1 25 0
#NO_APP
	mv	a5,a0
	sd	a5,-48(s0)
	.loc 1 26 0
	mv	a5,a1
	sd	a5,-40(s0)
	.loc 1 28 0
	ld	a5,-48(s0)
	sd	a5,-32(s0)
	ld	a5,-40(s0)
	sd	a5,-24(s0)
	li	a4,0
	ld	a4,-32(s0)
	li	a5,0
	ld	a5,-24(s0)
	mv	t1,a4
	mv	t2,a5
	mv	a5,t1
	mv	a6,t2
	.loc 1 47 0
	mv	a0,a5
	mv	a1,a6
	ld	s0,104(sp)
	.cfi_restore 8
	add	sp,sp,112
	.cfi_def_cfa_register 2
	jr	ra
	.cfi_endproc
.LFE0:
	.size	sbi_ecall, .-sbi_ecall
	.section	.text.sbi_putchar,"ax",@progbits
	.align	2
	.globl	sbi_putchar
	.type	sbi_putchar, @function
sbi_putchar:
.LFB1:
	.loc 1 49 0
	.cfi_startproc
	add	sp,sp,-32
	.cfi_def_cfa_offset 32
	sd	ra,24(sp)
	sd	s0,16(sp)
	.cfi_offset 1, -8
	.cfi_offset 8, -16
	add	s0,sp,32
	.cfi_def_cfa 8, 0
	mv	a5,a0
	sw	a5,-20(s0)
	.loc 1 50 0
	lwu	a2,-20(s0)
	li	a7,0
	li	a6,0
	li	a5,0
	li	a4,0
	li	a3,0
	li	a1,0
	li	a0,1
	call	sbi_ecall
	.loc 1 51 0
	nop
	ld	ra,24(sp)
	.cfi_restore 1
	ld	s0,16(sp)
	.cfi_restore 8
	add	sp,sp,32
	.cfi_def_cfa_register 2
	jr	ra
	.cfi_endproc
.LFE1:
	.size	sbi_putchar, .-sbi_putchar
	.text
.Letext0:
	.file 2 "/home/os22fall-stu/src/lab1/arch/riscv/include/sbi.h"
	.file 3 "/home/os22fall-stu/src/lab1/include/types.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1a1
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.byte	0x1
	.4byte	.LASF11
	.byte	0xc
	.4byte	.LASF12
	.4byte	.LASF13
	.4byte	.Ldebug_ranges0+0
	.8byte	0
	.4byte	.Ldebug_line0
	.byte	0x2
	.4byte	.LASF14
	.byte	0x3
	.byte	0x4
	.4byte	0x34
	.byte	0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF2
	.byte	0x4
	.4byte	.LASF15
	.byte	0x10
	.byte	0x2
	.byte	0x8
	.4byte	0x60
	.byte	0x5
	.4byte	.LASF0
	.byte	0x2
	.byte	0x9
	.4byte	0x60
	.byte	0
	.byte	0x5
	.4byte	.LASF1
	.byte	0x2
	.byte	0xa
	.4byte	0x60
	.byte	0x8
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF3
	.byte	0x6
	.4byte	.LASF16
	.byte	0x1
	.byte	0x31
	.8byte	.LFB1
	.8byte	.LFE1-.LFB1
	.byte	0x1
	.byte	0x9c
	.4byte	0x91
	.byte	0x7
	.string	"c"
	.byte	0x1
	.byte	0x31
	.4byte	0x91
	.byte	0x2
	.byte	0x91
	.byte	0x6c
	.byte	0
	.byte	0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.byte	0x8
	.4byte	.LASF17
	.byte	0x1
	.byte	0x5
	.4byte	0x3b
	.8byte	.LFB0
	.8byte	.LFE0-.LFB0
	.byte	0x1
	.byte	0x9c
	.4byte	0x19d
	.byte	0x7
	.string	"ext"
	.byte	0x1
	.byte	0x5
	.4byte	0x19d
	.byte	0x2
	.byte	0x91
	.byte	0x4c
	.byte	0x7
	.string	"fid"
	.byte	0x1
	.byte	0x5
	.4byte	0x19d
	.byte	0x2
	.byte	0x91
	.byte	0x48
	.byte	0x9
	.4byte	.LASF5
	.byte	0x1
	.byte	0x5
	.4byte	0x29
	.byte	0x2
	.byte	0x91
	.byte	0x40
	.byte	0x9
	.4byte	.LASF6
	.byte	0x1
	.byte	0x6
	.4byte	0x29
	.byte	0x3
	.byte	0x91
	.byte	0xb8,0x7f
	.byte	0x9
	.4byte	.LASF7
	.byte	0x1
	.byte	0x6
	.4byte	0x29
	.byte	0x3
	.byte	0x91
	.byte	0xb0,0x7f
	.byte	0x9
	.4byte	.LASF8
	.byte	0x1
	.byte	0x7
	.4byte	0x29
	.byte	0x3
	.byte	0x91
	.byte	0xa8,0x7f
	.byte	0x9
	.4byte	.LASF9
	.byte	0x1
	.byte	0x7
	.4byte	0x29
	.byte	0x3
	.byte	0x91
	.byte	0xa0,0x7f
	.byte	0x9
	.4byte	.LASF10
	.byte	0x1
	.byte	0x8
	.4byte	0x29
	.byte	0x3
	.byte	0x91
	.byte	0x98,0x7f
	.byte	0xa
	.string	"ret"
	.byte	0x1
	.byte	0xa
	.4byte	0x3b
	.byte	0x2
	.byte	0x91
	.byte	0x50
	.byte	0xa
	.string	"a0"
	.byte	0x1
	.byte	0xb
	.4byte	0x29
	.byte	0x1
	.byte	0x5a
	.byte	0xa
	.string	"a1"
	.byte	0x1
	.byte	0xc
	.4byte	0x29
	.byte	0x1
	.byte	0x5b
	.byte	0xa
	.string	"a2"
	.byte	0x1
	.byte	0xd
	.4byte	0x29
	.byte	0x1
	.byte	0x5c
	.byte	0xa
	.string	"a3"
	.byte	0x1
	.byte	0xe
	.4byte	0x29
	.byte	0x1
	.byte	0x5d
	.byte	0xa
	.string	"a4"
	.byte	0x1
	.byte	0xf
	.4byte	0x29
	.byte	0x1
	.byte	0x5e
	.byte	0xa
	.string	"a5"
	.byte	0x1
	.byte	0x10
	.4byte	0x29
	.byte	0x1
	.byte	0x5f
	.byte	0xa
	.string	"a6"
	.byte	0x1
	.byte	0x11
	.4byte	0x29
	.byte	0x1
	.byte	0x60
	.byte	0xa
	.string	"a7"
	.byte	0x1
	.byte	0x12
	.4byte	0x29
	.byte	0x1
	.byte	0x61
	.byte	0
	.byte	0xb
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0xe
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0x1b
	.byte	0xe
	.byte	0x55
	.byte	0x17
	.byte	0x11
	.byte	0x1
	.byte	0x10
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x16
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0x13
	.byte	0x1
	.byte	0x3
	.byte	0xe
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x38
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x96,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0x8
	.byte	0x2e
	.byte	0x1
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x49
	.byte	0x13
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x5
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0xa
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x2
	.byte	0x18
	.byte	0
	.byte	0
	.byte	0xb
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x3c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.LFB0
	.8byte	.LFE0-.LFB0
	.8byte	.LFB1
	.8byte	.LFE1-.LFB1
	.8byte	0
	.8byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.8byte	.LFB0
	.8byte	.LFE0
	.8byte	.LFB1
	.8byte	.LFE1
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF4:
	.string	"unsigned int"
.LASF0:
	.string	"error"
.LASF2:
	.string	"long unsigned int"
.LASF16:
	.string	"sbi_putchar"
.LASF13:
	.string	"/home/os22fall-stu/src/lab1/arch/riscv/kernel"
.LASF14:
	.string	"uint64"
.LASF15:
	.string	"sbiret"
.LASF5:
	.string	"arg0"
.LASF6:
	.string	"arg1"
.LASF3:
	.string	"long int"
.LASF17:
	.string	"sbi_ecall"
.LASF1:
	.string	"value"
.LASF12:
	.string	"sbi.c"
.LASF7:
	.string	"arg2"
.LASF8:
	.string	"arg3"
.LASF9:
	.string	"arg4"
.LASF10:
	.string	"arg5"
.LASF11:
	.string	"GNU C11 7.5.0 -march=rv64imafd -mabi=lp64 -mcmodel=medany -g -fno-builtin -ffunction-sections -fdata-sections"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
