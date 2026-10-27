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

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    volatile int letter;

    while (1)
    {
        letter = uart_receive();

        if (letter == 'h')
        {
            autonomous(sensor_data);
        }
        else if (letter == 'o')
        {
            scan_360(sensor_data);
        }
        else
        {
            manual_drive(sensor_data, letter);
        }

    }
    return 0;
}
