
OUTPUT_FORMAT("elf32-bfin","elf32-bfin","elf32-bfin")
OUTPUT_ARCH(bfin)

PROVIDE (ldf_stack_end = 0xffb00FFC ) ;
PROVIDE (hardware_init_hook = 0) ;
PROVIDE (software_init_hook = 0) ;
PROVIDE (software_term_hook = 0) ;
ENTRY (start);

MEMORY
  {
    MEM_SDRAM (XW)    : ORIGIN = 0x00000002, LENGTH = 128M
    MEM_ASYNC_0 (XW)  : ORIGIN = 0x20000000, LENGTH = 1M
    MEM_ASYNC_1 (XW)  : ORIGIN = 0x20100000, LENGTH = 1M
    MEM_ASYNC_2 (XW)  : ORIGIN = 0x20200000, LENGTH = 1M
    MEM_ASYNC_3 (XW)  : ORIGIN = 0x20300000, LENGTH = 1M

    MEM_DATA_A (W!X)  : ORIGIN = 0xff800000, LENGTH = 32K
    MEM_DATA_B (W!X)  : ORIGIN = 0xff900000, LENGTH = 16K
    MEM_INST (XR)     : ORIGIN = 0xffa00000, LENGTH = 64K
    MEM_SCRATCH (W!X) : ORIGIN = 0xffb00000, LENGTH = 4K
  }

SECTIONS
{
    .init :
    {
        KEEP (*(.init))
    } > MEM_INST

    .text :
    {
        libkernel.a(.text .stub .text.* .gnu.linkonce.t.*)
	start.o(.text .stub .text.* .gnu.linkonce.t.*)
	sample1.o(.text .stub .text.* .gnu.linkonce.t.*)
        timer.o(.text .stub .text.* .gnu.linkonce.t.*)
        serial.o(.text .stub .text.* .gnu.linkonce.t.*)
        logtask.o(.text .stub .text.* .gnu.linkonce.t.*)
        log_output.o(.text .stub .text.* .gnu.linkonce.t.*)
        vasyslog.o(.text .stub .text.* .gnu.linkonce.t.*)
        t_perror.o(.text .stub .text.* .gnu.linkonce.t.*)
        strerror.o(.text .stub .text.* .gnu.linkonce.t.*)
        kernel_cfg.o(.text .stub .text.* .gnu.linkonce.t.*)
   } > MEM_INST

    .text.mruby :
    {
        *(.text .stub .text.* .gnu.linkonce.t.*)
    } > MEM_SDRAM

    .fini :
    {
        KEEP (*(.fini))
    } > MEM_INST

    .rodata.mruby :
    {
        libmruby.a (.rodata .rodata.* .gnu.linkonce.r.*)
    } > MEM_SDRAM

    .rodata :
    {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
    } > MEM_DATA_A

    .data.mruby :
    {
        libmruby.a (.data)
    } > MEM_SDRAM

    .data :
    {
        *(.data)
    } > MEM_DATA_A

    .eh_frame : { KEEP (*(.eh_frame)) }
    .gcc_except_table : { *(.gcc_except_table) }

    .ctors :
    {
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o ) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*(.ctors))
    } > MEM_DATA_A

    .dtors :
    {
        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o ) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*(.dtors))
    } > MEM_DATA_A

    .bss :
    {
        __bss_start = . ;
        *(.bss)
        *(COMMON)
        __bss_end = . ;
    } > MEM_SDRAM

    __heap_start = . + 32;
    __heap_end = ORIGIN(MEM_SDRAM) + LENGTH(MEM_SDRAM) ;

    .comment        0 : { *(.comment) }
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
}
