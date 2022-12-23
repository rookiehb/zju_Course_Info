.extern start_kernel

    .section .text.entry
    .globl _start
_start:
    # ------------------
    # - your code here -
    # ------------------
    la sp, boot_stack_top
    jal start_kernel
    .section .bss.stack
    .globl boot_stack
boot_stack:
    #.space XYZ # <-- change to your stack size
    .space 4096
    .globl boot_stack_top
boot_stack_top:
