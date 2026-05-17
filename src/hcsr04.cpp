#include <avr/io.h>
#include <util/delay.h>
#include "hcsr04.h"

void HCSR04_init() {
  DDRD |= (1 << TRIG);
  DDRD &= ~(1 << ECHO);
}

void HCSR04_trigger()
{
    PORTD &= ~(1 << TRIG);
    _delay_us(2);

    PORTD |= (1 << TRIG);
    _delay_us(10);

    PORTD &= ~(1 << TRIG);
}

uint16_t HCSR04_read()
{
    uint16_t count = 0;

    while (!(PIND & (1 << ECHO)));

    while (PIND & (1 << ECHO))
    {
        _delay_us(1);
        count++;
    }

    return count;
}