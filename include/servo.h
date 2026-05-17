#ifndef SERVO_H
#define SERVO_H
#include <avr/io.h>
#include <util/delay.h>

#define SERVO_PIN PB3
// 500 stanga, 2500 dreapta
#define CENTRU 1600
#define DREAPTA 800
#define STANGA 2500

void timer1_init();

void servo_write(uint16_t us);


#endif