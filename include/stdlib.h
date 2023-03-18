#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <types.h>

char *itoa(int32_t n, char *buffer, int radix);

char *ulltoa(uint64_t n, char *buffer, int radix);

#endif // __STDLIB_H__
