#include "clean.h"
#include "string.h"
#include "functions.h"
#include "stdio.h"
#include "math.h"

int l = 0; // Index used to iterate through array of sensor data
float x = 0;
float y = 0;
float z = 0;
int window = 3;
float itself = 0;
float one = 0;
float two = 0;


void outlier_removal(float distance[])
{
    distance[0] = (distance[1] + distance[2]) / 2.0;
    for (l = 1; l < 90; l++)
    {
        x = distance[l]; //we chenaged from sensor_data_array to dist !      
        y = distance[l - 1];
        z = distance[l + 1];
 
        //x - current
        //y - previous
        //z - next

        if (((x - y >= 50) && (x - z >= 50))
                || ((x - y <= -50) && (x - z <= -50)))
        {
            distance[l] = (y + z)/2.0; //returned this, add previous value plus forward value

        }
    }
}



void moving_average(float distance[])
{
    float temp_distance[91];
    temp_distance[89] = distance[89];
    temp_distance[90] = distance[90];

    for (l = 0; l <= 90; l++)
    {
        itself = distance[l];
        if (l < 90)
            one = distance[l + 1];
        if (l < 89)
            two = distance[l + 2];

        if (fabsf(one - itself) >= 50)
            one = itself;

        if (fabsf(two - itself) >= 50)
            two = itself;
        
        temp_distance[l] = (itself + one + two) / window;
        distance[l] = temp_distance[l];

    }
}
