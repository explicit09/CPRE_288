#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include "Timer.h"
#include "lcd.h"
#include "string.h"
#include "sensor-data -3.h"
#include "math.h"
#include "open_interface.h"


// 227500 - right cal
// 1282750 - left cal
// for cyBOT 22

int main(void)
{
   timer_init();
   lcd_init();
   cyBOT_init_Scan(0b0111);
   //cyBOT_SERVO_cal();
  // cyBot_uart_init();
   right_calibration_value = 227500;
   left_calibration_value = 1282750;

//   int z;
//   int j;
   int k;
   
//   int letter;
//   char message[50];
   //double dist[91];
//   char *header;
   cyBOT_Scan_t scan;

//    for (z = 0; z <= 180; z += 2)
//    {
//        cyBOT_Scan(z, &scan);
//        dist[z / 2] = scan.sound_dist;
//    }

//    while (1)
//    {
//     //    letter = cyBot_getByte();

//        header = "Degrees\t\tDistance (cm)";

//    while (1)
//    {
    //    if (letter == 'm')
    //    {
        //    cyBot_sendByte('\r');
        //    cyBot_sendByte('\n');
        //    for (z = 0; z < strlen(header); z++)
        //    {
        //        cyBot_sendByte(header[z]);
        //    }
//
        //    for (j = 0; j < 91; j++)
        //    {
        //        sprintf(message, "%d\t\t%.1f", j * 2, dist[j]);
            //    cyBot_sendByte('\r');
            //    cyBot_sendByte('\n');
            //    for (k = 0; k < strlen(message); k++)
            //    {

            //        cyBot_sendByte(message[k]);
            //    }
//            }


//        }
//    }

  int i=0; 

  double start[10];

  double end[10];

  double width[10];

  int obj = 0;

  double dist[10];
  double end_d[10];

  int angle[10];

  
//safter scannig, we need to put tus data into a header file

  int a;

  //noiseless cleaning algo






  for(i=1; i<=89; i++) //detects the objects

  {

    double diff_forward = sensor_data_array[i-1] - sensor_data_array[i];

    double diff_backward = sensor_data_array[i+1] - sensor_data_array[i];



    if(sensor_data_array[i] < 300){

      if(diff_forward > 50)

      {

        obj++;
        start[obj] = i*2;

        dist[obj] = sensor_data_array[i];

       

        //obj++;

      } //else 


      if(diff_backward > 50)

      {
          
          end[obj] = i*2;
          angle[obj] = (end[obj]+start[obj])/2;
          end_d[obj] = sensor_data_array[i];
          // obj++;

      }

      //width[obj] = end[obj] - start[obj];
      width[obj] = sqrt(pow(end_d[obj], 2)+ pow(dist[obj], 2) - (2*end_d[obj]*dist[obj]*cos(width[obj]*(M_PI/180))));

    }


  }

  
  int min =100;
  int small_obj =0;
  for (k = 1; k < obj+1; k++)
  {
        if(width[k] < min)
        {
            min = width[k];
            small_obj = k;


        }
  }

    cyBOT_Scan(start[small_obj], &scan);

    lcd_printf("Smallest Object = %d\nSmallest Width = %.1f\nStart Angle = %.1f", small_obj, width[small_obj], start[small_obj] );

       printf("Object#\tAngle\tDistance\tWidth\n");

       for(a = 1; a <= obj; a++){

         printf("%d\t%d\t%.1f\t\t%.1f\n", a, angle[a], dist[a], width[a]);

      }
   return 0;
}
