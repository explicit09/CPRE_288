#include "lcd.h"
#include "part5_cyBot.h"
#include "movement.h"
#include "open_interface.h"
#include "Timer.h"

/// for roomba 12

int main(void)
{ //initialize the UART function
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    cyBot_uart_init();
    timer_init();
    lcd_init();

    //  int letter = cyBot_getByte();
    char message[100] = "";

    while (1)
    {

        int letter = cyBot_getByte();
        if (letter == 'w')
        { //w forward
            oi_setWheels(100, 100);
        }
        else if (letter == 's')
        { //s go back
            oi_setWheels(-100, -100);
        }
        else if (letter == 'a')
        { //a turn left
            turn(sensor_data, 90, 0);
            oi_setWheels(100, 100);
        }
        else if (letter == 'd')
        { //d turn right
            turn(sensor_data, 90, 1);
            oi_setWheels(100, 100);
        }

        else if (letter == 'm')
        { //m
            cyBot_sendByte(letter);
            sprintf(message, "Got an %s", letter);
            lcd_puts(message);
        }

        else
        {
            oi_setWheels(0, 0);
        }
    }

    return 0;
}
