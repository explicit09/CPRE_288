/*
 * adc.c
 *
 *  Created on: Oct 22, 2026
 *      Author: nkantner
 */
#include "adc.h"
#include "timer.h"

void adc_init(void)
{
    SYSCTL_RCGCGPIO_R |= 0b00000010; //port b
    //ENABLE ADC CLOCK
    SYSCTL_RCGCADC |= 0b10; // clock for ADC registers
    GPIO_PORTB_AFSEL_R |= 0b00010000; //pb4
    GPIO_PORTB_DIR_R = (GPIO_PORTB_DIR_R & ~0x01) | 0x02; // 1 = out; 0 = in
    GPIO_PORTB_DEN_R &= ~0x10; // pb4 = digital function disabled
    GPIO_PORTB_AMSEL |= 0x10; // pb4 = analog function enabled
    GPIO_PORTB_ADCCTL = 0x00; // not using any pins to trigger adc conversion

    //ADC REGISTERS
    ADC1_ACTSS_R |= 0x2; //ss1
    ADC1_EMUX_R &= ~0x0010; //em1 set to 0x0
    ADC1_SSPRI_R |= 0x2;
    //ADC1_SSMUX1_R





}





