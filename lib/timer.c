#include <timer.h>
#include <regs.h>

unsigned int timer_ticks = 0;

void timer_handler(struct regs *r){
    timer_ticks++;

    if (timer_ticks % 18 == 0) terminal_writestring("One second has passed\n");
    
}

void timer_install(){
    irq_install_handler(0, timer_handler);
}

void timer_wait(unsigned int ticks){
    unsigned int eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}