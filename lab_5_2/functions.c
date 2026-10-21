#include "functions.h"
#include "open_interface.h"
#include "math.h"
#include "movement.h"

//intializations for detecting objs
int a;
int obj = 0;
int i = 0;
cyBOT_Scan_t scan;
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

dataa detect_object(float distance[], double detect[], double width[],
                    int angle[], int obj, dataa data1)
{
    double diff_forward;
    double diff_backward;
    double end_d[5] = { 0 };
    double end[5] = { 0 };
    double start[5] = { 0 };
    obj = 0;
    int another_counter = 1;
    dataa temp_data;

    for (i = 1; i <= 89; i++) //detects the objects
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
                if (!end[obj])
                {
                    end[obj] = i * 2;
                    angle[obj] = (end[obj] + start[obj]) / 2;
                    end_d[obj] = distance[i]; //otehr side of the triangle
                    width[obj] = end[obj] - start[obj];
                    width[obj] = sqrt(
                            pow(end_d[obj], 2) + pow(detect[obj], 2)
                                    - (2 * end_d[obj] * detect[obj]
                                            * cos(width[obj] * (M_PI / 180))));

                    data1.obj = obj;
                    data1.angle[obj] = angle[obj];
                    data1.width[obj] = width[obj];
                    data1.dect[obj] = detect[obj];
                }
            }

            //why is this inside the loop

        }

    }

//    for (i = 0; i < 10; i++)
//    {
//        if (temp_data.angle[i] >= 0 && temp_data.angle[i] < 180)
//        {
//            data1.angle[another_counter] = temp_data.angle[i];
//            data1.width[another_counter] = temp_data.width[i];
//            data1.dect[another_counter] = temp_data.dect[i];
//            another_counter++;
//        }
//        data1.obj = another_counter;
//    }
    return data1;
}

void point_to_smallest_obj(int smallest_obj_angle)
{
    cyBOT_Scan(smallest_obj_angle, &scan);
}

void move_cyobot(int letter, int degrees) //come to finish this, I hate the declaraction of letter inside the function
{
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    int clockwise = 0;
    int degrees_to_turn = 90 - degrees;
    letter = cyBot_getByte();
    if (letter == 'w')
    {   // w forward
        oi_setWheels(100, 100);
    }
    else if (letter == 's')
    { // s go back
        oi_setWheels(-100, -100);
    }
    else if (letter == 'a')
    { // a turn left
        turn(sensor_data, 90, 0);
        oi_setWheels(100, 100);
    }
    else if (letter == 'd')
    { // d turn right
        turn(sensor_data, 90, 1);
        oi_setWheels(100, 100);
    }
    else if (letter == 'c')
    { // d turn right
        if (degrees < 90)
        {
            clockwise = 1;
        }
        turn(sensor_data, fabs(degrees_to_turn), clockwise);
    }
    else
    {
        oi_setWheels(0, 0);
    }

}
