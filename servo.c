#include "Timer.h"
#include "servo.h"

int current_match = 296000;   // 90 degreeas
int match_0 = 304000;
int match_180  = 288000;

void write_match(int match) 
{
    TIMER1_TBMATCHR_R = match & 0xFFFF;   // lower 16 bits to MATCH
    TIMER1_TBPMR_R = match >> 16; // upper 8 bits to prescale
}

void servo_init(void)
{
    //portb and timer1
    SYSCTL_RCGCGPIO_R |= 0x02;
    SYSCTL_RCGCTIMER_R |= 0x02;

    // PB5 function 7
    GPIO_PORTB_DEN_R|= 0x20;
    GPIO_PORTB_DIR_R|= 0x20;
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R &= ~0x00F00000;
    GPIO_PORTB_PCTL_R|=  0x00700000;

    // timer1B = PWM
    TIMER1_CTL_R &= ~0x100;      
    TIMER1_CFG_R = 0x4;  // 16-bit 
    TIMER1_TBMR_R    = 0xA; // PWM mode and periodic
    TIMER1_CTL_R &= ~0x4000;  

    // start value 
    TIMER1_TBPR_R = 320000 >> 16;
    TIMER1_TBILR_R = 320000 & 0xFFFF;

    write_match(current_match);
    TIMER1_CTL_R |= 0x100;   

    timer_waitMillis(1000);  
}

int servo_set_match(int match) //to wait for appropriate amt of time 
{
    int diff = match - current_match;
    if (diff < 0) diff = -diff;

    write_match(match);
    current_match = match;

    timer_waitMillis(diff / 16 + 20);   //waiting patienlty  
    return 1;  // if returned 1, servo has reached its destined angle!
}


int servo_move(float degrees)
{
    if (degrees < 0) degrees = 0;
    if (degrees > 180) degrees = 180;

    int match = (int)(match_0 + degrees * (match_180 - match_0) / 180.0);
    return servo_set_match(match);
}



int servo_get_match(void)
{
    return current_match;
}