#include "l298n.h"

// IN1=PD7, IN2=PB0, IN3=PB3, IN4=PB2
// ENA=PD5 (OC0B), ENB=PD6 (OC0A)

void L298N_init() {
    DDRD |= (1 << IN1) | (1 << ENA) | (1 << ENB);
    DDRB |= (1 << IN2) | (1 << IN3) | (1 << IN4);

    // Timer0 Fast PWM, non-inverting pe 0C0A si 0C0B
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 64 -> 980Hz PWM

    L298N_set_speed(165, 165);
    L298N_stop();
}

void L298N_set_speed(uint8_t left, uint8_t right) {
    OCR0B = left; // ENA = OC0B, stanga
    OCR0A = right; // ENB = OC0A, dreapta
}

void L298N_forward(void) {
    PORTD |=  (1 << IN1);  // IN1 HIGH
    PORTB &= ~(1 << IN2);  // IN2 LOW
    PORTB &= ~(1 << IN3);  // IN3 LOW
    PORTB |=  (1 << IN4);  // IN4 HIGH
}
 
void L298N_backward(void) {
    PORTD &= ~(1 << IN1);  // IN1 LOW
    PORTB |=  (1 << IN2);  // IN2 HIGH
    PORTB |=  (1 << IN3);  // IN3 HIGH
    PORTB &= ~(1 << IN4);  // IN4 LOW
}
 
void L298N_turn_left(void) {
    // stanga oprite, dreapta inainte
    PORTD &= ~(1 << IN1);  // IN1 LOW
    PORTB |=  (1 << IN2);  // IN2 HIGH
    PORTB &= ~(1 << IN3);  // IN3 LOW
    PORTB |=  (1 << IN4);  // IN4 HIGH
}
 
void L298N_turn_right(void) {
    // dreapta oprita, stanga inainte
    PORTD |=  (1 << IN1);  // IN1 HIGH
    PORTB &= ~(1 << IN2);  // IN2 LOW
    PORTB |=  (1 << IN3);  // IN3 HIGH
    PORTB &= ~(1 << IN4);  // IN4 LOW
}
 
void L298N_stop(void) {
    PORTD &= ~(1 << IN1);
    PORTB &= ~(1 << IN2);
    PORTB &= ~(1 << IN3);
    PORTB &= ~(1 << IN4);
}