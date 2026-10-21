////#include "lcd.h"
////#include "part5_cyBot.h"
////#include "movement.h"
////#include "open_interface.h"
////#include "Timer.h"
////
////
/////// for roomba 12
////
//// int main (void){ //initialize the UART function
////    oi_t *sensor_data =  oi_alloc();
////    oi_init(sensor_data);
////
////    cyBot_uart_init();
////    timer_init();
////    lcd_init();
////
////  //  int letter = cyBot_getByte();
////    char message[100] = "";
////
////    while(1){
////
////        int letter = cyBot_getByte();
////        if (letter == 'w'){ //w forward
////            oi_setWheels(100, 100);
////            cyBot_sendByte('w');
////        }
////        else if(letter == 's'){ //s go back
////            oi_setWheels(-100, -100);
////            cyBot_sendByte('s');
////        }
////        else if(letter == 'a'){ //a turn left
////            turn(sensor_data, 90, 0);
////            oi_setWheels(100, 100);
////            cyBot_sendByte('a');
////        }
////        else if (letter == 'd'){ //d turn right
////           turn(sensor_data, 90, 1);
////            oi_setWheels(100, 100);
////            cyBot_sendByte('d');
////        }
////
////        else if(letter == 'm'){ //m
////            cyBot_sendByte(letter);
////            sprintf(message, "Got an %s", letter);
////            lcd_puts(message);
////        }
////
////        else{
////            oi_setWheels(0, 0);
////        }
////    }
////
////        return 0;
////   }
//
//
//
//
/////////////////////////////////////////////////////////////////////////
//// Name: Simple-CyBot-echo.c                                         //
//// Author: Phillip Jones (phjones@iastate.edu)                       //
//// Date: 09/26/2023                                                  //
//// Description: Simple Cybot program that is an Echo'ish program for //
////              communicating with the Starter Client Socket code.   //
/////////////////////////////////////////////////////////////////////////
//
//#include "Timer.h"
//#include "lcd.h"
//#include "cyBot_uart.h"
//#include "open_interface.h"
//#include "movement.h"
//#include "part5_cyBot.h"
//
//
//int main(void)
//{
//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//
//    timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called
//                  // and enables time functions (e.g. timer_waitMillis)
//    lcd_init();  // Initialize the the LCD screen.  This also clears the screen.
//    cyBot_uart_init();  // Initialize UART
//
//    char my_data;       // Variable to get bytes from Client
//    char command[100];  // Buffer to store command from Client
//    int index = 0;      // Index position within the command buffer
//    int i = 0;
//
//    // Write to LCD so that we know the program is running
//    lcd_printf("Running");
//
//    while (1)
//    {
//
//        index = 0;  // Set index to the beginning of the command buffer
//        my_data = cyBot_getByte(); // Get first byte of the command from the Client
//
//        // Get the rest of the command until a newline byte (i.e., '\n') received
//        while (my_data == 'w' || my_data == 's' || my_data == 'a' || my_data == 'd')
//        {
////      command[index] = my_data;  // Place byte into the command buffer
////      index++;
//            my_data = cyBot_getByte(); // Get the next byte of the command
//            if (my_data == 'w')
//            { //w forward
//                oi_setWheels(100, 100);
//                cyBot_sendByte(my_data);
//                sprintf(command, "Got an %c", my_data);
//                lcd_puts(command);
//            }
//            else if (my_data == 's')
//            { //s go back
//                oi_setWheels(-100, -100);
//                cyBot_sendByte(my_data);
//                sprintf(command, "Got an %c", my_data);
//                lcd_puts(command);
//            }
//            else if (my_data == 'a')
//            { //a turn left
//                turn(sensor_data, 90, 0);
//                oi_setWheels(100, 100);
//                cyBot_sendByte(my_data);
//                sprintf(command, "Got an %c", my_data);
//                lcd_puts(command);
//            }
//            else if (my_data == 'd')
//            { //d turn right
//                turn(sensor_data, 90, 1);
//                oi_setWheels(100, 100);
//                cyBot_sendByte(my_data);
//                sprintf(command, "Got an %c", my_data);
//                lcd_puts(command);
//            }
//
//            else if (my_data == 'm')
//            { //m
//                cyBot_sendByte(my_data);
//                sprintf(command, "Got an %c", my_data);
//                lcd_puts(command);
//            }
//
//            else
//            {
//                oi_setWheels(0, 0);
//                sprintf(command, "quit");
//
//                for(i = 0; i < strlen(command); i++){
//                    cyBot_sendByte(command[i]);
//                }
//            }
//        }
//
//        command[index] = '\n'; // place newline into command in case one wants to echo the full command back to the Client
//        command[index + 1] = 0; // End command C-string with a NULL byte so that functions like printf know when to stop printing
////
//        lcd_printf("Got: %s", command); // Print received command to the LCD screen
//
//        // Send a response to the Client (Starter Client expects the response to end with \n)
//        //In this case I am just sending back the first byte of the command received and a '\n'
//        cyBot_sendByte(my_data);
//
//        // Only send a '\n' if the first byte of the command is not a '\n',
//        // to avoid sending back-to-back '\n' to the client
//        if (command[0] != '\n')
//        {
//            cyBot_sendByte('\n');
//        }
//
//    }
//
//    return 0;
//}
//
