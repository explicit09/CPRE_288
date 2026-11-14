#include "inc/tm4c123gh6pm.h"
//#include "driverlib/interrupt.h" --->this is in a different library so no here in our code should we be using this
#include "Timer.h"
#include "servo.h"



//similar to ping but instead of capturing the pulse width we are generating it
//so skip the interrupts...?
//setting up and using PWM
volatile int M = 16000;


void servo_init(void)
{
//enable GPIO clock

    SYSCTL_RCGCGPIO_R |= 0x02;    // enables clock for GPIO port B (bit 1)
    GPIO_PORTB_DEN_R |= 0x20; // enables digital function for port 5 (PB5 output)
    GPIO_PORTB_PCTL_R &= ~0x00F00000;   // clears PB35
    GPIO_PORTB_PCTL_R |= 0x00700000; // selects T1CCP1 which is connected(PB5)

    //PB5 as output
    GPIO_PORTB_AFSEL_R |= 20; // disables alternate function for PB5 to use GPIO instead
    GPIO_PORTB_DIR_R |= 0x20; // puts PB5 as output so we can send trigger pulse to sensor

// enable timer clock  (using Timer 1B)
    SYSCTL_RCGCTIMER_R |= 0x02; // turn on both clock for timer 1
    TIMER1_CTL_R &= ~0x100;  //disables timer 1b
    TIMER1_CFG_R = 0x4; // 16 bits, split  --> splits timer 1 into timer1A timer1B
    TIMER1_TBMR_R = 0xA; //Timer 1b is periodic and PWM mode

    TIMER1_TBILR_R = 0xFFFF; // sets timer 1b to 16-bit value (max value)
    TIMER1_TBPR_R = 0xFF; // 8 bit prescale so combined with 16-bit to make 24 bit

//no interrupt since this is generating waves not detecting
//idk if timer match should go here or not??

    TIMER1_CTL_R |= 0x100;  //done with the setup so we can enable timer 1b

}


// move servo to desired position
float servo_move ()
    {
        unsigned int pulseWidth;
        unsigned int match;

        //turning 0 degrees to width
        pulseWidth = 16000;//high for 1ms is 0 degrees so 16000

        // calculate desired pulse width
        match = 320000-pulseWidth;

        //  update match register 1B
        TIMER1_TAMATCHR_R = match;//timer match value]

        /*NOT SURE IF THESE COME HERE OR SHOULD GO INTO THE INIT()
                   |
                   V                                            */
        TIMER1_TBPMR_R = 0x04;//
        //TIMER1_TBILR_R = 41855; //not needed because we are not doing interrupts?

        return match;
    }

