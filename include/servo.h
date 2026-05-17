#ifndef SERVO_H
#define SERVO_H
#include <avr/io.h>
#include <util/delay.h>

#define SERVO_PIN PB1
#define CENTRU 1600
#define DREAPTA 800
#define STANGA 2500

void servo_init();

void servo_write(uint16_t us);


#endif