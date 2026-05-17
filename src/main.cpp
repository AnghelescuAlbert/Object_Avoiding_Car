#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "usart.h"
#include "hcsr04.h"
#include "servo.h"
#include "l298n.h"

#define PM_BAUD 28800

#define OBSTACLE_CM  40
#define SERVO_CENTER 1600
#define SERVO_LEFT   2500
#define SERVO_RIGHT  800
#define SCAN_DELAY   400 // timp sa se roteasca servo-ul

typedef enum {
  STATE_FORWARD,
  STATE_SCAN,
  STATE_TURN
}State;

int main() {
  servo_init();
  HCSR04_init();
  L298N_init();

  servo_write(SERVO_CENTER);
  _delay_ms(500);

  State state = STATE_FORWARD;
  uint16_t dist_left, dist_right;

  while (1) {
    switch (state) {
      case STATE_FORWARD:
        L298N_forward();
        _delay_ms(50);
        if (HCSR04_measure() < OBSTACLE_CM) {
          _delay_ms(20);
          if (HCSR04_measure() < OBSTACLE_CM) {
              L298N_stop();
              state = STATE_SCAN;
          }
        }
        break;

      case STATE_SCAN:
        servo_write(SERVO_LEFT);
        _delay_ms(SCAN_DELAY);
        dist_left = HCSR04_measure();

        servo_write(SERVO_RIGHT);
        _delay_ms(SCAN_DELAY);
        dist_right = HCSR04_measure();

        servo_write(SERVO_CENTER);
        _delay_ms(SCAN_DELAY);

        state = STATE_TURN;
        break;

      case STATE_TURN:
        if (dist_left > dist_right) {
            L298N_turn_left();
        } else {
            L298N_turn_right();
        }
        _delay_ms(400); // timpul de virare
        L298N_stop();
        state = STATE_FORWARD;
        break;
    }
  }
}