/*
 * lab5_p2.c
 *
 *  Created on: Sep 30, 2026
 *      Author: nkantner
 */

#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include "Timer.h"
#include "lcd.h"
#include "string.h"
#include "sensor-data -3.h"
#include "math.h"
#include "stdio.h"
#include "open_interface.h"
#include "inc/tm4c123gh6pm.h"
#include "functions.h"
#include "clean.h"

// 227500 - right cal
// 1282750 - left cal
// for cyBOT 22

int main(void)
{
    timer_init();
   // lcd_init(); --> we are no longer displaying it on LCD
    cyBOT_init_Scan(0b0111);
    //cyBOT_SERVO_cal();
    cyBot_uart_init();
    right_calibration_value = 227500;
    left_calibration_value = 1282750;

    int meters;
    int putty;
    char message[50];
    float dist[91];
    char *header;
    int output;
    cyBOT_Scan_t scan;

    for (meters = 0; meters <= 180; meters += 2) //scans 180 and records dist as it goes
    {
        cyBOT_Scan(meters, &scan);
        dist[meters / 2] = scan.sound_dist;
    }

    while (1)
    {
        header = "\nDegrees\t\tDistance (cm)\n";
        char title1[] = "** Raw noisy sensor data **\n";

        print_to_putty(title1);
        print_to_putty(header);
        
        for (putty = 0; putty < 91; putty++) //storing
        {
            sprintf(message, "%d\t\t%.1f\n", putty * 2, dist[putty]);
            print_to_putty(message);
        }

        //=====================================================================================
        //noiseless cleaning algo

        
        // Iterates through an array of sensor data, and prints the values.
        // Note: Consider updating code so that max index (l)
        // automatically matches the number of elements in
        // sensor_data_array

        char title2[] = "** Cleaned data **\n";
        print_to_putty(title2);
        print_to_putty(header);

        //removce outliers
        outlier_removal(dist);
        

        ///sliding window
        char message2[] = "";
        moving_average(message2, dist);

//=========================================================================================

        detect_object(dist);
        9
        int k;
        double min = 100;
        int small_obj;
        for (k = 1; k < obj + 1; k++)
        {
            if (width[k] < min)
            {
                min = width[k];
                small_obj = k;
            }
        }

        char title3[] = "Object#\tAngle\tDistance\tWidth\n";
        char message3[] = "";

        print_to_putty(title3);
        for (a = 1; a <= obj; a++)
        {
            sprintf(message3, "%d\t%d\t%.1f\t\t%.1f\n", a, angle[a], dect[a], width[a]);
            print_to_putty(message3);
        }

        point_to_smallest_obj(angle[small_obj]);
    }
    return 0;
}
