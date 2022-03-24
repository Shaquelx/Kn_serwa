#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PWM_TOP (39999u)
#define SEVRO_MIN (999u)
#define SEVRO_MAX  (4999u)

int16_t i = 0;

struct Servo
{
  uint8_t index = 0;
  uint16_t value = 0;

  Servo(uint8_t index, uint16_t value)
  {
    this->index = index;
    this->value = value;
  }
};

void calculate_servo_value (Servo& servo, uint16_t input) // example of input, microseconds length
{
  //do calcs
  servo.value = input;
}

Servo servo0 = Servo(0, 3000);
Servo servo1 = Servo(1, 3000);
Servo servo2 = Servo(2, 3000);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ISR(TIMER1_OVF_vect) {
  PORTB = 0xFF;
}

void servo_set(uint16_t deg, uint16_t max_deg) {

  float set = (float)deg / (float)max_deg;

  set = (((float)SEVRO_MAX - (float)SEVRO_MIN) * set) + (float)SEVRO_MIN;

  uint16_t piont = (uint16_t)set;

}
void setup() {

  DDRB = 0xFF;

  TCCR1A = (0b10 << WGM10);

  TIMSK1 = (1 << TOIE1);

  ICR1H = (PWM_TOP & 0xFF00) >> 8;
  ICR1L = (PWM_TOP & 0x00FF);

  TCCR1B = (0b11 << WGM12) | (1 << CS11);
  sei();

}
void loop()
{
  if (TCNT1 > SEVRO_MIN && TCNT1 < SEVRO_MAX)
  {
    if (TCNT1 >= servo0.value && bit_is_set(PORTB, PINB0)) //pinb0 servo
    {
      PORTB &= ~(1 << PINB0);
    }
    if (TCNT1 >= servo1.value && bit_is_set(PORTB, PINB1)) //pinb1 servo
    {
      PORTB &= ~(1 << PINB1);
    }
    if (TCNT1 >= servo2.value && bit_is_set(PORTB, PINB2)) //pinb2 servo
    {
      PORTB &= ~(1 << PINB2);
    }
  }
  //get input value

  //calculate and update servo values
  calculate_servo_value(servo0, 1300);
  calculate_servo_value(servo1, 3300);
  calculate_servo_value(servo2, 4899);

}
