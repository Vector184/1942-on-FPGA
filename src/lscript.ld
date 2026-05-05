/*******************************************************************/
/*                                                                 */
/* MicroBlaze linker script for the FPGA hardware build.            */
/*                                                                 */
/* Code and global data are placed in the AXI MIG DDR3 region so    */
/* the application does not overflow local BRAM. Heap and stack are */
/* kept in local BRAM for fast call frames and dynamic allocation.  */
/*                                                                 */
/*******************************************************************/

_STACK_SIZE = DEFINED(_STACK_SIZE) ? _STACK_SIZE : 0x400;
_HEAP_SIZE = DEFINED(_HEAP_SIZE) ? _HEAP_SIZE : 0x800;

/* Define Memories in the system */

MEMORY
{
   local_memory : ORIGIN = 0x50, LENGTH = 0xFFB0
   mig_ddr3     : ORIGIN = 0x80000000, LENGTH = 0x10000000
}

/* Specify the default entry point to the program */

ENTRY(_start)

/* Define the sections, and where they are mapped in memory */

SECTIONS
{
.vectors.reset 0x0 : {
   KEEP (*(.vectors.reset))
}

.vectors.sw_exception 0x8 : {
   KEEP (*(.vectors.sw_exception))
}

.vectors.interrupt 0x10 : {
   KEEP (*(.vectors.interrupt))
}

.vectors.hw_exception 0x20 : {
   KEEP (*(.vectors.hw_exception))
}

.usb_isr : {
   . = ALIGN(4);
   KEEP (*(.usb_isr))
   KEEP (*(.usb_isr.*))
   . = ALIGN(4);
} > local_memory

.text : {
   *(.text)
   *(.text.*)
   *(.gnu.linkonce.t.*)
} > mig_ddr3

.note.gnu.build-id : {
   KEEP (*(.note.gnu.build-id))
} > mig_ddr3

.init : {
   KEEP (*(.init))
} > mig_ddr3

.fini : {
   KEEP (*(.fini))
} > mig_ddr3

.ctors : {
   __CTOR_LIST__ = .;
   ___CTORS_LIST___ = .;
   KEEP (*crtbegin.o(.ctors))
   KEEP (*(EXCLUDE_FILE(*crtend.o) .ctors))
   KEEP (*(SORT(.ctors.*)))
   KEEP (*(.ctors))
   __CTOR_END__ = .;
   ___CTORS_END___ = .;
} > mig_ddr3

.dtors : {
   __DTOR_LIST__ = .;
   ___DTORS_LIST___ = .;
   KEEP (*crtbegin.o(.dtors))
   KEEP (*(EXCLUDE_FILE(*crtend.o) .dtors))
   KEEP (*(SORT(.dtors.*)))
   KEEP (*(.dtors))
   PROVIDE(__DTOR_END__ = .);
   PROVIDE(___DTORS_END___ = .);
} > mig_ddr3

.rodata : {
   __rodata_start = .;
   *(.rodata)
   *(.rodata.*)
   *(.gnu.linkonce.r.*)
   __rodata_end = .;
} > mig_ddr3

.sdata2 : {
   . = ALIGN(8);
   __sdata2_start = .;
   *(.sdata2)
   *(.sdata2.*)
   *(.gnu.linkonce.s2.*)
   . = ALIGN(8);
   __sdata2_end = .;
} > mig_ddr3

.sbss2 : {
   __sbss2_start = .;
   *(.sbss2)
   *(.sbss2.*)
   *(.gnu.linkonce.sb2.*)
   __sbss2_end = .;
} > mig_ddr3

.data : {
   . = ALIGN(4);
   __data_start = .;
   *(.data)
   *(.data.*)
   *(.gnu.linkonce.d.*)
   __data_end = .;
} > mig_ddr3

.got : {
   *(.got)
} > mig_ddr3

.got1 : {
   *(.got1)
} > mig_ddr3

.got2 : {
   *(.got2)
} > mig_ddr3

.eh_frame : {
   *(.eh_frame)
} > mig_ddr3

.jcr : {
   *(.jcr)
} > mig_ddr3

.gcc_except_table : {
   *(.gcc_except_table)
} > mig_ddr3

.sdata : {
   . = ALIGN(8);
   __sdata_start = .;
   *(.sdata)
   *(.sdata.*)
   *(.gnu.linkonce.s.*)
   __sdata_end = .;
} > mig_ddr3

.sbss (NOLOAD) : {
   . = ALIGN(4);
   __sbss_start = .;
   *(.sbss)
   *(.sbss.*)
   *(.gnu.linkonce.sb.*)
   . = ALIGN(8);
   __sbss_end = .;
} > mig_ddr3

.tdata : {
   __tdata_start = .;
   *(.tdata)
   *(.tdata.*)
   *(.gnu.linkonce.td.*)
   __tdata_end = .;
} > mig_ddr3

.tbss : {
   __tbss_start = .;
   *(.tbss)
   *(.tbss.*)
   *(.gnu.linkonce.tb.*)
   __tbss_end = .;
} > mig_ddr3

.bss (NOLOAD) : {
   . = ALIGN(4);
   __bss_start = .;
   *(.bss)
   *(.bss.*)
   *(.gnu.linkonce.b.*)
   *(COMMON)
   . = ALIGN(4);
   __bss_end = .;
} > mig_ddr3

_SDA_BASE_ = __sdata_start + ((__sbss_end - __sdata_start) / 2 );

_SDA2_BASE_ = __sdata2_start + ((__sbss2_end - __sdata2_start) / 2 );

/* Generate Stack and Heap definitions in local BRAM */

.heap (NOLOAD) : {
   . = ALIGN(8);
   _heap = .;
   _heap_start = .;
   . += _HEAP_SIZE;
   _heap_end = .;
} > local_memory

.stack (NOLOAD) : {
   _stack_end = .;
   . += _STACK_SIZE;
   . = ALIGN(8);
   _stack = .;
   __stack = _stack;
} > local_memory

_end = .;
}
