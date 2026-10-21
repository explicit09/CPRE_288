#include "stdio.h"
#include "../Lab8/clean.h"



int main(void)
{
    const int DATA_ELEMENTS = 91;
    float dist_data[DATA_ELEMENTS];
    int i = 0;

    for(i = 0; i<DATA_ELEMENTS; i++)
    {
        dist_data[i] = 100.0f; 
    }

    dist_data[46] = 200.0f;

    outlier_removal(dist_data);

    if(dist_data[45] == 100 && dist_data[46] == 100 && dist_data[47] == 100)
    {
        printf("PASS: The spike was removed.\n");
    }
    else
    {
        printf("FAIL: expected %.1f, got %.1f\n", 100.0f, dist_data[46]);
    }
    return 0;
}

