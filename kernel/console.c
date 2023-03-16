#include <console.h>
#include <kernel.h>
#include <stdarg.h>
#include <x86_64.h>

static struct console_t console = {
    .buffer    = (uint16_t *)(KERNEL_BASE + CRT_BUFFER_BASE),
    .pos       = 0,
    .forecolor = white,
    .backcolor = black,
};

// 设置光标位置
static void console_set_pos(uint16_t pos) {
  outb(CRT_IC, CRT_CURSOR_HIGH_HALF);
  outb(CRT_DC, pos >> 8);
  outb(CRT_IC, CRT_CURSOR_LOW_HALF);
  outb(CRT_DC, pos);
  console.pos = pos;
}

// 向屏幕打印一个字符
static void console_write(char c) {
  // 获取光标当前位置，这里没有从硬件取而是直接从系统维护的字段中取的
  uint16_t pos  = console.pos;
  uint16_t attr = ((console.backcolor << 4 | console.forecolor) << 8);
  uint16_t ch   = (c & 0xff) | attr;

  // 换行
  if (c == '\n') {
    pos = pos + CRT_COLUMNS - pos % CRT_COLUMNS;
  } else {
    console.buffer[pos++] = ch;
  }

  // 如果位置超出屏幕则将每行向上移动一行并将最后一行清空
  if (pos >= CRT_COLUMNS * CRT_ROWS) {
    for (int i = 0; i < CRT_COLUMNS * (CRT_ROWS - 1); i++) {
      console.buffer[i] = console.buffer[i + CRT_COLUMNS];
    }
    for (int i = CRT_COLUMNS * (CRT_ROWS - 1); i < CRT_COLUMNS * CRT_ROWS; i++) {
      console.buffer[i] = ' ' | attr;
    }
    pos = pos - CRT_COLUMNS;
  }

  console_set_pos(pos);
  console.buffer[pos] = ' ' | attr;
}

static void printint(int xx, int base, bool sign) {
  static char digits[] = "0123456789abcdef";
  char buf[16];
  int i;
  unsigned int x;

  if (sign && (sign = xx < 0)) {
    x = -xx;
  } else {
    x = xx;
  }

  i = 0;

  do {
    buf[i++] = digits[x % base];
  } while ((x /= base) != 0);

  if (sign) {
    buf[i++] = '-';
  }

  while (--i >= 0) {
    console_write(buf[i]);
  }
}

static void console_clear() {
  for (int i = 0; i < CRT_COLUMNS * CRT_ROWS; i++) {
    console_write(' ');
  }
}

void console_reset() {
  console_clear();
  console_set_pos(0);
}

void printk(const char *fmt, ...) {

  va_list ap;
  va_start(ap, fmt);

  char *s;
  int c;

  for (int i = 0; (c = fmt[i] & 0xff) != 0; i++) {
    if (c != '%') {
      console_write(c);
      continue;
    }

    c = fmt[++i] & 0xff;

    if (c == 0)
      break;

    switch (c) {
      case 'd':
        printint(va_arg(ap, int), 10, true);
        break;
      case 'x':
      case 'p':
        printint(va_arg(ap, int), 16, false);
        break;
      case 's':
        if ((s = va_arg(ap, char *)) == 0)
          s = "(null)";
        for (; *s; s++)
          console_write(*s);
        break;
      case '%':
        console_write('%');
        break;
      default:
        console_write('%');
        console_write(c);
        break;
    }
  }

  va_end(ap);
}
