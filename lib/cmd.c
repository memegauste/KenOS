#include <cmd.h>
#include <sys.h>
#include <data/kenfetch.h>
#include <stdbool.h>
#include <vga.h>
#define KENOUT 1
#define SERIAL 2

int strcmp(const char* s1, const char* s2){
    while(*s1 && (*s1 == *s2)){
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

const char* neofetch(){
    return kenfetch;
}

const char* execute(const char *command){
    if(!strcmp(command, "help")){
        return "Commands: help, shell, user, kenfetch, osinfo, cls, reboot";
    } else if(!strcmp(command, "shell")){
        return "You are using Simpell, that means simple shell";
    } else if(!strcmp(command, "user")){
        return "User: Hoshi";
    // } else if(!strcmp(command, "kenfetch")){
    //     return neofetch();
    } else if(!strcmp(command, "osinfo")){
        return "KenOS, developed in mistery environment";
    } else if(!strcmp(command, "reboot")){
        reboot();
    } else if(!strcmp(command, "cls")){
        terminal_clean();
    } else {
        return "Not known command, sorry mate!";
    }
}

int execution_router(const char *command, unsigned short int source){
    if(source == KENOUT){
        terminal_setcolor(VGA_COLOR_WHITE);
        terminal_putchar('\n');
        terminal_writestring(execute(command));
        terminal_writestring("\n[@Hoshi]>");
        terminal_setcolor(VGA_COLOR_LIGHT_GREY);
    } else if (source == SERIAL && strcmp(command, "reboot") && strcmp(command, "cls")){
        write_serialstring("KenOutput: {");
        write_serialstring(execute(command));
        write_serialstring("}\n");
    }
    return 0;
}

