#define sbi(port, bit) (port) |= (1 << (bit));   // setbit
#define cbi(port, bit) (port) &= ~(1 << (bit));  //clearbit
#define xbi(port, bit) (port) ^= (1 << (bit));

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  while (!Serial) {}
  Serial.println("Setup");
  noInterrupts();
  sbi(DDRC, DDC7);
  cbi(DDRD, DDD0);  
  sbi(PORTD, PORTD0); // pull up
  attachInterrupt(0, rti_int0_fb, RISING);
  interrupts();
}
volatile unsigned long num_ints = 0;

void rti_int0_fb() {
  num_ints++;
  xbi(PORTC, PORTC7);
}
void loop() {
  unsigned long num_ints_old = 0;
  unsigned long num_ints_new = 0;
  unsigned long segundos = 0;
  char s[100];
  Serial.println("Loop");

  // put your main code here, to run repeatedly:
  while (true) {
    num_ints_new = num_ints;
    if (num_ints_new != num_ints_old){
      sprintf(s,"millis: %lu  ints_old: %lu  ints_new: %lu , ints: %lu (%id)",millis(),num_ints_old,num_ints_new,num_ints , (num_ints - num_ints_new));
      Serial.println(s);
      num_ints_old= num_ints_new;
    }
    else{
      if((millis()/1000) > segundos){
         sprintf(s,"segundos: %lu ",segundos);
         Serial.println(s);
      }
    }
  }
}