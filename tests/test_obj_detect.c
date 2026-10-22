#include "stdio.h"
#include "../Lab8/functions.h"
#include "../Lab8/clean.h"
#include "data-w-cybot1.h"

dataa obj_data;
cyBOT_Scan_t scan;

int main(void)
{
    // outlier_removal(sensor_data_array);
    // moving_average(sensor_data_array);
    detect_object(sensor_data_array, &obj_data);
    
    print_objects(&obj_data);
}