/*
 * adc.c
 *
 *  Created on: Oct 22, 2026
 *      Author: nkantner
 */
#include "adc.h"
#include "Timer.h"
#include <inc/tm4c123gh6pm.h>

void adc_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0b00000010; //port b
    //ENABLE ADC CLOCK
    SYSCTL_RCGCADC_R |= 0b10; // clock for ADC registers
    GPIO_PORTB_AFSEL_R |= 0b00010000; //pb4
    GPIO_PORTB_DIR_R = (GPIO_PORTB_DIR_R & ~0x01) | 0x02; // 1 = out; 0 = in
    GPIO_PORTB_DEN_R &= ~0x10; // pb4 = digital function disabled
    GPIO_PORTB_AMSEL_R |= 0x10; // pb4 = analog function enabled
    GPIO_PORTB_ADCCTL_R = 0x00; // not using any pins to trigger adc conversion

    //ADC REGISTERS
    ADC1_ACTSS_R |= 0x2; //ss1
    ADC1_EMUX_R &= ~0x0010; //em1 set to 0x0
    ADC1_SSPRI_R |= 0x2; // initiating ss1
    ADC1_SSMUX1_R = 0xAAAA; //mux for ss1, where all the 4 samples have been configured to use input channel 10 (pb4), so selct lines should == 10 == 0xA
    ADC1_SSCTL0_R = 0x6444;
}

int adc_read(void)
{
    int value = 0;

    while(!(ADC1_RIS_R & 0x2))//wait until ss1 conversions are incomplete
    {

    }

    value = (int) (ADC1_SSFIFO0_R);

    return value;

}





