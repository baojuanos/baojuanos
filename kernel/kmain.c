#include <mmu.h>
#include <types.h>

uint16_t *video_buffer = (uint16_t *)(0xffff800000000000 + 0xb8000);

void printf(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    video_buffer[i] = str[i] | 0x0a00;
  }
}

void kernel_main() {
  printf("Baojuan my voice!");

  seginit();

  for (;;) {
    ;
  }
}
