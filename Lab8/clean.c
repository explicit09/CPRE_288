#include "clean.h"
#include "string.h"
#include "functions.h"
#include "stdio.h"
#include "math.h"

//int l = 0; // Index used to iterate through array of sensor data
float x = 0;
float y = 0;
float z = 0;
int window = 3;
float itself = 0;
float one = 0;
float two = 0;

float left = 0.0;
float right = 0.0;


void outlier_removal(float distance[])
{
    int l = 0;
    //added an if condition of when to modify distance[0]
    if(fabsf(distance[0] - distance[1]) >= 20
            && fabsf(distance[1] - distance[2]) < 20)
            {
                distance[0] = distance[1];
            }
    
    for (l = 1; l < 90; l++) 
    {
        x = distance[l]; //we chenaged from sensor_data_array to dist !      
        y = distance[l - 1];
        z = distance[l + 1];
 
        //x - current
        //y - previous
        //z - next

        if (((x - y >= 20) && (x - z >= 20))
                || ((x - y <= -20) && (x - z <= -20)))
        {
            //distance[l] = (y + z)/2.0; //returned this, add previous value plus forward value
            //using max and min values
            if (x > y)
            {
                distance[l] = fmaxf(y,z);
            }
            else{
                distance[l] = fminf(y,z);
            }
        }
    }

    if (fabsf(distance[90] - distance[89]) >= 20
            && fabsf(distance[89] - distance[88])
                    < 20)
        distance[90] = distance[89];
}



void moving_average(float distance[])
{
    float temp[91];
    int l;

    for (l = 0; l < 91; l++)
    {
        float itself = distance[l];

        if( l >0)
        {
            left = distance[l-1];
        }
        else{
            left = itself;
        }

        if( l < 90)
        {
            right = distance[l+1];
        }
        else{
            right = itself;
        }
       
        if (fabsf(left - itself) >= 20)
            left = itself;
        if (fabsf(right - itself) >= 20)
            right = itself;

        temp[l] = (left + itself + right) / 3.0f;
        distance[l] = temp[l];
    }
        
    }

