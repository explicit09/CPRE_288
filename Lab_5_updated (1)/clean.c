#include "clean.h"

int l = 0; // Index used to iterate through array of sensor data
float x = 0;
float y = 0;
float z = 0;
int window = 3;
float itself = 0;
float one = 0;
float two = 0;


void outlier_removal(float dist[91]);
{
    for (l = 0; l <= 90; l++)
    {
        x = dist[l]; //we chenaged from sensor_data_array to dist !
        if (l > 0)
        {
            y = dist[l - 1];
        }
        else
        {
            y = x;
        }

        if (l < 90)
        {
            z = dist[l + 1];
        }

        //x - cuurent
        //y - previous
        //z - next

        if (((x - y >= 50) && (x - z >= 50))
                || ((x - y <= -50) && (x - z <= -50)))
        {
            x = (y + z)/2; //returned this, add previous value plus forward value
            // y = z;
            // x = z;
            dist[l] = x;
            //dist[l - 1] = y;
        }
    }
}

void moving_average(char message2[], float dist[91])
{
    for (l = 0; l <= 90; l++)
    {
        itself = dist[l];
        if (l < 90)
            one = dist[l + 1];
        if (l < 89)
            two = dist[l + 2];

        itself = (itself + one + two) / window;
        dist[l] = itself;

        sprintf(message2, "%d\t\t%.1f\n", l * 2, itself);
        print_to_putty(message2);
    }
}