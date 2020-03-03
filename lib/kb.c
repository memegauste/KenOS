#include <kb.h>
#include <vga.h>
#include <scancode.h>
#include <stdbool.h>
#include <sys.h>
#include <irq.h>
#include <cmd.h>
#include <serial.h>
unsigned char command[70];
unsigned short int ptr = 0;
bool isShiftPressed = 0;

void clean_command(){
    for(short unsigned i = 0; i < 70; i++){
        command[i] = '\0';
    }
    ptr = 0;
}

void keyboard_handler(struct regs *r){
    unsigned char key;

    key = inb(0x60);

    // Check if shift is pressed
    
    if (key & 0x80){
        key -= 0x80;
        if(key == 0x2A || key == 0x36){
            isShiftPressed = false;
        }
    }
    else{
        if(key == 0x2A || key == 0x36){
            isShiftPressed = true;
        } else if(scancode[key] == '\b' && ptr > 0){
            terminal_backspace();
            ptr--;
            command[ptr] = '\0';
        } else if(scancode[key] == '\n'){
            execute((const char*)command);
            clean_command();
        } else if (ptr < 70 && scancode[key] != '\b'){
            char key_result = scancode[key];
            if(isShiftPressed){
                key_result -= 32;
                if(key_result < 'A' || key_result > 'Z'){
                    key_result = 0;
                }
            }
            terminal_putchar(key_result);
            command[ptr] = key_result;
            ptr++;
        }
    }
    write_serial(key);
}

/* Installs the keyboard handler into IRQ1 */
void keyboard_install(){
    irq_install_handler(1, keyboard_handler);

    clean_command();
}