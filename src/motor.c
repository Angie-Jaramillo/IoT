#include "motor.h"
#include "esp_log.h"
 
#define TAG "MOTOR"
 
 
void motor_init(motor_t *m)
{
    ledc_timer_config_t timer = {
        .speed_mode      = LEDC_LOW_SPEED_MODE,
        .timer_num       = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz         = 5000,
        .clk_cfg         = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&timer);
 
    ledc_channel_config_t channel = {
        .gpio_num   = m->pwm,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = LEDC_CHANNEL_0,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = 0,
        .hpoint     = 0,
    };
    ledc_channel_config(&channel);
 
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << m->in1) | (1ULL << m->in2),
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);
 
    gpio_set_level(m->in1, 0);
    gpio_set_level(m->in2, 0);

    ESP_LOGI(TAG, "Motor inicializado (IN1=%d, IN2=%d, PWM=%d)",
             m->in1, m->in2, m->pwm);
}
 
 
void motor_set_direction(motor_t *m)
{
    if (m->direction) {
        gpio_set_level(m->in1, 1);
        gpio_set_level(m->in2, 0);
    } else {
        gpio_set_level(m->in1, 0);
        gpio_set_level(m->in2, 1);
    }
}
 
 
void motor_set_speed(motor_t *m, uint32_t duty)
{
    if (duty > MOTOR_DUTY_MAX) duty = MOTOR_DUTY_MAX;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}
 
 
void motor_stop(motor_t *m)
{
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    gpio_set_level(m->in1, 0);
    gpio_set_level(m->in2, 0);
}
 