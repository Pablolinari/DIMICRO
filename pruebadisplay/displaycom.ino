#include <LiquidCrystal.h>

#define sbi(port, bit) (port) |= (1 << (bit))   //setbit
#define cbi(port, bit) (port) &= ~(1 << (bit))  //clearbit

//LiquidCrystal lcd(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
//LiquidCrystal lcd(RS,RW,E,D0,D1,D2,D3,D4,D5,D6,D7); --> Indicamos a que pines tenemos conectados cada entrada

void setup(){
  // put your setup code here, to run once:
  //lcd.begin(20, 4);  // Indica 4 lineas de 20 caracteres
  Serial.begin(57600);

  //Incializamos los pines como salida
  //pinMode(LED_BUILTIN, OUTPUT)
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

  reset();
}


byte estadoDisplay = 0x0C;  // 0000 1 D C B --> Display on/off control
byte estadoEntrada = 0x06; // 

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

void clear() {
  comando(0x01, 1520);
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
  comando(codInstruccion, 40);
}

void scrollDisplayLeft() {
  // 0x18 --> 0001 1 0 xx (Cursor or display shift) (0001 S/C R/L - -)
  comando(0x18, 50);
}

void scrollDisplayRight() {
  comando(0x1C, 50);
}

void cursor() {
  sbi(estadoDisplay, 1);
  comando(estadoDisplay, 50);
}

void noCursor() {
  cbi(estadoDisplay, 1);
  comando(estadoDisplay, 50);
}

void blink() {
  sbi(estadoDisplay, 0);
  comando(estadoDisplay, 50);
}

void noBlink() {
  cbi(estadoDisplay, 0);
  comando(estadoDisplay, 50);
}

void display() {
  sbi(estadoDisplay, 2);
  comando(estadoDisplay, 50);
}

void noDisplay() {
  cbi(estadoDisplay, 2);
  comando(estadoDisplay, 50);
}

void autoscroll() {
  sbi(estadoEntrada, 0);
  comando(estadoEntrada, 50);
}

void noAutoscroll() {
  cbi(estadoEntrada, 0);
  comando(estadoEntrada, 50);
}

void setmode(){
  delay(16);
  // modo de 8 bits
  comando(0x30,4103);
  comando(0x30,100);
  comando(0x30,100);

  comando(0x38,40);
  comando(0x38,40);
  noDisplay();
  clear();
  comando(0x6,40);

}



void reset(){
  sbi(PORTD, PORTD2);
  delay(12);

  clear();
  setmode();
  display();
  cursor();
  noBlink();

}





void loop() {
  byte i;
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
  /*
   for(i=0;i<20;i++){
    lcd.scrollDisplayLeft();
    delay(500);
  }
  delay(1000);
*/
  for (i = 0; i < 20; i++) {
    scrollDisplayRight();
    delay(500);
  }
  delay(1000);




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
}
