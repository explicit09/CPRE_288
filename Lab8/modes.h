#pragma once
#include "functions.h"
#include "open_interface.h"

extern dataa impp;
extern float estimate[91];
extern int clicked;
extern int clockwise;
extern int small;
extern int degrees_to_turn;

void autonomous(oi_t *sensor_data);
void manual_drive(oi_t *sensor_data,int letter);
