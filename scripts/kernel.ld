ENTRY(_start)

KERNEL_BASE = 0xffff800000000000;

SECTIONS
{
  . = 1M;

  .bstext :
  {
    * (.bstext)
  }

  .bsdata :
  {
    * (.bsdata)
  }

  . += KERNEL_BASE;

  .text : AT(ADDR(.text) - KERNEL_BASE) ALIGN(4K)
  {
    * (.text)
  }

  /* PROVIDE 指令用于在给定的位置定义一个符号 */
  PROVIDE(etext = .);

  .rodata : ALIGN(4K)
  {
    * (.rodata)
    * (.rodata.*)
  }

  .data : ALIGN(4K)
  {
    * (.data)
  }

  PROVIDE(edata = .);

  .bss : ALIGN(4K)
  {
    * (.bss)
  }

  PROVIDE(end = .);
}
