#ifndef MOTOR_H
#define MOTOR_H
 
#include <stdbool.h>
#include <stdint.h>
#include "driver/gpio.h"
#include "driver/ledc.h"
 
typedef struct {
    gpio_num_t in1;      
    gpio_num_t in2;       
    gpio_num_t pwm;       
    bool       direction; 
} motor_t;
 
#define MOTOR_DUTY_MAX  1023u
#define MOTOR_DUTY_MED  512u
 

void motor_init(motor_t *m); 
void motor_set_direction(motor_t *m);
void motor_set_speed(motor_t *m, uint32_t duty);
void motor_stop(motor_t *m);
 
#endif /* MOTOR_H */
 