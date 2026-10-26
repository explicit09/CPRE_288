

/**
 * main.c
 */

#include "Timer.h"
#include <inc/tm4c123gh6pm.h>
#include "lcd.h"
#include "adc.h"
//#include "functions.h"
#include "uart.h"

int main(void)
{

    char message[100];
    //acd_init
    //while (1)
    //putty for
    //cybot_scan == ir_vlaue
    //display adc_read value
    //timer_waitMillis()
    int result = 0;

    timer_init();
    lcd_init();
    uart_init();
    adc_init();



    while(1)
    {
        result =  adc_read();
        //lcd_printf();
        sprintf(message,"ADC Value: %d", result);
        //print_to_putty(message);

        int k;
        uart_sendChar('\r');
        for (k = 0; k < strlen(message); k++)
        {
            uart_sendChar(message[k]);
        }

        timer_waitMillis(2000);

    }

    return 0;
}
