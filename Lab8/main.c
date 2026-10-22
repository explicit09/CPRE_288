//#include "common.h"
//#include "movement.h"
//#include "stdio.h"
//#include "math.h"
//#include "functions.h"
//#include "clean.h"
//#include "init.h"
//#include "scanner.h"
//
//dataa impp;
//float dist[91];
//float estimate[91];
//int ir[91];
//int clicked = 0;
//int clockwise = 0;
//int degrees_to_turn = 0;
//int small = 0;
//
//int main(void)
//{
//    init();
//
//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//
//    cyBOT_Scan_t scan;
//    int letter;
//
//    char message[50];
//    while (1)
//    {
//        int i;
//        letter = uart_receive();
//
//        if (letter == 'm') // scan, clean, find objects, point at the smallest
//        {
//            scan_IR_PING();                                        // same scanning mechanism from before
//            print_scan("** Raw noisy sensor data **\n", estimate); // print_scan is another function just to make our loves easier with printing these titles
//
//            // data cleaning
//            outlier_removal(estimate);
//            outlier_removal(dist);
//
//            moving_average(estimate);
//            moving_average(dist);
//
//            print_scan("** Cleaned data **\n", estimate);
//            print_scan("** Cleaned data **\n", dist);
//
//            detect_object(estimate, &impp);
//            print_objects(&impp); // another function, to print the required data about objetcs, more deatiled i have in functions.c
//
//            for (i = 0; i < impp.obj; i++)
//            {
//                cyBOT_Scan(impp.angle[i + 1], &scan);
//                timer_waitMillis(1000);
//                point_to_smallest_obj(impp.angle[i]);
//                // impp.dect[i+1] = scan.sound_dist;
//            }
//
//            small = find_smallest(&impp);
//            point_to_smallest_obj(impp.angle[small]);
//            print_objects(&impp);
//
//            clockwise = (impp.angle[small] < 90); // if false, == 0, or not 0
//            degrees_to_turn = 85 - impp.angle[small];
//            turn(sensor_data, fabs(degrees_to_turn), clockwise);
//
//            // move ahead untill dist <=5cm
//            drive_mm(sensor_data, (impp.dect[small] - 12) * 10);
//
//            scan_IR_PING();
//            detect_object(estimate, &impp);
//            print_objects(&impp);
//            small = find_smallest(&impp);
//            point_to_smallest_obj(impp.angle[small]);
//            sprintf(message, "The smallest is %d\n", small);
//            print_to_putty(message);
//        }
//    }
//
//    return 0;
//}
