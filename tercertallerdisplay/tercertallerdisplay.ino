#include <LiquidCrystal.h>

#define sbi(port, bit) (port) |= (1 << (bit))   //setbit
#define cbi(port, bit) (port) &= ~(1 << (bit))  //clearbit

//LiquidCrystal lcd(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
//LiquidCrystal lcd(RS,RW,E,D0,D1,D2,D3,D4,D5,D6,D7); --> Indicamos a que pines tenemos conectados cada entrada

void setup() {
  // put your setup code here, to run once:
  //lcd.begin(20, 4);  // Indica 4 lineas de 20 caracteres
  Serial.begin(57600);
  reset();
}

void setIO(bool salida) {
  if (salida) {
    // solo los pines de datos
    sbi(DDRE, DDE6);  //p7
    sbi(DDRD, DDD7);  //p6
    sbi(DDRC, DDC6);  //p5
    sbi(DDRD, DDD4);  //p4
    sbi(DDRD, DDD0);  //p3
    sbi(DDRD, DDD1);  //p2
    sbi(DDRD, DDD3);  //p1
    sbi(DDRD, DDD2);  //p0
  } else {
    cbi(DDRE, DDE6);  //p7
    cbi(DDRD, DDD7);  //p6
    cbi(DDRC, DDC6);  //p5
    cbi(DDRD, DDD4);  //p4
    cbi(DDRD, DDD0);  //p3
    cbi(DDRD, DDD1);  //p2
    cbi(DDRD, DDD3);  //p1
    cbi(DDRD, DDD2);  //p0
  }
}

/*
void setIO(bool salida) {
  if (salida) {
    sbi(DDRB, DDB6);  // p10
    sbi(DDRB, DDB5);  //p9
    sbi(DDRB, DDB4);  //p8
    sbi(DDRE, DDE6);  //p7
    sbi(DDRD, DDD7);  //p6
    sbi(DDRC, DDC6);  //p5
    sbi(DDRD, DDD4);  //p4
    sbi(DDRD, DDD0);  //p3
    sbi(DDRD, DDD1);  //p2
    sbi(DDRD, DDD3);  //p1
    sbi(DDRD, DDD2);  //p0
  } else {
    cbi(DDRB, DDB6);  // p10
    cbi(DDRB, DDB5);  //p9
    cbi(DDRB, DDB4);  //p8
    cbi(DDRE, DDE6);  //p7
    cbi(DDRD, DDD7);  //p6
    cbi(DDRC, DDC6);  //p5
    cbi(DDRD, DDD4);  //p4
    cbi(DDRD, DDD0);  //p3
    cbi(DDRD, DDD1);  //p2
    cbi(DDRD, DDD3);  //p1
    cbi(DDRD, DDD2);  //p0
  }
}
*/
byte estadoDisplay = 0x0C;  // 0000 1 D C B --> Display on/off control
byte estadoEntrada = 0x06;  //

//Carga el código de bits en D7-D0
// valor --> dato de 8 bits
void cargarDatos(byte valor) {
  if (bitRead(valor, 7) == 0) {
    cbi(PORTD, PORTD2);
  } else {
    sbi(PORTD, PORTD2);
  }

  if (bitRead(valor, 6) == 0) {
    cbi(PORTD, PORTD3);
  } else {
    sbi(PORTD, PORTD3);
  }

  if (bitRead(valor, 5) == 0) {
    cbi(PORTD, PORTD1);
  } else {
    sbi(PORTD, PORTD1);
  }

  if (bitRead(valor, 4) == 0) {
    cbi(PORTD, PORTD0);
  } else {
    sbi(PORTD, PORTD0);
  }

  if (bitRead(valor, 3) == 0) {
    cbi(PORTD, PORTD4);
  } else {
    sbi(PORTD, PORTD4);
  }

  if (bitRead(valor, 2) == 0) {
    cbi(PORTC, PORTC6);
  } else {
    sbi(PORTC, PORTC6);
  }

  if (bitRead(valor, 1) == 0) {
    cbi(PORTD, PORTD7);
  } else {
    sbi(PORTD, PORTD7);
  }

  if (bitRead(valor, 0) == 0) {
    cbi(PORTE, PORTE6);
  } else {
    sbi(PORTE, PORTE6);
  }
}

// Escribe un caracter Por pantalla.
// valor --> Código 8 bits con el caracter a imprimir
void write(byte valor) {
  isBusy();
  sbi(PORTB, PORTB6);  //RS = 1
  cbi(PORTB, PORTB5);  // R/W = 0
  cargarDatos(valor);
  sbi(PORTB, PORTB4);  //E=1
  delayMicroseconds(1);
  cbi(PORTB, PORTB4);  //E=0
  delayMicroseconds(37);
}

//Imprime por pantalla un String

void printDisp(char* frase) {
  int i = 0;
  while (frase[i] != '\0') {
    write(frase[i]);
    i++;
  }
}

//Usa las Instrucciones del lcd
// valor --> Código de la instrucción en byte
// timeout --> duración de la operacion
void comando(byte valor, int timeout) {
  cbi(PORTB, PORTB6);  //RS = 0
  cbi(PORTB, PORTB5);  //R/W = 0

  cargarDatos(valor);

  sbi(PORTB, PORTB4);  // E = 1
  delayMicroseconds(1);
  cbi(PORTB, PORTB4);  // E = 0

  delayMicroseconds(timeout);
}
void comando(byte valor) {
  isBusy();
  cbi(PORTB, PORTB6);  //RS = 0
  cbi(PORTB, PORTB5);  //R/W = 0

  cargarDatos(valor);

  sbi(PORTB, PORTB4);  // E = 1
  delayMicroseconds(1);
  cbi(PORTB, PORTB4);  // E = 0
}
void clear() {
  comando(0x01);
}

void home() {
  // 0x02 --> 0000 001 - (Return home): DDRAM a 0 y deshace el desplazamiento
  comando(0x02);
}

void setCursor(byte columna, byte fila) {
  //Guarda las direcciones de inicio de cada fila
  // 0x00 --> 0; 0x40 --> 64; 0x14 --> 20; 0x54 --> 84
  const byte filas[4] = {
    0x00, 0x40, 0x14, 0x54
  };

  if (fila >= 4) return;
  byte direccion = filas[fila] + columna;
  //Hace OR con 0x80 (0010000000) + dir en bits --> 0x80: Entra en SET DDRAM ADDRESS
  byte codInstruccion = 0x80 | direccion;
  comando(codInstruccion);
}

void scrollDisplayLeft() {
  // 0x18 --> 0001 1 0 xx (Cursor or display shift) (0001 S/C R/L - -)
  comando(0x18);
}

void scrollDisplayRight() {
  comando(0x1C);
}

void cursor() {
  sbi(estadoDisplay, 1);
  comando(estadoDisplay);
}

void noCursor() {
  cbi(estadoDisplay, 1);
  comando(estadoDisplay);
}

void blink() {
  sbi(estadoDisplay, 0);
  comando(estadoDisplay);
}

void noBlink() {
  cbi(estadoDisplay, 0);
  comando(estadoDisplay);
}

void display() {
  sbi(estadoDisplay, 2);
  comando(estadoDisplay);
}

void noDisplay() {
  cbi(estadoDisplay, 2);
  comando(estadoDisplay);
}

void autoscroll() {
  sbi(estadoEntrada, 0);
  comando(estadoEntrada);
}

void noAutoscroll() {
  cbi(estadoEntrada, 0);
  comando(estadoEntrada);
}

void setmode() {
  delay(16);
  // modo de 8 bits
  comando(0x30, 4103);
  comando(0x30, 100);
  comando(0x30, 100);

  comando(0x38, 40);
  comando(0x38, 40);
  noDisplay();
  clear();
  comando(0x6);
}



void reset() {
  sbi(DDRB, DDB6);  // RS
  sbi(DDRB, DDB5);  //RW
  sbi(DDRB, DDB4);  //E
  setIO(true);
  clear(); //supuestamente no hace falta
  setmode();
  display();
  noCursor();
  noBlink();
}
void isBusy() {
  setIO(false);
  cbi(PORTB, PORTB6);    // RS
  sbi(PORTB, PORTB5);    //Rw
  sbi(PORTB, PORTB4);    //E
  delayMicroseconds(1);  // por que se supone que tarda 360ns en detectar E
  // mirar si hace falta ir modificando E dentro del bucle para que funcione
  while (((PIND & (1 << PIND2)) != 0) == 1) {}

  cbi(PORTB, PORTB6);  // RS
  cbi(PORTB, PORTB4);  //E
  cbi(PORTB, PORTB5);  //Rw
                       //
  setIO(true);
}



void loop() {
  int i;
  int j;

  clear();  // borra el display
  printDisp("1 hello, world!");
  setCursor(0, 1);  // Fila 1 (equivalente a dirección DDRAM 0x40 / 64)
  printDisp("2 hello, world!");
  setCursor(0, 2);  // Fila 2 (equivalente a dirección DDRAM 0x14 / 20)
  printDisp("3 hola ol");
  write(0xE3);  // Caracter especial epsilon
  printDisp("!");
  setCursor(0, 3);  // Fila 3 (equivalente a dirección DDRAM 0x54 / 84)
  printDisp("4 Vamonos de ca");
  write(0xEE);  // Caracter Ñ
  printDisp("as?");
  delay(1500);

  

  for (i = 0; i < 20; i++) {
    scrollDisplayLeft();
    delay(500);
  }
  delay(500);

  clear();
  for (i = 0xe0; i < 0xe0 + 16; i++) {
    write(i);
    delay(100);
  }
  setCursor(0, 1);
  for (i = 0xf0; i < 0xf0 + 15; i++) {
    write(i);
    delay(100);
  }
  write(i);

  delay(500);


  clear();
  delay(500);
  printDisp("1 hello, world!");
  setCursor(0, 1);
  printDisp("2 Vamos de ca");
  delay(500);
  cursor();
  //autoscroll();
  write(0xEE);
  write('a');
  delay(500);
  write('s');
  delay(500);
  write('?');
  delay(500);
  write('?');
  delay(500);
  write('?');
  delay(500);
  write('?');
  delay(500);
  noAutoscroll();

  clear();
  setCursor(0, 2);
  for (i = 0xe0; i < 0xe0 + 16; i++) {
    write(i);
  }
  setCursor(0, 3);
  for (j = 0xf0; j < 0xf0 + 16; j++) {
    write(j % 256);
    delay(100);
  }


  setCursor(0,0);

  for (j = 0; j < 3; j++) {
    delay(500);
    for (i = 0; i < 20; i++) {
      scrollDisplayLeft();
    }
    delay(500);
    for (i = 0; i < 20; i++) {
      scrollDisplayRight();
    }
  }

  delay(500);

  cursor();

  for (i = 0; i < 16; i++) {
    setCursor(i, 0);
    delay(200);
  }
  for (i = 15; i >= 1; i--) {
    setCursor(i, 0);
    delay(200);
  }
  setCursor(i, 0);
  delay(200);
  for (i = 0; i < 16; i++) {
    setCursor(i, 1);
    delay(200);
  }
  for (i = 15; i >= 0; i--) {
    setCursor(i, 1);
    delay(200);
  }


  blink();
  for (j = 0; j < 1; j++) {
    for (i = 0; i < 8; i++) {
      setCursor(i, 0);
      delay(500);
    }
    for (i = 7; i >= 0; i--) {
      setCursor(i, 1);
      delay(500);
    }
  }
  noBlink();
  clear();


  char s1[21];
  char s2[21];
  char s3[21];

  byte h = 3, m = 23, s = 7, c = 85;

  clear();

  for (j = 0; j < 9; j++) {
    setCursor(0, 0);
    sprintf(s1, "hora %2d:%02d:%02d:%02d", h++, m++, s++, c--);
    printDisp(s1);
    delay(1000);
  }

  sprintf(s3, "millis= %u", millis());
  sprintf(s2, "ms/us= %s", dtostrf((float)micros() / millis(), 9, 3, s3));

  setCursor(0, 2);
  printDisp(s3);

  setCursor(0, 1);
  printDisp(s2);
  delay(500);
}


//void loop() {
//byte i;
// Programa a Completar
/*
  lcd.clear(); // borra el display
  lcd.print("1 hello, world!");
  lcd.setCursor(64,0);
  lcd.print("2 hello, world!");
  lcd.setCursor(20,0);
  lcd.print("3 hola ol");
  lcd.write(0xE3);  // para escribir el caracter especial epsilon
  lcd.print("!");
  lcd.setCursor(84,0);
  lcd.print("4 Vamonos de ca");
  lcd.write(0xEE); // caracter Ñ
  lcd.print("as?");
  delay(1000);
  */
/*
  //Programa
  comando(0x01, 1520);           //lcd.clear()
  printDisp("1 hello, world!");  // lcd.print()
  setCursor(64, 0);
  printDisp("2 hello world!");
  setCursor(20, 0);
  printDisp("3 hola ol");
  write(0xE3);
  printDisp("!");
  setCursor(84, 0);
  printDisp("4 Vamonos de ca");
  write(0xEE);
  printDisp("as?");
  delay(1000);
*/
/*

  for (i = 0; i < 20; i++) {
    scrollDisplayLeft();
    delay(500);
  }
  delay(1000);


  for (i = 0; i < 20; i++) {
    scrollDisplayRight();
    delay(500);
  }
  delay(1000);
*/



/*lcd.clear();
  for(i=0xe0;i<0xe0+16;i++){
    lcd.write(i);
    delay(100);
  }
  lcd.setCursor(64,0);
  for(i=0xf0;i<0xf0+15;i++){
    lcd.write(i);
    delay(100);
  }
  lcd.write(i);


  delay(1000);
*/
/*
  comando(0x01, 1520);
  for (i = 0xe0; i < 0xe0 + 16; i++) {
    write(i);
    delay(100);
  }
  setCursor(64, 0);
  for (i = 0xf0; i < 0xf0 + 15; i++) {
    write(i);
    delay(100);
  }
  write(i);
  delay(1000);

*/
/*
  clear();

  printDisp("1 hello, world!");
  setCursor(64, 0);
  printDisp("2 Vamos de ca");
  delay(5000);
  cursor();
  autoscroll();
  write(0xEE);
  write('a');
  delay(500);
  write('s');
  delay(500);
  printDisp('?');
  delay(500);
  write('?');
  delay(500);
  write('?');
  delay(500);
  write('?');
  delay(500);
  noAutoscroll();
  */

//}
