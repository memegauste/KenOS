#include <kb.h>
#include <vga.h>
#include <scancode.h>
#include <sys.h>
#include <irq.h>
#include <cmd.h>
unsigned char command[70];
unsigned short int ptr = 0;

void clean_command(){
    for(short unsigned i = 0; i < 70; i++){
        command[i] = '\0';
    }
    ptr = 0;
}

void keyboard_handler(struct regs *r)
{
    unsigned char key;

    key = inb(0x60);

    if (key & 0x80){
        //Hold
    }
    else{
        if(scancode[key] == '\b' && ptr > 0){
            terminal_backspace();
            ptr--;
            command[ptr] = '\0';
        } else if(scancode[key] == '\n'){
            execute(command);
            clean_command();
        } else if (ptr < 70 && scancode[key] != '\b'){
            terminal_putchar(scancode[key]);
            command[ptr] = scancode[key];
            ptr++;
        }
    }
}

/* Installs the keyboard handler into IRQ1 */
void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);

    clean_command();
}