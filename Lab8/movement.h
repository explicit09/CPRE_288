/*
 * movement.h
 *
 *  Created on: Sep 3, 2026
 *      Author: kausalya
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "open_interface.h"

void drive_mm(oi_t *sensor_data, int mm);
double move_forward(oi_t *sensor, double distance); //TO MOVE AHEAD
void move_backward(oi_t *sensor, double distance);
void turn(oi_t *sensor, int degrees, bool clockwise);
void correction(oi_t *sensor, int turn_distance);


#endif /* MOVEMENT_H_ */
