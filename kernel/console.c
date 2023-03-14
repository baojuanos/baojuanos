#include <console.h>
#include <x86_64.h>

void console_write(char c) {
  // read cursor_pos
  uint16_t pos        = console.pos;
  console.buffer[pos] = c | ((console.backcolor << 4 | console.forecolor) << 8);
  // write cursor_pos
  console_set_pos(pos + 1);
}

void console_reset() {
  console_clear();
  console_reset_pos();
}

void console_reset_pos() { console_set_pos(0); }

void console_set_pos(uint16_t pos) {
  outb(CRTPORT, 14);
  outb(CRTPORT + 1, pos >> 8);
  outb(CRTPORT, 15);
  outb(CRTPORT + 1, pos);
  console.pos = pos;
}

uint16_t console_get_pos() {
  // uint16_t pos;
  // outb(CRTPORT, 14);
  // pos = inb(CRTPORT + 1) << 8;
  // outb(CRTPORT, 15);
  // pos |= inb(CRTPORT + 1);
  return console.pos;
}

void console_clear() {
  for (int i = 0; i < 80 * 25; i++) {
    console_write(' ');
  }
}

void console_set_color(console_color_t backcolor, console_color_t forecolor) {
  console.backcolor = backcolor;
  console.forecolor = forecolor;
}

void printk(const char *fmt) {
  for (int i = 0; fmt[i] != '\0'; i++) {
    console_write(fmt[i]);
  }
}

void printk_color(console_color_t backcolor, console_color_t forecolor, const char *fmt) {
  console_set_color(backcolor, forecolor);
  printk(fmt);
}
