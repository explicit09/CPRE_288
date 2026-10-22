#include "stdio.h"
#include "../Lab8/functions.h"
#include "sensor-data-2.h"

dataa obj_data;

int main(void)
{
    detect_object(sensor_data_array, &obj_data);

    print_objects(&obj_data);
}