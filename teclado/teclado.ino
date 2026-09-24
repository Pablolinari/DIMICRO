#define sbi(port,bit)  (port) |= (1<<(bit)); // setbit 
#define cbi(port,bit)  (port) &= ~(1<<(bit)); //clearbit
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(57600);
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0,INPUT);
  //Serial.println("Prueba de teclado");

}
int LeerTeclado(){
  int valor;
  int boton;
  while(valor = analogRead(A0) >= 1000){valor = 0;}
  valor = analogRead(A0);

  if(valor>=0 && valor<=73){
    return 1;
  }
  else if ((valor>=73 && valor<=226)){
    return 2;
  }
    else if ((valor>=226 && valor<=401)){
    return 3;
  }
    else if ((valor>=401 && valor<=546)){
    return 4;
  }
    else if ((valor>=546 && valor<=890)){
    return 5;
  }


}
// the loop function runs over and over again forever
void loop() {
  int valor;
  int tecla;
  int i = 0;
  while(true){

    Serial.print(i++);
    Serial.print("  Tecla pulsada ....");
    valor = analogRead(A0);
    Serial.print(tecla = LeerTeclado());
    Serial.print("(");
    Serial.print(valor);
    Serial.print(")      ");
    Serial.println("Procesando tecla ......");
  }
}
