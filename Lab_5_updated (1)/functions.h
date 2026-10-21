#include "cyBot_uart.h"
#include "string.h"
#include "cyBot_Scan.h"
#include "open_interface.h"

int display = 0;


void print_to_putty(char message[]);
void point_to_smallest_obj(int smallest_obj_angle);
void move_cyobot();
