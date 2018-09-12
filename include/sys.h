#ifndef _SYS_H
#define _SYS_H
#include <stdint.h>
#include <stddef.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void cpuid(int code, uint32_t *a, uint32_t *d);
int cpuid_string(int code, uint32_t where[4]);
void reboot();

#endif