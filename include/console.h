#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <types.h>

static uint16_t *video_buffer = (uint16_t *)(0xffff800000000000 + 0xb8000);

void printk(const char *fmt);

#endif // __CONSOLE_H__
