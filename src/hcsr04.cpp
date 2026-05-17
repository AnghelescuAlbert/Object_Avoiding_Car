#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "hcsr04.h"


// Timer0 normal mode, prescaler 64, 16 Mhz -> 1 tick = 4 us

void HCSR04_init() {
  DDRD |= (1 << TRIG);
  DDRD &= ~(1 << ECHO);
  PORTD &= ~(1 << TRIG);
  
  TCCR2A = 0;
  TCCR2B = (1 << CS22); // prescaler 64
  TCNT2 = 0;
}


uint16_t HCSR04_measure()
{
    // Puls TRIG 10 us
    PORTD |= (1 << TRIG);
    _delay_us(10);
    PORTD &= ~(1 << TRIG);

    // Asteapta ECHO HIGH
    TCNT2 = 0;
    while (!(PIND & (1 << ECHO)));

    // Masoara pulsul ECHO
    uint16_t ticks = 0;
    TCNT2 = 0;
    while (PIND & (1 << ECHO)) {
        if (TCNT2 > 250) {
            ticks += 250;
            TCNT2 = 0;

            if (ticks > 7500) return 0; // timeout 30ms
        }
    }
    ticks += TCNT2;

    return ticks / 14; // ticks * 4 us / 58 = cm

}