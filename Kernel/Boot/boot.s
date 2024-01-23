.set ALIGN,    1<<0             
.set MEMINFO,  1<<1            
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002    
.set CHECKSUM, -(MAGIC + FLAGS)

gdtr:
    .long 0 # Limit
    .long 0 # Base
    
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
.section .text
.global _start
.type _start, @function

    
_start:
	mov $stack_top, %esp
	# This is a good place to initialize crucial processor state before the
	# high-level kernel is entered. It's best to minimize the early
	# environment where crucial features are offline. Note that the
	# processor is not fully initialized yet: Features such as floating
	# point instructions and instruction set extensions are not initialized
	# yet. The GDT should be loaded here. Paging should be enabled here.
	# C++ features such as global constructors and exceptions will require
	# runtime support to work as well.
    call gdt_init
	call kernel_main

	cli
1:	hlt
	jmp 1b

.size _start, . - _start

# Sets up GDTR
