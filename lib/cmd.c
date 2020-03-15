#include <cmd.h>
#include <sys.h>
#include <data/kenfetch.h>

int strcmp(const char* s1, const char* s2){
    while(*s1 && (*s1 == *s2)){
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void gen_space(short int i){
    while(i>0){
        terminal_putchar(' ');
        i--;
    }
}

void neofetch(){
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    for(int i = 0; i < strlen)
}

void execute(const char *command){
    terminal_setcolor(VGA_COLOR_CYAN);
    if(!strcmp(command, "help")){
        terminal_writestring("\nCommands: help, shell, user, kenfetch, osinfo, cls, reboot\n");
    } else if(!strcmp(command, "shell")){
        terminal_writestring("\nYou are using Simpell, that means simple shell\n");
    } else if(!strcmp(command, "user")){
        terminal_writestring("\nUser: Hoshi\n");
    } else if(!strcmp(command, "kenfetch")){
        neofetch();
    } else if(!strcmp(command, "osinfo")){
        terminal_writestring("\nKenOS, developed in mistery environment\n");
    } else if(!strcmp(command, "reboot")){
        terminal_writestring("\nPreparing to reboot...\n");
        reboot();
    } else if(!strcmp(command, "cls")){
        terminal_clean();
    } else {
        terminal_writestring("\nNot known command, sorry mate!\n");
    }
    terminal_setcolor(VGA_COLOR_WHITE);
    terminal_writestring("[@Hoshi]>");
    terminal_setcolor(VGA_COLOR_LIGHT_GREY);
}