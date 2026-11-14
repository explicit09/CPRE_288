#include "common.h"
#include "movement.h"
#include "stdio.h"
#include "math.h"
#include "functions.h"
#include "clean.h"
#include "init.h"
#include "scanner.h"
#include "modes.h"
#include "adc.h"
#include "uart.h"

dataa impp;
float dist[91];
float estimate[91];
int ir[91];
//int clicked = 0;
//int clockwise = 0;
//int degrees_to_turn = 0;
int small = 0;


// Net--> just added common, clean, function.h, movements.h, modes, etc to folder 9
//in sanner.c ir is switched to adc
int main(void)
{
    init();
    timer_init();
    //lcd_init();
    uart_init();

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    volatile int letter;
    char message[100];

    letter = uart_receive();
    if(letter == 'A')
    {
        drive_mm(sensor_data, 200);

        sprintf(message, "CliffFrontLeft %d, CliffFrontRight %d", sensor_data->cliffFrontLeft, sensor_data->cliffFrontRight);
        print_to_putty(message);
    }


//    while (1)
//    {
//        letter = uart_receive();
//
//        if (letter == 'h')
//        {
//            autonomous(sensor_data);
//        }
//        else if (letter == 'H')
//        {
//            auto_move(sensor_data);
//        }
//        else if (letter == 'o')
//        {
//            scan_360(sensor_data);
//        }
//        else
//        {
//            manual_drive(sensor_data, letter);
//            uart_sendChar('f');
//            uart_sendChar('\n');
//        }
//       // letter = uart_receive();
//
//
//        //uart_sendChar['']
//
//
//
//    }

    return 0;
}
