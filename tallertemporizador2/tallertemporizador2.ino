
//usar ctcrna
// poner a 0 los registros

//

#include <avr/io.h>
#include <avr/interrupt.h>
#define sbi(port, bit) (port) |= (1 << (bit));   // setbit
#define cbi(port, bit) (port) &= ~(1 << (bit));  //clearbit

volatile uint32_t g_millis = 0;

void clock_init() {
  //Desactivar las interrupciones globales
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
  uint16_t tcnt;

  cli();
  ms = g_millis;
  tcnt = TCNT1;
  sei();
  us = ms * 1000 + tcnt/2;
  return us;
  
}

// Esperas Relativas y Absolutas
void delay_ms(uint32_t ms){
  uint32_t inicio = clock_ms();
  while(clock_ms() - inicio < ms);
}

void delay_until_ms(uint32_t end_ms){
  while((int32_t)(end_ms - clock_ms()) > 0);
}

void delay_us(uint32_t us){
  uint32_t inicio = clock_us();
  while(clock_us()-inicio < us);
}

void delay_until_us(uint32_t end_us){
  while((int32_t)(end_us - clock_us()) > 0);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  clock_init();  // configurar timer 1 con todos los registros que hemos visto
}



void loop() {
  /*static uint32_t lastms = 0;   // static: conserva su valor entre vueltas
  uint32_t now_ms = clock_ms();

  if (now_ms - lastms >= 1000) {
    lastms += 1000;
    Serial.println("Ha pasado 1 segundo");
  }*/

   uint32_t t0, t1;

  // 1. delay_ms: debería medir ~500000 us
  t0 = clock_us();
  delay_ms(500);
  t1 = clock_us();
  Serial.print("delay_ms(500)   -> ");
  Serial.print(t1 - t0);
  Serial.println(" us");

  // 2. delay_us: debería medir ~250 us
  t0 = clock_us();
  delay_us(250);
  t1 = clock_us();
  Serial.print("delay_us(250)   -> ");
  Serial.print(t1 - t0);
  Serial.println(" us");

  // 3. delay_until_ms: 3 ticks exactos cada 200 ms
  uint32_t t = clock_ms();
  for (int i = 0; i < 3; i++) {
    t += 200;
    delay_until_ms(t);
    Serial.print("until_ms tick en ");
    Serial.print(clock_ms());
    Serial.println(" ms");
  }

  // 4. delay_until_us: esperar hasta dentro de 1000 us
  uint32_t fin = clock_us() + 1000;
  delay_until_us(fin);
  Serial.print("delay_until_us  -> retraso ");
  Serial.print(clock_us() - fin);
  Serial.println(" us");

  Serial.println("----");
  delay_ms(2000);
}