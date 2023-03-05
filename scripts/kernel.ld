ENTRY(_start)

SECTIONS
{
  . = 1M;

  .bstext :
  {
    arch/x86_64/boot.o (.bstext)
  }

  .bsdata :
  {
    arch/x86_64/boot.o (.bsdata)
  }
}
