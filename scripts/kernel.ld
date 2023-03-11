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

  . = ALIGN(4K);

  _bs_end = .;

  . += KERNEL_BASE;

  .text : AT(_bs_end)
  {
    * (.text)
  }

  .rodata : ALIGN(4K)
  {
    * (.rodata)
    * (.rodata.*)
  }

  .data : ALIGN(4K)
  {
    * (.data)
  }

  .bss : ALIGN(4K)
  {
    * (.bss)
  }
}
