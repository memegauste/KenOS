#include <vga.h>
#include <kb.h>
#include <sys.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <timer.h>
#include <serial.h>
uint32_t cpuCode[4];

#if defined(__cplusplus)
extern "C"
#endif
void kernel_main(void){
	terminal_initialize();
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    keyboard_install();
    serial_install();
    
    terminal_setcolor(VGA_COLOR_GREEN);
    terminal_writestring("Ken");
    terminal_setcolor(VGA_COLOR_RED);
    terminal_writestring("OS ");
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    terminal_writestring("ver 0.001 booted up!\n");
    terminal_setcolor(VGA_COLOR_LIGHT_CYAN);
    terminal_writestring("Welcome, Hoshi!\n");
    terminal_setcolor(VGA_COLOR_LIGHT_BLUE);
    terminal_writestring("Hardware info: ");
    terminal_writestring((const char*)cpuid_string(0, cpuCode));
    terminal_writestring("\n");
    terminal_setcolor(VGA_COLOR_WHITE);
    terminal_writestring("[@Hoshi]>");
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    write_serialstring("kenOS 0.001 serial debugger");

    __asm__ __volatile__ ("sti");
    for(;;);
}