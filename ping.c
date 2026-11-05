#include "inc/tm4c123gh6pm.h"
#include "driverlib/interrupt.h"
#include "Timer.h"
#include "ping.h"


static volatile int rise = 0; // rising edge
static volatile int fall = 0;      // falling edge
static volatile int edgeCount = 0; 
static volatile int done = 0; // after both edges
static int overflows = 0;

//init
void ping_init(void) {
    // gpio
    SYSCTL_RCGCGPIO_R|= 0x02;                       
    GPIO_PORTB_DEN_R|= 0x08;                  
    GPIO_PORTB_PCTL_R &= ~0x0000F000;               
    GPIO_PORTB_PCTL_R|=  0x00007000;               
    
    //as output
    GPIO_PORTB_AFSEL_R &= ~0x08;   
    GPIO_PORTB_DIR_R|=  0x08; 

   
    GPIO_PORTB_DATA_R  &= ~0x08; // low

    // timer 3b
    SYSCTL_RCGCTIMER_R |= 0x08; //timer 3                     
    TIMER3_CTL_R &= ~0x100;  //tben=0                       
    TIMER3_CFG_R = 0x4;   // 16 bits, split                        
    TIMER3_TBMR_R = 0x07;   // tbmr = 3, tbcmr = 1                                                                        
    TIMER3_CTL_R|= 0xC00;  // tbevent = 11                     
    TIMER3_TBILR_R  = 0xFFFF;                      
    TIMER3_TBPR_R = 0xFF;                          
    TIMER3_ICR_R = 0x400;                         
    TIMER3_IMR_R |= 0x400;                         

    //interrupts
    IntRegister(INT_TIMER3B, TIMER3B_Handler);      
    NVIC_EN1_R |= 0x10;  // Timer 3B = IRQ 36 
    IntMasterEnable();                              

}

//trigger
void ping_trigger(void) {
   
    GPIO_PORTB_AFSEL_R &= ~0x08;   
    GPIO_PORTB_DIR_R |=  0x08; 
    
    GPIO_PORTB_DATA_R &= ~0x08;   

    timer_waitMicros(2);
    GPIO_PORTB_DATA_R |=  0x08;    // high

    timer_waitMicros(5);               
    GPIO_PORTB_DATA_R &= ~0x08;    // low 
}


//readinhg
int ping_read(void) {
    // timer disable and masking
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;

    edgeCount = 0;
    done = 0;

    // trigger
    ping_trigger();

    // pb3 = input
    GPIO_PORTB_DIR_R &= ~0x08;   // input
    GPIO_PORTB_AFSEL_R |=   0x08; 

    //clearing flag, interrupt and enabling time
    TIMER3_ICR_R = 0x400;
    TIMER3_CTL_R |= 0x100;
    TIMER3_IMR_R |= 0x400;

    // ISR working
    while (!done) {
        timer_waitMicros(100);
    }

    // pb3 = output after finsihed capturing
    TIMER3_IMR_R &= ~0x400;
    TIMER3_CTL_R &= ~0x100;

    GPIO_PORTB_AFSEL_R &= ~PB3_MASK;   
    GPIO_PORTB_DIR_R   |=  PB3_MASK;
    

    if (!done) return 0;  // nothing

    // Pulse width
    int width;
    width = g_rise - g_fall;
    if (width < 0) {
        width += += 0x1000000;
        overflows++;
    }
    return width;
}

// ISR

void TIMER3B_Handler(void) {
    if (TIMER3_MIS_R & 0x400) {                  
        TIMER3_ICR_R = 0x400;                    
        int t = TIMER3_TBR_R & 0xFFFFFF;    

        if (edgeCount == 0) {
            rise = t;
            edgeCount = 1;
        } else {
            fall = t;
            edgeCount = 0;
            done = 1;
        }
    }
}


float ping_cyclesToMs(int cycles) {
    return (cycles / 16000000.0f) * 1000.0f;
}

float ping_cyclesToCm(int cycles) {
    return (cycles / 16000000.0f) * 34000.0f / 2.0f;
}

int ping_getOverflowCount(void) {
    return overflows;
}