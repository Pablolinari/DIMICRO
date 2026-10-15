#define sbi(port, bit) (port) |= (1 << (bit));   // setbit
#define cbi(port, bit) (port) &= ~(1 << (bit));  //clearbit
// the setup function runs once when you press reset or power the board
int ultimoEstadoA;
int ultimoEstadoB;
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);

  pinMode(1, INPUT_PULLUP);  //encoder b
  pinMode(2, INPUT_PULLUP);  //encoder a
  pinMode(3, OUTPUT);        //IN1
  pinMode(5, OUTPUT);        //IN2
  ultimoEstadoA = digitalRead(2);
  ultimoEstadoB = digitalRead(1);
analogWrite(3, 255); // Velocidad media-alta
  digitalWrite(5, LOW);
  //Serial.println("Prueba de teclado");
}
long contadorA = 0;
long contadorB = 0;
unsigned long tiempoAnterior = 0;


void loop() {
  // 1. Leer el estado actual de los pines
  int estadoA = digitalRead(2);
  int estadoB = digitalRead(1);

  // 2. Si la señal A cambió, incrementamos su contador
  if (estadoA != ultimoEstadoA) {
    contadorA++;
    ultimoEstadoA = estadoA;
  }

  // 3. Si la señal B cambió, incrementamos su contador
  if (estadoB != ultimoEstadoB) {
    contadorB++;
    ultimoEstadoB = estadoB;
  }

  // 4. Cada 1 segundo (1000 ms), imprimir los resultados
  if (millis() - tiempoAnterior >= 1000) {
    tiempoAnterior = millis();

    Serial.print("Cambios A: ");
    Serial.print(contadorA);
    Serial.print(" | Cambios B: ");
    Serial.println(contadorB);
  }
}
