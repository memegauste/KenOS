#include <idt.h>
#include <regs.h>
#include <stddef.h>

void* memset(void *s, int c, size_t len){
    unsigned char *dst = s;
    while(len > 0){
        *dst = (unsigned char)c;
        dst++;
        len--;
    }
    return s;
}

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].flags = flags | 0x60;
}

void idt_install(){
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = &idt;

    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    idt_load();
}