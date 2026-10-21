/*
*
*   uart.c
*
*
*
*
*
*   @author
*   @date
*/

#include "uart.h"

void uart_init(void){
    SYSCTL_RCGCGPIO_R |= 0b00000010;      // enable clock GPIOB (page 340)
    SYSCTL_RCGCUART_R |= 0b00000010;      // enable clock UART1 (page 344)
    GPIO_PORTB_AFSEL_R =0b00000011; // sets PB0 and PB1 as peripherals (page 671)
    GPIO_PORTB_PCTL_R |= 0x00000011; // pmc0 and pmc1       (page 688)  also refer to page 650
    GPIO_PORTB_DEN_R |= 0b00000011;        // enables pb0 and pb1
    GPIO_PORTB_DIR_R = ((GPIO_PORTB_DIR_R) & 0b11111110)
            | ((GPIO_PORTB_DIR_R) | 0b00000010); // sets pb0 as output, pb1 as input


    //compute baud values [UART clock= 16 MHz]
    double fbrd;
    int ibrd;
    //float brd;

    //brd = (16000000)/(16*115200); // page 903
    ibrd = 8;
    fbrd = 44;

    UART1_CTL_R &= ~0x01;      // disable UART1 (page 918)
    UART1_IBRD_R = ibrd;        // write integer portion of BRD to IBRD
    UART1_FBRD_R = fbrd;   // write fractional portion of BRD to FBRD
    UART1_LCRH_R = 0b01100000; // write serial communication parameters (page 916) * 8bit and no parity
    UART1_CC_R = 0x0;     // use system clock as clock source (page 939)
    UART1_CTL_R |= 0x301;        // enable UART1


}

void uart_sendChar(char data){ // to send 1 char over UART1

    UART1_DR_R = data;

    while (UART1_FR_R & 0x20) ///// Waiting as long as FIFO is full
	        {
	        }

}

char uart_receive(void){
	char data=0;
	while (UART1_FR_R & 0x10) //waiting as long as FIFO is empty
	{
	}

	data = (char)(UART1_DR_R & 0xFF);
	return data;
}


volatile int flag = 0;
volatile char c;

void uart_interrupt(void)
{
        UART1_CTL_R &= ~0x01;
        UART1_ICR_R = 0x10;
        UART1_IM_R |= 0x10;

        //NVIC_PRI1_R |= 0x00200000;
        NVIC_EN0_R |= 0x40;

        IntRegister(INT_UART1, UART1_Handler);
        IntMasterEnable();

        UART1_CTL_R |= 0x301;

}

void UART1_Handler(void)
{

    if(UART1_MIS_R & 0x10)
    {
        c = (char)(UART1_DR_R & 0xFF);
        flag = 1;
        UART1_ICR_R = 0x10;
    }

}
//void uart_sendStr(const char *data){
	//TODO for reference see lcd_puts from lcd.c file
//}


