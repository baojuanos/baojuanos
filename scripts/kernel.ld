ENTRY(_start)

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

  .text : 
  {
    * (.text)
  }

  .rodata :
  {
    * (.rodata)
    * (.rodata.*)
  }

  .data :
  {
    * (.data)
  }

  .bss :
  {
    * (.bss)
  }
}
