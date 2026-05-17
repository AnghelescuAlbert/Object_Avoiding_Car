#include "servo.h"

void timer1_init()
{
    // Fast PWM, TOP = ICR1
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // prescaler 8

    ICR1 = 40000; // 20ms perioada (50Hz la 16MHz cu prescaler 8)
}

void servo_write(uint16_t us)
{
    // 1us ≈ 2 ticks (cu prescaler 8)
    OCR1A = us * 2;
}
