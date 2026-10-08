#include <LiquidCrystal.h>

#define sbi(port, bit) (port) |= (1 << (bit));   // setbit
#define cbi(port, bit) (port) &= ~(1 << (bit));  //clearbit
// the setup function runs once when you press reset or power the board
LiquidCrystal lcd(10,9,8,7,6,5,4,3,2,1,0);
void setup() {
  lcd.begin(20,4); // indica 4 lineas de 20 caracteres en el display
}

// the loop function runs over and over again forever
void loop() {
  byte i;
  int j;
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
  
  for(i=0;i<20;i++){
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

}
