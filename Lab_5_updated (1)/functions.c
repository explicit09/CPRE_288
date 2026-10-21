#include "functions.h"

//intializations for detecting objs
double start[10];
double end[10];
double width[10];
double dect[10];
double end_d[10];
int angle[10];
int a;
int obj = 0;
int i = 0;


void print_to_putty(char message[])
{
    cyBot_sendByte('\r');
    //cyBot_sendByte('\n');
    for (display = 0; display < strlen(message); display++)
    {
        cyBot_sendByte(message[display]);
    }
}

void detect_object(float dist[])
{
    double diff_forward;
    double diff_backward;

    for (i = 1; i <= 89; i++) //detects the objects --> we already used i so changing to q
    {
        diff_forward = dist[i - 1] - dist[i];
        diff_backward = dist[i + 1] - dist[i];
        if (dist[i] < 300)
        {
            if (diff_forward > 50)
            {
                obj++;
                start[obj] = i * 2;
                //start distance; one side of the triangle
                dect[obj] = dist[i]; //so this dist looks into the data after we have objects detected - changing to dect
            } 

            if (diff_backward > 50)
            {
                end[obj] = i * 2;
                angle[obj] = (end[obj] + start[obj]) / 2;
                end_d[obj] = dist[i]; //otehr side of the triangle    
            }

            //why is this inside the loop 
            //width[obj] = end[obj] - start[obj];
            width[obj] = sqrt(
                    pow(end_d[obj], 2) + pow(dect[obj], 2)
                            - (2 * end_d[obj] * dect[obj]
                                    * cos(width[obj] * (M_PI / 180))));
        }
    }
}

void point_to_smallest_obj(int smallest_obj_angle)
{
    cyBOT_Scan(smallest_obj_angle, &scan);
}

void move_cyobot(int letter) //come to finish this, I hate the declaraction of letter inside the function
{
    letter = cyBot_getByte();
    if (letter == 'w'){   // w forward
        oi_setWheels(100, 100);
    }
    else if (letter == 's'){ // s go back
        oi_setWheels(-100, -100);
    }
    else if (letter == 'a'){ // a turn left
        turn(sensor_data, 90, 0);
        oi_setWheels(100, 100);
    }
    else if (letter == 'd'){ // d turn right
        turn(sensor_data, 90, 1);
        oi_setWheels(100, 100);
    }
    else{
        oi_setWheels(0, 0);
    }
}
