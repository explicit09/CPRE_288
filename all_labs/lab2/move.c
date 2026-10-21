//#include "open_interface.h"
//
//void main() {
//
//    //initializing the serial connection
//    oi_t *sensor_data = oi_alloc();
//    oi_init(sensor_data);
//
//    double sum = 0;
//
//    oi_setWheels(100, 100); // move forward; full speed
//
//    while (sum < 1000)
//    {
//        oi_update(sensor_data);
//
//        sum += sensor_data->distance;
//
//    }
//        oi_setWheels(0, 0); // stop
//        oi_free(sensor_data);
//}
