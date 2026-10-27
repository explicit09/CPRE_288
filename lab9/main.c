//
//
///**
// * main.c
// */
//
//#include "Timer.h"
//#include <inc/tm4c123gh6pm.h>
//#include "lcd.h"
//#include "adc.h"
////#include "functions.h"
//#include "uart.h"
//#include "cyBot_Scan.h"
//#include "math.h"
//
//int main(void)
//{
//
//    char message[100];
//    //acd_init
//    //while (1)
//    //putty for
//    //cybot_scan == ir_vlaue
//    //display adc_read value
//    //timer_waitMillis()
//    int result = 0;
//    float dist;
//    //int ir;
//    float estimate;
//
//    timer_init();
//    cyBOT_init_Scan(0b0011);
//    lcd_init();
//    uart_init();
//
//
//    adc_init();
//
//    cyBOT_Scan_t scan;
//
//
// //calibrated for cybot 4
//    while(1)
//    {
//        //scanning
//        cyBOT_Scan(90, &scan);
//        dist = scan.sound_dist;
//
//
//        result =  adc_read();
//
//        estimate = 50316.8052 * pow(result, -1.06489);
//        lcd_printf(message,"ADC Value: %d", result);
//        sprintf(message,"ADC Value: %d Dist: %.1f Est Dist: %.1f", result, dist, estimate);
//        //print_to_putty(message);
//
//        int k;
//        uart_sendChar('\r');
//        for (k = 0; k < strlen(message); k++)
//        {
//            uart_sendChar(message[k]);
//        }
//
//        //message = "";
//
//        timer_waitMillis(1000);
//
//    }
//
//    return 0;
//}
