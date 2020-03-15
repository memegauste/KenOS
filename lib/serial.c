#include <sys.h>
#define PORT 0x3f8   /* COM1 */
#include <vga.h>
#include <scancode.h>
#define SERIAL 2
unsigned char serialCommandBuffer[70];
unsigned short int serialPtr = 0;

void init_serial(){
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   outb(PORT + 1, 0x01);
   inb(0x3f8);
}

int is_transmit_empty(){
   return inb(PORT + 5) & 0x20;
}
 
void write_serial(char a){
   while (is_transmit_empty() == 0);
 
   outb(PORT,a);
}

int serial_received(){
   return inb(PORT + 5) & 1;
}
 
char read_serial(){
   while (serial_received() == 0);
 
   return inb(PORT);
}

void write_serialstring(const char *data){
    for (size_t i = 0; i < strlen(data); i++)
        write_serial(data[i]);
}

void clean_serial(){
    for(short unsigned i = 0; i < 70; i++){
        serialCommandBuffer[i] = '\0';
    }
    serialPtr = 0;
}

void serial_handler(struct regs *r){
    char key = read_serial();
    if(key == '\n'){
       execution_router(serialCommandBuffer, SERIAL);
       clean_serial();
    }
    else if(serialPtr < 70){
       serialCommandBuffer[serialPtr] = key;
       serialPtr++;
    }
}

/* Installs the serial handler into IRQ4.*/
void serial_install(){
    irq_install_handler(4, serial_handler);
    init_serial();
}