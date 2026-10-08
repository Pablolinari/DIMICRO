#include <LiquidCrystal.h>

#define sbi(port, bit) (port) |= (1 << (bit));   // setbit
#define cbi(port, bit) (port) &= ~(1 << (bit));  //clearbit
// the setup function runs once when you press reset or power the board
LiquidCrystal lcd(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
void setup() {
  lcd.begin(20, 4);  // indica 4 lineas de 20 caracteres en el display
  Serial.begin(57600);
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  sbi(DDRB, DDB6);
  sbi(DDRB, DDB5);
  sbi(DDRD, DDD2);
  sbi(DDRD, DDD3);
  sbi(DDRD, DDD1);
  sbi(DDRD, DDD0);
  sbi(DDRD, DDD4);
  sbi(DDRC, DDC6);
  sbi(DDRD, DDD7);
  sbi(DDRE, DDE6);
}


//funcion que sustituye la funcion write

// parametro = dato de 8bits
void rellenarpuertos(byte valor) {
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
void write(byte valor) {
  sbi(PORTB, PORTB6);
  cbi(PORTB, PORTB5);
  rellenarpuertos(valor);
  sbi(PORTB, PORTB4);
  delayMicroseconds(1);
  cbi(PORTB, PORTB4);
  delayMicroseconds(37);
}

void printpant(char* frase) {
  int i = 0;
  while (frase[i]) {
    write(frase[i]);
    i++;
  }
}

//poner como parametro timeout y comando
/*
funcion parecida a write para mandar comandos que se distinguen por rs , y el tiempo se variable 

hay 3 funciones que tienen una orden con 3 parametros , 


*/

void comando(byte valor, int timeout) {
  cbi(PORTB, PORTB6);
  cbi(PORTB, PORTB5);

  rellenarpuertos(valor);

  sbi(PORTB, PORTB4);
  delayMicroseconds(1);
  cbi(PORTB, PORTB4);
  delayMicroseconds(37);
  delayMicroseconds(timeout);
}

void clear() {
  // ver si funciona 
  comando(0x80, 1700);
}

// the loop function runs over and over again forever
void loop() {
  byte i;
  int j;

  //lcd.clear();  // borra el display
  //clear();
  lcd.print("hola");
  //printpant("hola");
  write(0xE3);  // para escribir el caracter especial epsilon

  delay(1000);
  /*
  for (i = 0; i < 20; i++) {
    lcd.scrollDisplayLeft();
    delay(500);
  }
  delay(1000);
*/

  /*
  lcd.clear();
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
  lcd.clear();

  lcd.print("1 hello, world!");
  lcd.setCursor(64,0);
  lcd.print("2 Vamos de ca");
  delay(5000);
  lcd.cursor();
  lcd.autoscroll();
  lcd.write(0xEE);
  lcd.print('a');
  delay(500);
  lcd.print('s');
  delay(500);
  lcd.print('?');
  delay(500);
  lcd.print('?');
  delay(500);
  lcd.print('?');
  delay(500);
  lcd.print('?');
  delay(500);
  lcd.noAutoscroll();


*/



  /*
  lcd.setCursor(20,0);
  for(i=0xe0;i<0xe0+16;i++){
    lcd.write(i);
  }
  lcd.setCursor(84,0);
  for(j=0xf0;j<0xf0+16;j++){
    lcd.write(j%256);
    delay(100);
  }
  lcd.home();
  for(j=0;j<3;j++){
    delay(1000);
    for(i=0;i<20;i++){
      lcd.scrollDisplayLeft();
    }
    delay(1000);
    for(i=0;i<20;i++){
      lcd.scrollDisplayRight();
    }
  }
*/



  /*

  delay(1000);


  lcd.cursor();
  for(j=0;j<1;j++){
    for(i=0;i<16;i++){
      lcd.setCursor(i,0);
      delay(200);
    }
    for(i=15;i>=1;i--){
      lcd.setCursor(i,0);
      delay(200);
    }
    lcd.setCursor(i,0);
    delay(200);
    for(i=64;i<80;i++){
      lcd.setCursor(i,0);
      delay(200);
    }
    for(i=79;i>=64;i--){
      lcd.setCursor(i,0);
      delay(200);
    }
  }

  lcd.blink();
  for(j=0;j<1;j++){
    for(i=0;i<8;i++){
      lcd.setCursor(i,0);
      delay(500);
    }
    for(i=71;i>=64;i--){
      lcd.setCursor(i,0);
      delay(500);
    }
  }
  lcd.noBlink();
*/
  // parpadeo del display
  /*
  for(j=0;j<2;j++){
    lcd.noDisplay();
    delay(2000);
    lcd.display();
    delay(2000);

  }
*/
  /*
  char s1[21];
  char s2[21];
  char s3[21];

  byte h=3,m=23,s=7,c=85;

  lcd.clear();

  for(j=0;j<9;j++){
    lcd.home();
    sprintf(s1,"hora %2d:%02d:%02d:%02",h++,m++,s++,c--);
    //lcd.priint(s1);
    i=0;
    while(s1[i]){
      lcd.print(s1[i++]);
    }
    delay(1000);
  }
  sprintf(s3,"millis= %u",millis());

  sprintf(s2,"ms/us= %s",dtostrf((float)micros()/millis(),9,3,s3));

  lcd.setCursor(20,0);

  lcd.print(s3);

  lcd.setCursor(64,0);
  lcd.print(s2);
  delay(5000);
*/
}
