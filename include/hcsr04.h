#ifndef HCSR04_H
#define HCSR04_H
#include <avr/io.h>
#include <util/delay.h>

#define TRIG PD2
#define ECHO PD3


void HCSR04_init();
void HCSR04_trigger();

uint16_t HCSR04_read();

#endif