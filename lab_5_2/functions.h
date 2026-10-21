#include "cyBot_uart.h"
#include "string.h"
 #include "cyBot_Scan.h"
 #include "open_interface.h"
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct{
    // float dist;
    double dect[10];
    double width[10];
    int angle[10];
    int obj;
//    int start[10];
//    int end[10];
}dataa;


void print_to_putty(char message[]);
void point_to_smallest_obj(int smallest_obj_angle);
dataa detect_object(float distance[], double detect[], double width[], int angle[], int obj, dataa data);
void move_cyobot(int letter, int degrees);


#endif 
