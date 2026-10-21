//#include "lcd.h"
//#include "movement.h"
//#include "open_interface.h"
//#include "Timer.h"
//#include "cyBot_Scan.h"
//#include "cyBot_uart.h"
//#include "string.h"
//#include "math.h"
//#include "stdio.h"
//#include "functions.h"
//#include "clean.h"
//#include "movement.h"
//
///// for roomba 12
//
//int main(void)
//{ //initialize the UART function
//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//
//    cyBot_uart_init();
//    timer_init();
//    cyBOT_init_Scan(0b0111);
//    lcd_init();
//    right_calibration_value = 227500;
//    left_calibration_value = 1282750;
//
//    int meters;
//    int putty;
//    char message[50];
//    float dist[91];
//    char *header;
//    double width_[10];
//    double dect[10];
//    int angle_[10];
//    int a = 0;
//    int obj1 = 0;
//    dataa impp;
//    int clockwise = 0;
////    int degrees = 0;
//    int small_obj = 0;
//    int degrees_to_turn;
//
//    cyBOT_Scan_t scan;
//
//    //  int letter = cyBot_getByte();
//    //char message[100] = "";
//
//    while (1)
//    {
//
//        int letter = cyBot_getByte();
//        if (letter == 'w')
//        { //w forward
//            oi_setWheels(100, 100);
//        }
//        else if (letter == 's')
//        { //s go back
//            oi_setWheels(-100, -100);
//        }
//        else if (letter == 'a')
//        { //a turn left
//            turn(sensor_data, 90, 0);
//            oi_setWheels(100, 100);
//        }
//        else if (letter == 'd')
//        { //d turn right
//            turn(sensor_data, 90, 1);
//            oi_setWheels(100, 100);
//        }
//        else if (letter == 'c')
//        {
//            if (impp.angle[small_obj] < 90)
//            {
//                clockwise = 1;
//            }
//            degrees_to_turn = 90 - impp.angle[small_obj];
//            turn(sensor_data, fabs(degrees_to_turn), clockwise);
//        }
//        else if (letter == 'm')
//        {
//            oi_setWheels(0, 0);
//            for (meters = 0; meters <= 180; meters += 2) //scans 180 and records dist as it goes
//            {
//                cyBOT_Scan(meters, &scan);
//                dist[meters / 2] = scan.sound_dist;
//            }
//            //     for (meters = 0; meters <= 90; meters++)
//            //     {
//            //         dist[meters] = sensor_data_array[meters];
//            //     }
//
//            header = "\nDegrees\t\tDistance (cm)\n";
//            char title1[] = "** Raw noisy sensor data **\n";
//
//            print_to_putty(title1);
//            print_to_putty(header);
//            //         printf("%s", title1);
//            //         printf("%s", header);
//
//            for (putty = 0; putty < 91; putty++) //printing message
//            {
//                sprintf(message, "%d\t\t%.1f\n", putty * 2, dist[putty]);
//                print_to_putty(message);
//                //             printf("%s", message);
//            }
//
//            //=====================================================================================
//            //noiseless cleaning algo
//
//            // Iterates through an array of sensor data, and prints the values.
//            // Note: Consider updating code so that max index (l)
//            // automatically matches the number of elements in
//            // sensor_data_array
//
//            char title2[] = "** Cleaned data **\n";
//            print_to_putty(title2);
//            print_to_putty(header);
//            //         printf("%s", title2);
//            //         printf("%s", header);
//
//            //remove outliers
//            outlier_removal(dist);
//
//            ///sliding window
//            char message2[50];
//            moving_average(dist);
//
//            for (putty = 0; putty < 91; putty++) //printing message
//            {
//                sprintf(message2, "%d\t\t%.1f\n", putty * 2, dist[putty]);
//                print_to_putty(message2);
//                //             printf("%s", message2);
//            }
//
//            //=========================================================================================
//
//            impp = detect_object(dist, dect, width_, angle_, obj1, impp);
//
//            int k;
//            double min = 100;
//            int small_obj;
//            for (k = 1; k < impp.obj + 1; k++)
//            {
//                if (impp.width[k] < min)
//                {
//                    min = impp.width[k];
//                    small_obj = k;
//                }
//            }
//
//            char title3[] = "Object#\tAngle\tDistance\tWidth\n";
//            char message3[50];
//
//            print_to_putty(title3);
//            //         printf("%s\n", title3);
//            // printf("%d\n", impp.obj);
//            for (a = 1; a <= impp.obj; a++)
//            {
//                sprintf(message3, "%d\t%d\t%.1f\t\t%.1f\n", a, impp.angle[a],
//                        impp.dect[a], impp.width[a]);
//                print_to_putty(message3);
//                //             printf("%s", message3);
//            }
//
//            point_to_smallest_obj(impp.angle[small_obj]);
//            sprintf(message3, "The smallest object is %d",
//                    impp.angle[small_obj]);
//            print_to_putty(message3);
//            continue;
//        }
//
//        else
//        {
//            oi_setWheels(0, 0);
//        }
//
//        return 0;
//    }
//}
