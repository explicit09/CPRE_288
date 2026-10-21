// //#include "stdio.h"
// //#include "sensor1.h"
// //
// //
// //void main()
// //{
// //
// //     int i=0; // Index used to iterate through array of sensor data
// //     float x =0;
// //     float y=0;
// //     float z=0;
// //     float start_dist =0;
// //     float end_dist =0;
// //     char *header2;
// //     int obj[];
// //
// //     for(i=0; i<=90; i++)
// //       {
// //         x = sensor_data_array[i];
// //         if (i > 0)
// //         {
// //             y= sensor_data_array[i-1];
// //         }
// //         else {
// //           y = x;
// //         }
// //
// //         if (i < 90)
// //         {
// //             z = sensor_data_array[i+1];
// //         }
// //
// ////         if(((x -y >= 0.5) || (x - z >= 0.5)) || ((x - y <= -0.5) && (x -z <= -0.5)))
// ////         {
// ////
// ////         }
// //
// //         if (x - z >= 50)
// //         {
// //             start_dist = x;
// //
// //         }
// //         else if (x -z <= -0.5)
// //         {
// //             end_dist = x;
// //         }
// //
// //         if(start_dist != end_dist)
// //         {
// //             obj[]
// //         }
// //
// //
// //       }
// //
// //     //print out the txt file
// //     header2 = "Object #\t\Angle\tDistance\tWidth";
// //
// //
// //
// //     srpintf(message2, )
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //}



// #include "stdio.h"

// #include "sensor-data-2.h"

// #include  "math.h"



// int main(void)
// {

//      int i=0; //angle storage 

//   double start[10]; //angle start value 

//   double end[10]; //end angle 

//   double width[10]; //end- start

//   int obj=0; // detect # of objects 

//   double dist[100];

//   int angle[100];

  

//   int a;


// //loop to see when there is an object based off current vs past or current vs future distance 
//   for(i=1; i<=89; i++)

//   {

//     double diff_forward = sensor_data_array[i] - sensor_data_array[i-1];

//     double diff_backward = sensor_data_array[i] - sensor_data_array[i+1];


// //after 300 there is no object so if it is less than 300 we take absolute value of the distance differrence 
//     if(sensor_data_array[i] < 300){

//       if(fabs(diff_forward) > 45)// start of object 


//       {

//         //start[obj] = sensor_data_array[i];

//         dist[obj] = sensor_data_array[i];
//         angle[obj] = i*2;
        
//         start[obj] = angle[obj]; //starting angle
//         //obj++;
        

//       } //else 

//     }

    

//     if(fabs(diff_backward) > 45)//end of the object

//     {

      
//      // end[obj] = sensor_data_array[i];
//       end[obj] = i*2;
//       obj++;


//     }



//     width[obj] = end[obj] - start[obj];

//   }

  

//   printf("Object#\tAngle\tDistance\tWidth\tStart\tEnd\n");

//   for(a =1; a <= obj; a++){

//     printf("%d\t%d\t%.1f\t\t%.1f%\t%.1f\t\t%.1f\n", a, angle[a], dist[a], width[a], start[a], end[a]);

//   }

//     return 0;

// }




// WIDTH WORKS 
// #include "stdio.h"

// #include "sensor-data-2.h"

// #include  "math.h"



// int main(void)

// {

//   int i=0; 

//   double start[10];

//   double end[10];

//   double width[10];

//   int obj = 0;

//   double dist[100];

//   int angle[100];

  

//   int a;



//   for(i=1; i<=89; i++)

//   {

//     double diff_forward = sensor_data_array[i-1] - sensor_data_array[i];

//     double diff_backward = sensor_data_array[i+1] - sensor_data_array[i];



//     if(sensor_data_array[i] < 300){

//       if(diff_forward > 50)

//       {

//         obj++;
//         start[obj] = i*2;

//         dist[obj] = sensor_data_array[i];

       

//         //obj++;

//       } //else 


//       if(diff_backward > 50)

//       {
          
//           end[obj] = i*2;
//           angle[obj] = (end[obj]+start[obj])/2;
//           // obj++;

//       }

//       width[obj] = end[obj] - start[obj];

//     }

    
    

//   }

  

//   printf("Object#\tAngle\tDistance\tWidth\n");

//   for(a = 1; a <= obj; a++){

//     printf("%d\t%d\t%.1f\t\t%.1f\n", a, angle[a], dist[a], width[a]);

//   }

  



//   return 0;

// }



