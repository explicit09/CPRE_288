#ifndef SERVO_H_
#define SERVO_H_

#include "inc/tm4c123gh6pm.h"
#include "driverlib/interrupt.h"
#include "Timer.h"
#include "servo.h"

void servo_init(void);
float servo_move();

#endif 
