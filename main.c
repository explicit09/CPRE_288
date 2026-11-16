#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include "button.h"

int main(void)
{
    //1
    lcd_init();
    servo_init(); //going to 90 degres

    lcd_printf("Moving to 0");
    servo_set_match(304000); 
    lcd_printf("At 0: 304000");

    while (1) {}


    //2
    float angle = 90;
    int direction = 1; //if 1= go clockwise, -1 = anticlockwise

    lcd_init();
    button_init();
    servo_init();
    servo_move(angle);
    lcd_printf("match: %d\n", servo_get_match());

    while (1)
    {
        int button = button_getButton();

        if (button == 1) angle += direction * 1;
        else if (button == 2)     angle += direction * 5;
        else if (button == 3) direction = -direction;
        else if (button == 4) 
        {
            if (direction == 1) {
                angle = 180;
            }
            else if{
                angle = 0;
            }
        }

        if (angle > 180)    angle = 180;
        if (angle < 0) angle = 0;

        if (button != 0)
        {
            servo_move(angle);

            
            if (direction == 1)
                lcd_printf("match: %d\ntoward higher",    servo_get_match());
            else
                lcd_printf("match: %d\ntoward lower", servo_get_match());


            timer_waitMillis(200);  
        }
    }
}