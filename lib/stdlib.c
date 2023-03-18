#include <stdlib.h>

static char digits[] = "0123456789abcdef";

char *itoa(int32_t n, char *buffer, int radix) {
  int i  = 0;
  int nn = n;

  if (n < 0) {
    nn          = -nn;
    buffer[i++] = '-';
  }

  // 此时存入 buffer 中的数据是逆序的，例如数字 1024，转为字符串在 buffer 中是 "4201"
  do {
    buffer[i++] = digits[nn % radix];
  } while ((nn /= radix) != 0);

  size_t length = 0;
  while (buffer[length] != '\0') {
    length++;
  }

  // 反转字符串为正常顺序
  char t;
  // 如果数字小于 0，则需从第二个字符开始反转，因为此时第一个字符是负号 '-'
  char *buf = (n < 0) ? buffer + 1 : buffer;
  length    = (n < 0) ? length - 1 : length;
  for (i = 0; i < length / 2; i++) {
    t                   = buf[i];
    buf[i]              = buf[length - i - 1];
    buf[length - i - 1] = t;
  }
  return buffer;
}

char *ulltoa(uint64_t n, char *buffer, int radix) {
  int i = 0;

  do {
    buffer[i++] = digits[n % radix];
  } while ((n /= radix) != 0);

  size_t length = 0;
  while (buffer[length] != '\0') {
    length++;
  }

  char t;
  for (i = 0; i < length / 2; i++) {
    t                      = buffer[i];
    buffer[i]              = buffer[length - i - 1];
    buffer[length - i - 1] = t;
  }
  return buffer;
}
