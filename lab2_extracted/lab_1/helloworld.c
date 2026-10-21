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

#define LCD_WIDTH 20  //taken from lcd.c

char text[] = "!"; //

void shiftLeft(char display[]);
void onLCD(char display[]);

int main(void)
{

    char display[LCD_WIDTH + 1]; //the char array that will be displayed on the screen

    int i;
    int len;

    timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called
                  // and enables time functions (e.g. timer_waitMillis)

    lcd_init(); // Initialize the the LCD screen.  This also clears the screen.

    len = strlen(text);

    while (1) //to run indefinitely
    {
        for (i = 0; i < LCD_WIDTH; i++) //to start with a blank screen
        {
            display[i] = ' '; //padding the array with 20 spaces to start with an empty screen
        }

        display[LCD_WIDTH] = '\0';

        onLCD(display); //displaying the char from the leftmost corner of the lcd

        for (i = 0; i < len; i++) //to print from the right
        {
            shiftLeft(display); //moving everything left
            display[LCD_WIDTH - 1] = text[i]; //filling the char with the text, from the right

            onLCD(display);

            timer_waitMillis(300);
        }

        for (i = 0; i < LCD_WIDTH; i++) //to insert spaces after text is done
        {
            shiftLeft(display);

            display[LCD_WIDTH - 1] = ' '; //padding with spaces

            onLCD(display);

            timer_waitMillis(300);
        }

        timer_waitMillis(300);

    }

    return 0;
}

// Clear the LCD screen and print "Hello, world" on the LCD
//lcd_printf("Microcontrollers are lots of fun!");

//lcd_puts("Microcontrollers are lots of fun!");// Replace lcd_printf with lcd_puts
// step through in debug mode
// and explain to TA how it
// works

// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
// NOTE: For time fuctions see Timer.h

void shiftLeft(char display[]) //changes the array elements to the left
{
    int i;
    for (i = 0; i < LCD_WIDTH - 1; i++) //repeats 19 times, but the last element is not changed
    {
        display[i] = display[i + 1];
    }
}

void onLCD(char display[]) //displays 20 chars on the lcd
{
    lcd_setCursorPos(0, 0); //starts from the leftmost corner
    lcd_puts(display);
}
