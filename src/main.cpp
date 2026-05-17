#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "usart.h"
#include "hcsr04.h"
#include "servo.h"

#define PM_BAUD 28800

int main() {
  USART0_init(UBRR_VALUE);

  DDRB |= (1 << SERVO_PIN); // D9 output

  timer1_init();

  while (1) {
    _delay_ms(1000);
    servo_write(CENTRU);
      _delay_ms(1000);
    servo_write(STANGA);
      _delay_ms(1000);
    servo_write(DREAPTA);
  }
}