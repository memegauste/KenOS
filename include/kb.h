#ifndef _KB_H
#define _KB_H
#include <regs.h>

void clean_command();
void keyboard_handler(struct regs *r);
void keyboard_install();

#endif