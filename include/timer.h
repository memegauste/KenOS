#ifndef _TIMER_H
#define _TIMER_H
#include <regs.h>
#include <vga.h>
#include <irq.h>

int timer_ticks;
void timer_handler(struct regs *r);
void timer_install();
void timer_wait(int ticks);

#endif
