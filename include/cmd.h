#ifndef _CMD_H
#define _CMD_H
#include <vga.h>

int strcmp(const char* s1, const char* s2);
void gen_space(short int i);
void kenfetch();
void execute(unsigned char *command);

#endif