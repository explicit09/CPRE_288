/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Describtion: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"


int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the the LCD screen.  This also clears the screen. 




	char str[] = "Microcontrollers are lots of fun!";
	//int len = strlen(str);
	while (1) {   //to run indefinitely

	    int i =0;
	    int j = 19;

	    while(i <strlen(str) && j >= 0 )
	    {
	        lcd_setCursorPos(j,0);
	        lcd_putc(str[i]);
	        j--;
	        i++;
	    }


//	    for(i = 0; i < strlen(str); i++)  //lwn = 20
//	    {
//	        for (j = 19; j > 0; j--) //set the cursor at the rightmost position
//	        {
//	            lcd_setCursorPos(j,0);
//	            lcd_putc(str[i]);
//	        }
//
//
//
//
//	    }

	    //lcd_setCursorPos(19,0); //set the cursor at the right most coordinate
	    //lcd_puts("Microcontrollers are lots of fun!");
	}





//	variables we are using
//	char strArray [] = {Microcontrollers are lots of fun!};
//
//	while (*str && charnum < LCD_TOTAL_CHARS) {
//	        if (*str == '\n') {
//	            /* fill remainder of line with spaces */
//	            charnum += LCD_WIDTH - charnum % LCD_WIDTH;
//	        } else {
//	            lcd_putc(*str);
//	            charnum++;
//	        }
//
//	        str++;
	// Clear the LCD screen and print "Hello, world" on the LCD
	//lcd_printf("Microcontrollers are lots of fun!");

	//lcd_puts("Microcontrollers are lots of fun!");// Replace lcd_printf with lcd_puts
                                 // step through in debug mode
                                 // and explain to TA how it
                                 // works


    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
    // NOTE: For time fuctions see Timer.h

	return 0;
}
