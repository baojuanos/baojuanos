#include <console.h>

void printk(const char *fmt) {
  for (int i = 0; fmt[i] != '\0'; i++) {
    video_buffer[i] = fmt[i] | 0x0a00;
  }
}
