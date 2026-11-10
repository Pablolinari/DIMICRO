
//usar ctcrna
// poner a 0 los registros

//

#include <avr/io.h>
#include <avr/interrupt.h>
#define sbi(port, bit) (port) |= (1 << (bit));   // setbit
#define cbi(port, bit) (port) &= ~(1 << (bit));  //clearbit

volatile uint32_t g_millis = 0;

void clock_init() {
  //desactiver interrucpciones cghlobales
  cli();
  //ttcr1a ,ttcr1b y c  a 0 todos
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;

  //configurar timer1 en modo ctc icr1 como top

  sbi(TCCR1B, WGM13);
  sbi(TCCR1B, WGM12);
  cbi(TCCR1A, WGM11);
  cbi(TCCR1A, WGM10);

  // prescaler a 8
  cbi(TCCR1B, CS12);
  sbi(TCCR1B, CS11);
  cbi(TCCR1B, CS10);

  //valor de tope icr1 para 1khz
  ICR1 = 1999;
  //habilitar interrupcion por compare match con icr1
  sbi(TIMSK1, ICIE1);

  //deshabilitar comunicaciones con el pin
  cbi(TCCR1A, COM1C1);
  cbi(TCCR1A, COM1C0);
  //habilita interrupciones globales
  sei();
}
ISR(TIMER1_CAPT_vect) {
  // rutina de interrupciones cada 1ms
  g_millis++;
}

uint32_t clock_ms() {
  uint32_t ms;
  cli();
  ms = g_millis;
  sei();
  return ms;
}
uint32_t clock_us() {
  uint32_t ms;
  uint32_t us;
  cli();
  ms = g_millis;
  microsecond = read(TCNT1)/2
  us = ms*1000 + microsecond
  sei();
  return ms;
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  clock_init();  // configurar timer 1 con todos los registros que hemos visto
}



void loop() {
  uint32_t lastms = 0;
  uint32_t now_ms = clock_ms();

  if (now_ms % 1000==0) {
    Serial.println("Ha pasado 1 segundo");
  }
}
