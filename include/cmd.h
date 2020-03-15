#ifndef _CMD_H
#define _CMD_H
#include <vga.h>

int strcmp(const char* s1, const char* s2);
const char* neofetch();
const char* execute(const char *command);
int execution_router(const char *command, unsigned short int source);

#endif