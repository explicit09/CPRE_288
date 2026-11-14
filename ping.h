#ifndef PING_H_
#define PING_H_

#include "inc/tm4c123gh6pm.h"
#include "driverlib/interrupt.h"
#include "Timer.h"
#include "ping.h"

void ping_init(void);
void ping_trigger(void);
int ping_read(void);
float ping_cyclesToMs(int cycles);
float ping_cyclesToCm(int cycles);
int ping_getOverflowCount(void);
void TIMER3B_Handler(void);

#endif 