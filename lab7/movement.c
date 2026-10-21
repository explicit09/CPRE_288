#include "open_interface.h"

#include "stdbool.h"

bool bumped(oi_t *sensor)

{

    return sensor->bumpLeft || sensor->bumpRight;

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

    while ((sum > distance)) //while it is not bumped and there is still distance to travel

    {

        oi_update(sensor);

        sum += sensor->distance;

    }

    oi_setWheels(0, 0); // stop

}

//considering changing this to work for both clockwise and anti-clockwise, adding a bool to help out

void turn(oi_t *sensor, int degrees, bool clockwise)

{

    double deg = 0;

    if (clockwise)

    {

        oi_setWheels(-100, 100); //start turning

    }

    else

    {

        oi_setWheels(100, -100);

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

        turn(sensor, 90, 1); //only for roomba 12

        move_forward(sensor, turn_distance);

        turn(sensor, 90, 0);

    }

    else

    {

        move_backward(sensor, -150);

        turn(sensor, 90, 0);

        move_forward(sensor, turn_distance);

        turn(sensor, 90, 1);

    }

}

//void main()
//
//{
//
//    oi_t *sensor_data = oi_alloc();
//
//    oi_init(sensor_data);
//
////
//
//    const int total_distance = 2000;
//
//    const int reverse = 150;
//
//    const int turn = 250;
//
//    int distance_left;
//
//    int distance_moved = 0;
//
//    distance_left = total_distance - distance_moved;
//
//    //move_backward(sensor_data, -150);
//
//    while (distance_moved < total_distance)
//
//    {
//
//        distance_moved += move_forward(sensor_data, distance_left); //distance_left should also be modified inside the while loop
//
//        distance_left = total_distance - distance_moved; //updates the distance left
//
//        if (bumped(sensor_data))
//        {
//
//            //move_backward(sensor_data, reverse);
//
//            correction(sensor_data, turn);
//            move_forward(sensor_data, 150);
//
//        }
//
//    }
//
//    oi_free(sensor_data);
//
//}
//








