#include "modes.h"
#include "movement.h"
#include "scanner.h"
#include "clean.h"
#include "math.h"
#include "open_interface.h"

const int GO_MM = 15;
int clicked = 0;
int degrees_to_turn = 0;
int clockwise = 0;
int small2 = 0;
int store_small_obect = 0;

void autonomous(oi_t *sensor_data)
{
    int check_click = clicked % 2;
    
    if (sensor_data->bumpLeft || sensor_data->bumpRight)
    {
        correction(sensor_data, 150);
    }
    else if (!check_click)
    {
        scan_IR_PING();
        print_scan("** Raw data **\n", estimate);
        outlier_removal(estimate);
        moving_average(estimate);
        detect_object(estimate, &impp);
        print_scan("** Cleaned data **\n", estimate);
        print_objects(&impp);
    }
    else
    {
        small = find_smallest(&impp);
        point_to_smallest_obj(impp.angle[small]);
        clockwise = (impp.angle[small] < 90);
        degrees_to_turn = 85 - impp.angle[small];
        turn(sensor_data, fabs(degrees_to_turn), clockwise);
        drive_mm(sensor_data, (impp.dect[small] - 12) * 10);
    }
    clicked++;
}

void manual_drive(oi_t *sensor_data,int letter)
{
    if (letter == 'w')
    {
        drive_mm(sensor_data, GO_MM);
    }
    else if (letter == 's')
    {
        drive_mm(sensor_data, -GO_MM);
    }
    else if (letter == 'a')
    {
        turn(sensor_data, 90, 0);
    }
    else if (letter == 'd')
    {
        turn(sensor_data, 90, 1);
    }
    else if (letter == 'c')
    {
        clockwise = (impp.angle[small] < 90);
        degrees_to_turn = 90 - impp.angle[small];
        turn(sensor_data, fabs(degrees_to_turn), clockwise);
    }
    else if (letter == 'k')
    {
        correction(sensor_data, 150);
    }
    else
    {
        oi_setWheels(0, 0);
    }
}

void scan_360(oi_t *sensor_data)
{
    scan_IR_PING();
    outlier_removal(estimate);
    moving_average(estimate);
    detect_object(estimate, &impp);
    small = find_smallest(&impp);
    turn(sensor_data, 180, 1);
    scan_IR_PING();
    outlier_removal(estimate);
    moving_average(estimate);
    detect_object(estimate, &impp);
    small2 = find_smallest(&impp);

    if(impp.angle[small] < impp.angle[small2])
    {
        point_to_smallest_obj(small);
    }
    else 
    {
        point_to_smallest_obj(small2);
    }
}