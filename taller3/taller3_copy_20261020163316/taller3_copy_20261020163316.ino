#define sbi(port, bit) (port) |= (1 << (bit));   // setbit
#define cbi(port, bit) (port) &= ~(1 << (bit));  //clearbit
// the setup function runs once when you press reset or power the board
int ultimoEstadoA;
int ultimoEstadoB;
int direccion = 1; //derecha 
const int PPR =823.1;
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);

  pinMode(1, INPUT_PULLUP);  //encoder b
  pinMode(2, INPUT_PULLUP);  //encoder a
  pinMode(3, OUTPUT);        //IN1
  pinMode(5, OUTPUT);        //IN2
  pinMode(6,OUTPUT);         // enable
  ultimoEstadoA = digitalRead(2);
  ultimoEstadoB = digitalRead(1);
  digitalWrite(3, direccion);
  digitalWrite(5, !direccion);
  analogWrite(6,100);
  //Serial.println("Prueba de teclado");
}
long contadorA = 0;
long contadorB = 0;
unsigned long tiempoAnterior = 0;


void loop() {
  int estadoA = digitalRead(2);
  int estadoB = digitalRead(1);

  if (estadoA != ultimoEstadoA) {
    contadorA++;
    ultimoEstadoA = estadoA;
  }

  if (estadoB != ultimoEstadoB) {
    contadorB++;
    ultimoEstadoB = estadoB;
  }


  long int antes = millis();
  unsigned int pulsovuelta = 0;
  //int intervalo =100 //
  while (millis() - antes < 100) {
    int estadoA = digitalRead(2);
    if (estadoA != ultimoEstadoA) {
      pulsovuelta++;
      ultimoEstadoA = estadoA;
    }

  }
  double pulsomin = 600*pulsovuelta;
  double velocidad = pulsomin/PPR;
  delay(900);
  Serial.print("Pulsos en 10 seg: ");
  Serial.print(pulsovuelta);
  Serial.print("       RPM ");

  Serial.println(velocidad);

}
