ENTRY(_start)

SECTIONS
{
  . = 1M;

  .boot :
  {
    *(.multiboot)
  }
}
