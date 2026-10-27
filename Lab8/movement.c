#include "open_interface.h"
#include "stdbool.h"

bool bumped(oi_t *sensor)
{
    return sensor->bumpLeft || sensor->bumpRight;
}

void drive_mm(oi_t *sensor_data, int mm)
{
    double sum = 0;
    int speed;

    if(mm> 0) speed = 100;
    else speed = -100;

    oi_setWheels(speed, speed);
    while (!bumped(sensor_data) && fabs(sum) < fabs((double) mm))
    {
        oi_update(sensor_data);
        sum += sensor_data->distance;
    }
    oi_setWheels(0, 0);
}

double move_forward(oi_t *sensor, double distance)
{
    double sum = 0.0;

    oi_setWheels(96, 100); // move forward; at 100 mm/s

    while (!bumped(sensor) && (sum < distance))
    {
        oi_update(sensor);
        sum += sensor->distance;
    }

    oi_setWheels(0, 0); // stop
    return sum;
}

void move_backward(oi_t *sensor, double distance)
{
    double sum = 0.0;

    oi_setWheels(-100, -100); // move BACKWARD; at 100 mm/s

    while ((sum > distance)) // while it is not bumped and there is still distance to travel
    {
        oi_update(sensor);
        sum += sensor->distance;
    }

    oi_setWheels(0, 0); // stop
}

// considering changing this to work for both clockwise and anti-clockwise, adding a bool to help out
void turn(oi_t *sensor, int degrees, bool clockwise)
{
    double deg = 0;
    if (clockwise)
    {
        oi_setWheels(-80, 100); // start turning
    }
    else
    {
        oi_setWheels(80, -100);
    }

    while (deg < degrees)
    {
        oi_update(sensor);
        deg += fabs(sensor->angle);
    }
    
    oi_setWheels(0, 0); // stop
}

void correction(oi_t *sensor, int turn_distance)
{
    if (sensor->bumpLeft)
    {
        move_backward(sensor, -150);
        turn(sensor, 10, 1);
        move_forward(sensor, turn_distance);
        turn(sensor, 10, 0);
    }
    else
    {
        move_backward(sensor, -150);
        turn(sensor, 10, 0);
        move_forward(sensor, turn_distance);
        turn(sensor, 10, 1);
    }
}
