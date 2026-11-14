

/**
 * main.c
 */


//we are using cybot 28

#include "lcd.h"
#include "Timer.h"
#include "servo.h"

int main(void)
{
    timer_init();
    lcd_init();
    servo_init();

    float answer = servo_move();
    while(1)
    {
        lcd_printf("Position: %f", answer);
    }



    return 0;
}
