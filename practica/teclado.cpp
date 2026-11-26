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
void TecladoLibre() {
  int filtro = 20;
  int cuenta = filtro;

  while (cuenta > 0) {
    int valor = analogRead(A0);
    if (valor >= 1000) {
      cuenta--;
    } else {
      cuenta = filtro;
    }
  }
}
int LeerTeclado_filtroespera() {
  int valor;
  int boton = 0;
  int filtro = 100;
  int f1, f2, f3, f4, f5 = filtro;

  TecladoLibre();
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
      return 1;
    }
    if (f2 == 0) {
      return 2;
    }
    if (f3 == 0) {
      return 3;
    }
    if (f4 == 0) {
      return 4;
    }
    if (f5 == 0) {
      return 5;
    }
  }
}
int RepetirTecla(int tecla, int espera) {
  int boton = 0;
  int f1 = 0, f2 = 0, f3 = 0, f4 = 0, f5 = 0;
  for (int i = 0; i < espera; i++) {
    int valor = analogRead(A0);
    boton = 0;
    if (tecla == 1 && valor >= 0 && valor <= 73) {
      f1++;
      boton = 1;
    } else if (tecla == 2 && valor >= 73 && valor <= 226) {
      f2++;
      boton = 2;
    } else if (tecla == 3 && valor >= 226 && valor <= 401) {
      f3++;
      boton = 3;
    } else if (tecla == 4 && valor >= 401 && valor <= 546) {
      f4++;
      boton = 4;;
    } else if (tecla == 5 && valor >= 546 && valor <= 890) {
      f5++;
      boton = 5;
    }
    if (boton != tecla) {
      boton = 0;
      break;
    }
    delay(1);
  }
  return boton;
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

    int repe = 800;
    while (tecla == RepetirTecla(tecla, repe)) {
      Serial.println();
      Serial.print("  Tecla pulsada ....");
      Serial.print(tecla);
      Serial.println("repetida Procesando tecla ......");
      repe = 200;
    }
  }
}
