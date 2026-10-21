#include "functions.h"
#include "open_interface.h"
#include "math.h"

//intializations for detecting objs
int a;
int obj = 0;
int i = 0;
// cyBOT_Scan_t scan;
int display = 0;


void print_to_putty(char message[])
{
    cyBot_sendByte('\r');
    //cyBot_sendByte('\n');
    for (display = 0; display < strlen(message); display++)
    {
        cyBot_sendByte(message[display]);
    }
}

dataa detect_object(float distance[], double detect[], double width[], int angle[], int obj, dataa data1)
{
    double diff_forward;
    double diff_backward;
    double end_d[10];
    double end[10];
    double start[10];
    obj = 0;


    for (i = 1; i <= 89; i++) //detects the objects --> we already used i so changing to q
    {
        diff_forward = distance[i - 1] - distance[i];
        diff_backward = distance[i + 1] - distance[i];
        if (distance[i] < 300)
        {
            if (diff_forward > 50)
            {
                obj++;
                start[obj] = i * 2;
                //start distance; one side of the triangle
                detect[obj] = distance[i]; //so this dist looks into the data after we have objects detected - changing to dect
            } 

            if (diff_backward > 50)
            {
                end[obj] = i * 2;
                angle[obj] = (end[obj] + start[obj]) / 2;
                end_d[obj] = distance[i]; //otehr side of the triangle    
            }

            //why is this inside the loop 
            width[obj] = end[obj] - start[obj];
            width[obj] = sqrt(
                    pow(end_d[obj], 2) + pow(detect[obj], 2)
                            - (2 * end_d[obj] * detect[obj]
                                    * cos(width[obj] * (M_PI / 180))));

            data1.obj = obj;
            data1.angle[obj] =  angle[obj];
            data1.width[obj] = width[obj];
            data1.dect[obj] = detect[obj];
            
        }
    }
    return data1;
}

// void point_to_smallest_obj(int smallest_obj_angle)
// {
//     cyBOT_Scan(smallest_obj_angle, &scan);
// }

//void move_cyobot(int letter) //come to finish this, I hate the declaraction of letter inside the function
//{
//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//    letter = cyBot_getByte();
//    if (letter == 'w'){   // w forward
//        oi_setWheels(100, 100);
//    }
//    else if (letter == 's'){ // s go back
//        oi_setWheels(-100, -100);
//    }
//    else if (letter == 'a'){ // a turn left
//        turn(sensor_data, 90, 0);
//        oi_setWheels(100, 100);
//    }
//    else if (letter == 'd'){ // d turn right
//        turn(sensor_data, 90, 1);
//        oi_setWheels(100, 100);
//    }
//    else{
//        oi_setWheels(0, 0);
//    }
//}
