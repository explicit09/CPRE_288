#include "stdio.h"
#include "stdlib.h"
#include "../Lab8/cyBot_Scan.h"
#include "../Lab8/uart.h"

void cyBOT_Scan(int angle, cyBOT_Scan_t* getScan)
{
    puts("FAIL: test uses hardware");
    exit(1);
}

void uart_sendChar(char data)
{
    // puts("FAIL: test uses hardware");
    // exit(1);
    putchar(data);
}

