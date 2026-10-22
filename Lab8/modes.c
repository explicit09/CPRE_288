#include "modes.h"
#include "movement.h"
#include "scanner.h"
#include "clean.h"

const int GO_MM = 15;
int clockwise = 0;
int small = 0;
int degrees_to_turn = 0;

void autonomous(oi_t *sensor_data)
{
    int check_click = clicked % 2;
    if (!check_click)
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
    else
    {
        oi_setWheel(0, 0);
    }
}