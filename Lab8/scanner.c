#include "scanner.h"
#include "cyBot_Scan.h"

cyBOT_Scan_t scan;
extern float dist[91];
extern int ir[91];
extern float estimate[91];
const int degrees_to_scan = 180;
int i = 0;
int sum = 0;
int avg = 0;

void scan_IR_PING(void)
{
    for (i = 0; i <= degrees_to_scan; i += 2)
    {
        cyBOT_Scan(i, &scan);
        dist[i / 2] = scan.sound_dist;

        for (avg = 0; avg < 3; avg++)
        {
            cyBOT_Scan(i, &scan); // multiple scans with taking avg of IR
            sum += scan.IR_raw_val;
        }
        sum /= 3;
        ir[i / 2] = sum; // it will return -1 if not enabled
        sum = 0;

        estimate[i / 2] = (4.80028 * pow(10, -12)) * pow(ir[i / 2], 4) - (4.96639 * pow(10, -8)) * pow(ir[i / 2], 3) + (0.000194691) * pow(ir[i / 2], 2) - (0.350156 * ir[i / 2]) + 260.87977;
    }
}
void scan_PING(void)
{
    for (i = 0; i <= degrees_to_scan; i += 2)
    {
        cyBOT_Scan(i, &scan);
        dist[i / 2] = scan.sound_dist;
    }
}

void scan_IR(void)
{
    for (i = 0; i <= degrees_to_scan; i += 2)
    {
        for (avg = 0; avg < 3; avg++)
        {
            cyBOT_Scan(i, &scan); // multiple scans with taking avg of IR
            sum += scan.IR_raw_val;
        }
        sum /= 3;
        ir[i / 2] = sum; // it will return -1 if not enabled
        sum = 0;

        estimate[i / 2] = (4.80028 * pow(10, -12)) * pow(ir[i / 2], 4) - (4.96639 * pow(10, -8)) * pow(ir[i / 2], 3) + (0.000194691) * pow(ir[i / 2], 2) - (0.350156 * ir[i / 2]) + 260.87977;
    }
}