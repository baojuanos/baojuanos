#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <types.h>

#define CRTPORT 0x3d4

typedef enum console_color_t {
  black       = 0,
  blue        = 1,
  green       = 2,
  cyan        = 3,
  red         = 4,
  magenta     = 5,
  brown       = 6,
  light_gray  = 7,
  dark_gray   = 8,
  light_blue  = 9,
  light_green = 10,
  light_cyan  = 11,
  light_red   = 12,
  pink        = 13,
  yellow      = 14,
  white       = 15,
} console_color_t;

struct console_t {
  uint16_t *buffer;
  uint16_t pos;
  console_color_t forecolor;
  console_color_t backcolor;
};

static struct console_t console = {
    .buffer    = (uint16_t *)(0xffff800000000000 + 0xb8000),
    .pos       = 0,
    .forecolor = white,
    .backcolor = black,
};

void console_reset();

void console_reset_pos();

void console_set_pos(uint16_t pos);

uint16_t console_get_pos();

void console_clear();

void console_write(char c);

void console_set_color(console_color_t backcolor, console_color_t forecolor);

void printk(const char *fmt);

void printk_color(console_color_t backcolor, console_color_t forecolor, const char *fmt);

#endif // __CONSOLE_H__
