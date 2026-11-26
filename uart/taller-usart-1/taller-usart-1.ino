// Demo 1: test the hardware setup with the Serial library.

void setup() {
  Serial.begin(57600);
  Serial1.begin(115200);

  while(!Serial || !Serial1) {
    // Do nothing, wait for Serial and Serial1 to be ready
  }
}

void loop() {
  static int counter = 0;

  Serial.print("Hello World S0: ");
  Serial.println(counter);

  Serial1.print("Hello World S1: ");
  Serial1.println(counter);

  counter+=1;
  delay(2000);
}
