#ifndef SERVO_H_
#define SERVO_H_

void servo_init(void);
int  servo_set_match(int match); 
void write_match(int match);
int  servo_move(float degrees);
int  servo_get_match(void);

#endif