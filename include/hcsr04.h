#ifndef HCSR04_H
#define HCSR04_H
#include <avr/io.h>
#include <util/delay.h>

#define TRIG PD2
#define ECHO PD3


void HCSR04_init(void);
uint16_t HCSR04_measure(void); // returneaza in cm, 0 la timeout

#endif