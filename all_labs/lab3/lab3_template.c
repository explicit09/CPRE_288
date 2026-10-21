/**
 * lab3_template.c
 * 
 * Template file for CprE 288 lab 3
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "cyBot_uart.h"
#include "stdio.h"// Functions for communiticate between CyBot and Putty (via UART)
                         // PuTTy: Buad=115200, 8 data bits, No Flow Control, No Party,  COM1

//#warning "Possible unimplemented functions"
//#define REPLACEME 0



int main(void) {
    oi_t *sensor_data =  oi_alloc();
    oi_init(sensor_data);


	button_init();
	lcd_init();
	            // Don't forget to initialze the cyBot UART before trying to use it
	
	// YOUR CODE HERE
	
	cyBot_uart_init();

	int button;
	char message;
	
	while(1)
	{
	
      // YOUR CODE HERE

	    button = button_getButton();
	    message = button;


//	    sprintf(message, button);
//	    lcd_puts(message);

	    lcd_printf("%d", button);


	    cyBot_sendByte(message + 48);//orginally we forgot to add the %

	}
	return 0;
	
}
