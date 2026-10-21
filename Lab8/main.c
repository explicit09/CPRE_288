#include "common.h"
#include "movement.h"
#include "stdio.h"
#include "math.h"
#include "functions.h"
#include "clean.h"
#include "init.h"

float dist[91];
int ir[91];
float estimate[91];
dataa impp;

int main(void)
{
    init();

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    cyBOT_Scan_t scan;
    int letter;
    int meters;
    int clockwise = 0;
    int degrees_to_turn;
    int avg = 0;
    int sum = 0;
    int small = 0;
    int scan2 = 0;
    char message[50];

    while (1)
    {
        letter = uart_receive();

        if (letter == 'm') // scan, clean, find objects, point at the smallest
        {
            // same as before, populating our dist array
            for (meters = 0; meters <= 180; meters += 2)
            {
                cyBOT_Scan(meters, &scan);          // scane 180
                dist[meters / 2] = scan.sound_dist; // from ping sensor
                for (avg = 0; avg < 3; avg++)
                {

                    cyBOT_Scan(meters, &scan); // multiple scans with taking avg of IR
                    sum += scan.IR_raw_val;
                }
                sum /= 3;
                ir[meters / 2] = sum; // it will return -1 if not enabled
                sum = 0;

                estimate[meters / 2] = (4.80028 * pow(10, -12)) * pow(ir[meters / 2], 4) - (4.96639 * pow(10, -8)) * pow(ir[meters / 2], 3) + (0.000194691) * pow(ir[meters / 2], 2) - (0.350156 * ir[meters / 2]) + 260.87977;
            }

            // print_scan is another function just to make our loves easier with printing these titles
            print_scan("** Raw noisy sensor data **\n", estimate);

            outlier_removal(estimate);
            moving_average(estimate);
            print_scan("** Cleaned data **\n", estimate);

            detect_object(estimate, &impp);

            print_objects(&impp); // another function, to print the required data about objetcs, more deatiled i have in functions.c
            int i;
            for (i = 0; i < impp.obj; i++)
            {
                cyBOT_Scan(impp.angle[i + 1], &scan);
                timer_waitMillis(1000);
                point_to_smallest_obj(impp.angle[i]);
                // impp.dect[i+1] = scan.sound_dist;
            }

            outlier_removal(dist);
            moving_average(dist);
            print_scan("** Cleaned data **\n", dist);

            small = find_smallest(&impp);
            point_to_smallest_obj(impp.angle[small]);

            print_objects(&impp);

            // drive

            // turn the cybot itsekf
            // turn to the smallest object
            clockwise = (impp.angle[small] < 90); // if false, == 0, or not 0
            degrees_to_turn = 90 - impp.angle[small];
            turn(sensor_data, fabs(degrees_to_turn), clockwise);

            // move ahead untill dist <=5cm
            drive_mm(sensor_data, (impp.dect[small] - 6) * 10);

            // scan again to point the sensor

            //             for( scan2 = 0; scan2<= 180; scan2+=2)
            //             {
            //                 cyBOT_Scan(scan2, &scan);
            //                 dist[scan2 / 2] = scan.sound_dist;
            //
            //
            //
            //             }
        }
    }

    return 0;
}
