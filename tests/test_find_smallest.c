#include "stdio.h"
#include "../Lab8/functions.h"

int test_no_objects(void);
int test_objects(void);

int main(void)
{
 
    int i = test_objects();
    int j = test_no_objects(); 
    if(i + j > 0)
    {
        return 1;
    }
    return 0;
}

int test_no_objects(void)
{
    dataa sample = {0};
    sample.obj = 0;

    int expected = 0;
    int actual = find_smallest(&sample);

    if(expected == actual)
    {
        printf("PASS: no objects returns index 0\n");
    }
    else
    {
        printf("FAIL: expected index is %d, got %d\n", expected, actual);
        return 1;
    }
    return 0;
}

int test_objects(void){
    dataa sample = {0};
    sample.obj = 3;
    sample.width[1] = 14.0;
    sample.width[2] = 6.0;
    sample.width[3] = 8.0;

    int expected = 2;
    int actual = find_smallest(&sample);

    if(expected == actual)
    {
        printf("PASS: narrowest of three objects selected\n");
    }
    else
    {
        printf("FAIL: expected index is %d, got %d\n", expected, actual);
        return 1;
    }
    return 0;
}