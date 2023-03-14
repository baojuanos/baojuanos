#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <types.h>

// CRT 显卡文本模式内存映射起始地址
#define CRT_BUFFER_BASE 0xb8000

// CRT 文本模式行数
#define CRT_ROWS 25

// CRT 文本模式列数
#define CRT_COLUMNS 80

// CRT 索引寄存器端口
#define CRT_IC 0x3d4

// CRT 数据寄存器端口
#define CRT_DC 0x3d5

// CRT 光标位置寄存器高 8 位索引值
#define CRT_CURSOR_HIGH_HALF 0xe

// CRT 光标位置寄存器低 8 位索引值
#define CRT_CURSOR_LOW_HALF 0xf

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

void console_reset();

void printk(const char *fmt, ...);

#endif // __CONSOLE_H__
