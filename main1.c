#include "Timer.h"
#include "ping.h"

int main(void) {
    timer_init(); 
    lcd_init();
    ping_init();

    while (1) {
        ping_trigger();           
        timer_waitMillis(2000);   
    }


    //part 2 and 3
    while (1) {
        int width = ping_read();  
 
        if (width == 0) {
            lcd_printf("Nothinhg");
        } else {
            lcd_printf("Pulse width:\n%d cycles", width);

            //3
            float ms = ping_cyclesToMs(width);
            float cm = ping_cyclesToCm(width);
 
            lcd_printf("Cycles: %d\nTime: %.2f ms\nDist: %.2f cm\nOverflows: %d", width, ms, cm, ping_getOverflowCount());
        }
 
        timer_waitMillis(500);
    }
}