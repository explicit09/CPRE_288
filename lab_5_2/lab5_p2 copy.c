#include "lcd.h"
#include "movement.h"
#include "open_interface.h"
#include "Timer.h"
#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include "string.h"
#include "math.h"
#include "stdio.h"
#include "functions.h"
#include "clean.h"
#include "movement.h"

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
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    int meters;
    int putty;
    char message[50];
    float dist[91];
    char *header;
    double width_[10];
    double dect[10];
    int angle_[10];
    int a = 0;
    int obj1 = 0;
    dataa impp;
    int letter;
    int small_obj = 0;
    int degrees_to_turn;
    int clockwise = 0;
    char message3[50];
    int k;
    double min = 100;
    char title3[] = "Object#\tAngle\tDistance\tWidth\n";

    cyBOT_Scan_t scan;

    while (1)
    {
        letter = cyBot_getByte();
        if (letter == 'm')
        {
            for (meters = 0; meters <= 180; meters += 2) //scans 180 and records dist as it goes
            {
                cyBOT_Scan(meters, &scan);
                dist[meters / 2] = scan.sound_dist;
            }

            header = "\nDegrees\t\tDistance (cm)\n";
            char title1[] = "** Raw noisy sensor data **\n";

            print_to_putty(title1);
            print_to_putty(header);
            for (putty = 0; putty < 91; putty++) //printing message
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

            //remove outliers
            outlier_removal(dist);

            ///sliding window
            char message2[50];
            moving_average(dist);

            for (putty = 0; putty < 91; putty++) //printing message
            {
                sprintf(message2, "%d\t\t%.1f\n", putty * 2, dist[putty]);
                print_to_putty(message2);
            }
//=========================================================================================
            impp = detect_object(dist, dect, width_, angle_, obj1, impp);

            for (k = 1; k < impp.obj + 1; k++)
            {
                if (impp.width[k] < min)
                {
                    min = impp.width[k];
                    small_obj = k;
                }
            }

            print_to_putty(title3);
            for (a = 1; a <= impp.obj; a++)
            {
                sprintf(message3, "%d\t%d\t%.1f\t\t%.1f\n", a, impp.angle[a],
                        impp.dect[a], impp.width[a]);
                print_to_putty(message3);
            }

            point_to_smallest_obj(impp.angle[small_obj]);
            sprintf(message3, "The smallest object is %.1f",
                    impp.width[small_obj]);
            print_to_putty(message3);
            continue;
        }
        else if (letter == 'o')
        {
            meters = impp.angle[small_obj] - 45;
            int meters_end = impp.angle[small_obj] + 45;
            int counter = 0;
            for (; meters <= meters_end; meters += 2) //scans 180 and records dist as it goes
            {
                cyBOT_Scan(meters, &scan);
                dist[counter] = scan.sound_dist;
                counter++;
            }
            outlier_removal(dist);
            moving_average(dist);
            impp = detect_object(dist, dect, width_, angle_, obj1, impp);

            for (k = 1; k < impp.obj + 1; k++)
            {
                if (impp.width[k] < min)
                {
                    min = impp.width[k];
                    small_obj = k;
                }
            }
            print_to_putty(title3);
            for (a = 1; a <= impp.obj; a++)
            {
                sprintf(message3, "%d\t%d\t%.1f\t\t%.1f\n", a, impp.angle[a],
                        impp.dect[a], impp.width[a]);
                print_to_putty(message3);
            }

            point_to_smallest_obj(impp.angle[small_obj]);
            sprintf(message3, "The smallest object is at %d",
                    impp.angle[small_obj]);
            print_to_putty(message3);
            continue;

        }
        else if (letter == 'w')
        { //w forward
            oi_setWheels(100, 100);
            continue;
        }
        else if (letter == 's')
        { //s go back
            oi_setWheels(-100, -100);
            continue;
        }
        else if (letter == 'a')
        { //a turn left
            turn(sensor_data, 90, 0);
            oi_setWheels(100, 100);
            continue;
        }
        else if (letter == 'd')
        { //d turn right
            turn(sensor_data, 90, 1);
            oi_setWheels(100, 100);
            continue;
        }
        else if (letter == 'c')
        {
            if (impp.angle[small_obj] < 90)
            {
                clockwise = 1;
            }
            degrees_to_turn = 90 - impp.angle[small_obj];
            turn(sensor_data, fabs(degrees_to_turn), clockwise);
            continue;
        }
        else
        {
            oi_setWheels(0, 0);
            continue;
        }

        return 0;
    }
}
