.extern start_kernel
    .section .text.init
    # .section .text.entry
    .globl _start
_start:
    # ------------------
    # - your code here -
    # ------------------
    la sp, boot_stack_top
    la t0, _trap
    csrw stvec, t0
    
    csrr t0, sie
    ori t0, t0, 0x20
    csrw sie, t0
    
    rdtime t0
    li t1, 10000000
    add a0, t0, t1
    add a6, zero, zero
    add a7, zero, zero
    ecall
    
    csrr t0, sstatus
    ori t0, t0, 0x02
    csrw sstatus, t0    

    jal start_kernel
    .section .bss.stack
    .globl boot_stack
boot_stack:
    #.space XYZ # <-- change to your stack size
    .space 4096
    .globl boot_stack_top
boot_stack_top:
