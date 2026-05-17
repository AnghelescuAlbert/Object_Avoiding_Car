#ifndef L298N_H
#define L298N_H

#include <avr/io.h>
#include <stdint.h>

#define IN1 PD7
#define IN2 PB0
#define IN3 PB3
#define IN4 PB2
#define ENA PD5
#define ENB PD6

void L298N_init();
void L298N_set_speed(uint8_t left, uint8_t right);  // 0-255
void L298N_forward(void);
void L298N_backward(void);
void L298N_turn_left(void);
void L298N_turn_right(void);
void L298N_stop(void);

#endif