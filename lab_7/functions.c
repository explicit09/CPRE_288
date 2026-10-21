#include "functions.h"
#include "stdio.h"
#include "math.h"

cyBOT_Scan_t scan;

void print_to_putty(char message[]) //same as before
{
    int k;
    cyBot_sendByte('\r');
    for (k = 0; k < strlen(message); k++)
    {
        cyBot_sendByte(message[k]);
    }
}

// prints one scan of raw or cleaned data with "Degrees  Distance"
void print_scan(char title[], float d[])
{
    char message[50];
    int k;

    print_to_putty(title);
    print_to_putty("\nDegrees\t\tDistance (cm)\n");
    for (k = 0; k <  91; k++)
    {
        sprintf(message, "%d\t\t%.1f\n", k * 2, d[k]);
        print_to_putty(message);
    }
}

// prints the object table: Object#  Angle  Distance  Width......same algo as before, but now in a function
void print_objects(dataa *data)
{
    char message[50];
    int k;

    print_to_putty("Object#\tAngle\tDistance\tWidth\n");
    for (k = 1; k <= data->obj; k++)
    {
        sprintf(message, "%d\t%d\t%.1f\t\t%.1f\n", k, data->angle[k],
                data->dect[k], data->width[k]);
        print_to_putty(message);
    }
}

// stores one object that will take the start index of the object and the end index of the object
//made this function static sp that we can deal with every object seperately instead of the whole while loop we had prev
//this function is only called within detect_object
static void add_object(float distance[], dataa *data, int first, int last)
{
    double d1 = distance[first];        // distance at the right edge == start index
    double d2 = distance[last];         // distance at the left edge == end index
    double closest = d1;                //closest dist from cybot to the obj
    double span = (last - first + 1) * 2.0;   // we had 2 widths prev, so instead of doing that, we will be doing the same thing but with a diff variable name
    // still a bit iffy about adding 1, i keep confusing myself with it. Lmk what you guys feel.
    //my example was if the end index is 60 and start index if 50, end-start = 1o, but wont we have 11 indices that we should cover? (50,51,52,53,54,55,56,57,58,59,60)
    int j, n;

    if (last - first + 1 < 5 || data->obj >= 3) 
    //5 is one artbitary number i thought of. So, the miminum number of indexes that an object should span is 5 (5*2 = 10 degrees?)
    // so even in the worst case, we should have objects place atleast 10 degress apart from each other.

    //3 is the max number of objects we can have. I dont think we will ever test with 3+ objects. Right now, im saying if the program 
    //finds more than 3 obj, just return, saying that is likely just a noise. 
        return;

    for (j = first; j <= last; j++) //from start index to end index
    {
        if (distance[j] < closest)
            closest = distance[j];
    }
    
    //trying pointer notation, we can shift to dot notation if required
    data->obj++;
    n = data->obj;
    data->angle[n] = first + last; //this will be same as taking the average of start and end angle (first and last are indices not angles) 
    data->dect[n] = closest;
    // width =  (law of cosines)
    data->width[n] = sqrt(pow(d1,2) + pow(d2,2)
                          - 2.0 * d1 * d2 * cos(span * (M_PI / 180.0))); //same formula
}

// Finds the objects 
// An object starts where the distance drops by 20 cm or more and
// ends where it jumps back up by 20 or more.
//prev we had 50 cm, lets see how this works
void detect_object(float distance[], dataa *data)
{
    int first = -1;         // so if we are inside the bounds of the object, it will be 1, if not an obj, first will be -1
    int idx;
    float diff;

    data->obj = 0; //starting the total objects as 0 in the beginning
    data->angle[0] = 90;    // if nothing is found, "smallest object" points straight ahead

    for (idx = 1; idx < 91; idx++)
    {
        diff = distance[idx] - distance[idx - 1]; //curr - prev

        if (diff <= -20 || diff >= 20)       // an edge
        {
            if (first >= 0) //within the bounds of the obj
                add_object(distance, data, first, idx - 1);   // object just ended so we add it 

            if (diff <= -20 && distance[idx] < 300.0f)
                first = idx;                           // something closer starts here
            else
                first = -1;                            // back to background
        }
    }
    
}



// same algo
int find_smallest(dataa *data)
{
    int k, smallest = 0;
    double min = 1e9; //smallest number i cld find

    for (k = 1; k <= data->obj; k++)
    {
        if (data->width[k] < min)
        {
            min = data->width[k];
            smallest = k;
        }
    }
    return smallest;
}

void point_to_smallest_obj(int smallest_obj_angle)
{
    cyBOT_Scan(smallest_obj_angle, &scan);
}
