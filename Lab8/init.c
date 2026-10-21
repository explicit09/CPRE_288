#include "init.h"
#include "common.h"


void init()
{
    timer_init();
    lcd_init();
    uart_init();
    uart_interrupt();

    cyBOT_init_Scan(0b0111);
    //cyBot_uart_init();
    right_calibration_value = 227500;
    left_calibration_value = 1282750;
}
