#pragma once
#include "functions.h"
#include "open_interface.h"

extern dataa impp;
extern float estimate[91];
extern int clicked;

void autonomous(oi_t *sensor_data);
