
//usar ctcrna
// poner a 0 los registros

//

#include <avr/io.h>
#include <avr/interrupt.h>
#define sbi(port, bit) (port) |= (1 << (bit));   // setbit
#define cbi(port, bit) (port) &= ~(1 << (bit));  //clearbit

volatile uint32_t g_millis = 0;
void pwm1_init(uint16_t top, uint16_t prescaler) {
  cli();
  //oc1c y oc1b como salida
  sbi(DDRB, DDB6);
  sbi(DDRB, DDB7);

  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;

  OCR1B = 0;
  OCR1C = 0;
  // configurar modoe fastpwm con tope ocr1A
  sbi(TCCR1B, WGM13);
  sbi(TCCR1B, WGM12);
  sbi(TCCR1A, WGM11);
  sbi(TCCR1A, WGM10);


  // Configurar prescaler
  switch (prescaler) {
    case 1:
      sbi(TCCR1B, CS10);
      break;
    case 8:
      sbi(TCCR1B, CS11);
      break;
    case 64:
      sbi(TCCR1B, CS11);
      sbi(TCCR1B, CS10);
      break;
    case 256:
      sbi(TCCR1B, CS12);
      break;
    case 1024:
      sbi(TCCR1B, CS12);
      sbi(TCCR1B, CS10);
      break;
  }

  //habilitar b y c

  cbi(TCCR1A, COM1B0);
  sbi(TCCR1A, COM1B1);
  cbi(TCCR1A, COM1C0);
  sbi(TCCR1A, COM1C1);

  OCR1A = top;
  sei();
}
void set_pwm_duty(int ch, float duttycicle) {
  //verificar float dentro de rango y si no pasarlo a 0 o a 1
  if (duttycicle > 1) {
    duttycicle = 1.0;
  } else if (duttycicle < 0) {
    duttycicle = 0.0;
  }
  // convertir a valor uint16_t calcular el 50% del toper de ocra pej
  uint16_t valor = OCR1A * duttycicle;

  //asignar al registro B o C

  if (ch == 0) {  //canal B
    OCR1B = valor;
  } else if (ch == 1) {  //canal C
    OCR1C = valor;
  }
}



void setup() {
  Serial.begin(9600);
  while (!Serial) {}
}



void loop() {
  static uint32_t last = 0;
  static float d = 0.0;
  for (int i = 0; i < 2; i++) {
    if (i == 0) {
      Serial.println("PWM cambiado a 10Hz");
      pwm1_init((200000-1)/8, 64);

    } else {
      Serial.println("PWM cambiado a 50Hz");
      pwm1_init(40000 - 1, 8);
    }
    d = 0.0;
    while (d < 1.0) {
      delay(50);
      set_pwm_duty(0, d);
      set_pwm_duty(1, 1.0 - d);
      d += 0.01;
    }
  }
}