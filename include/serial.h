#ifndef _SERIAL_H
#define _SERIAL_H

void init_serial();
int is_transmit_empty();
void write_serial(char a);
int serial_received();
char read_serial();
void write_serialstring(const char *data);
void serial_handler();
void serial_install();

#endif