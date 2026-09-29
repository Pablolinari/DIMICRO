#define sbi(port, bit) (port) |= (1 << (bit));   // setbit
#define cbi(port, bit) (port) &= ~(1 << (bit));  //clearbit
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(57600);
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT);
  //Serial.println("Prueba de teclado");
}
int LeerTeclado() {
  int valor;
  int boton;
  while (valor = analogRead(A0) >= 1000) { valor = 0; }
  valor = analogRead(A0);

  if (valor >= 0 && valor <= 73) {
    return 1;
  } else if ((valor >= 73 && valor <= 226)) {
    return 2;
  } else if ((valor >= 226 && valor <= 401)) {
    return 3;
  } else if ((valor >= 401 && valor <= 546)) {
    return 4;
  } else if ((valor >= 546 && valor <= 890)) {
    return 5;
  }
}

int LeerTeclado_filtroespera() {
  int valor;
  int boton = 0;
  int filtro = 100;
  int f1, f2, f3, f4, f5 = filtro;
  while (boton == 0) {
    valor = analogRead(A0);
    if (valor >= 1000) {
      boton = 0;
      f1 = filtro;
      f2 = filtro;
      f3 = filtro;
      f4 = filtro;
      f5 = filtro;
    } else if (valor >= 0 && valor <= 73) {
      f1--;
      f2 = filtro;
      f3 = filtro;
      f4 = filtro;
      f5 = filtro;

    } else if ((valor >= 73 && valor <= 226)) {
      f2--;
      f1 = filtro;
      f3 = filtro;
      f4 = filtro;
      f5 = filtro;
    } else if ((valor >= 226 && valor <= 401)) {
      f3--;
      f2 = filtro;
      f1 = filtro;
      f4 = filtro;
      f5 = filtro;
    } else if ((valor >= 401 && valor <= 546)) {
      f4--;
      f2 = filtro;
      f3 = filtro;
      f1 = filtro;
      f5 = filtro;
    } else if ((valor >= 546 && valor <= 890)) {
      f5--;
      f2 = filtro;
      f3 = filtro;
      f4 = filtro;
      f1 = filtro;
    }
    if (f1 == 0) {
      while (analogRead(A0) >= 0 && analogRead(A0) <= 73) {}
      return 1;
    }
    if (f2 == 0) {
      while (analogRead(A0) >= 73 && analogRead(A0) <= 226) {}
      return 2;
    }
    if (f3 == 0) {
      while (analogRead(A0) >= 226 && analogRead(A0) <= 401) {}
      return 3;
    }
    if (f4 == 0) {
      while (analogRead(A0) >= 401 && analogRead(A0) <= 546) {}
      return 4;
    }
    if (f5 == 0) {
      while (analogRead(A0) >= 546 && analogRead(A0) <= 890) {}
      return 5;
    }
  }
}


// the loop function runs over and over again forever
void loop() {
  int valor;
  int tecla;
  int i = 0;
  while (true) {

    Serial.print(i++);
    Serial.print("  Tecla pulsada ....");
    valor = analogRead(A0);
    Serial.print(tecla = LeerTeclado_filtroespera());
    Serial.print("(");
    Serial.print(valor);
    Serial.print(")      ");
    Serial.println("Procesando tecla ......");
  }
}
