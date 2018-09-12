#include <sys.h>

void outb(uint16_t port, uint8_t val){
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port){
    uint8_t ret;
    asm volatile ("inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port));
    return ret;
}

void cpuid(int code, uint32_t *a, uint32_t *d){
  asm volatile("cpuid":"=a"(*a),
               "=d"(*d):"a"(code):"ecx","ebx");
}

int cpuid_string(int code, uint32_t where[4]){
  asm volatile("cpuid":"=a"(*where),"=b"(*(where+1)),
               "=c"(*(where+2)),"=d"(*(where+3)):"a"(code));
  return (int)where[0];
}

void reboot(){
    uint8_t temp;
    asm volatile ("cli");
    
    do{
        temp = inb(0x64);
        if((temp) & (1<<(0)) != 0) inb(0x60);
    } while((temp) & (1<<(1)) != 0);
 
    outb(0x64, 0xFE);
loop:
    asm volatile ("hlt");
    goto loop;
}