// Demo 3: test the transmission TX procedure based on
//         code from "eje_usart_vmlab/usart/usart.c"

/***************************************************************************//**
 * L E D   F U N C T I O N S
 ******************************************************************************/

#define LED_DDRX   (DDRC)
#define LED_DDRXn  (DDC7)
#define LED_PORTX  (PORTC)
#define LED_PORTXn (PORTC7)

static void led_setup() {
  // Configures the LED pin as an output I/O port.
  LED_DDRX |= (1<<LED_DDRXn);
}

static void led_off() {
  LED_PORTX &= ~(1<<LED_PORTXn); //< turn OFF (sets to 1, 5V)
}

static void led_on() {
  LED_PORTX |= (1<<LED_PORTXn);  //< turn ON  (sets to 0, 0V)
}

static void led_toggle() {
  static bool on = false;
  if (on) {
    led_off();
    on = false;
  } else {
    led_on();
    on = true;
  }
}

void leds(unsigned char l){
	static int counter = 1;
  if (counter % (10-l) == 0) {
    led_on();
  } else {
    led_off();
  }
  
  if (++counter == 10) {
    counter = 1;
  }
}

/***************************************************************************//**
 * U A R T   F U N C T I O N S
 ******************************************************************************/

// ---------------
// -- Variables --
// ---------------

// Buffer sizes must be 2^n
//
#define TBUFSIZE	64
#define RBUFSIZE	64

#define TMASK		(TBUFSIZE-1)
#define RMASK		(RBUFSIZE-1)

// Static variables
//
volatile unsigned char tbuf[TBUFSIZE];  // TX buffer
volatile unsigned char rbuf[RBUFSIZE];  // RX buffer

volatile unsigned char t_in  = 0;            // TX buffer in index
volatile unsigned char t_out = 0;           // TX buffer out index

volatile unsigned char r_in  = 0;            // RX buffer in index
volatile unsigned char r_out = 0;           // RX buffer out index
volatile unsigned char putting   = 0x00;
volatile unsigned char echo      = 0x00;
volatile unsigned char echo_char = 0x00;

volatile unsigned char linea = 0x00;

unsigned char s[RBUFSIZE];
unsigned char so[RBUFSIZE];
unsigned char cmd[RBUFSIZE];
unsigned char pars[RBUFSIZE];
int n;
int cont=0;

// --------------------
// -- Initialization --
// --------------------

// Same as in Demo 2/3
void UART_first_init(void) {

}

// ------------------
// -- Transmission --
// ------------------

// Same as in Demo 3
ISR(USART1_UDRE_vect){

}

// Same as in Demo 3
char tbuflen(void) {
//****************
// Retrieve pending chars in TX buffer
//
	return(t_in - t_out);
}

// Same as in Demo 3
int USART_putchar(char c) {

}

// Same as in Demo 3
void print_msg(unsigned char *msg){
	int i=0;
	while(msg[i]) {
	  USART_putchar(msg[i++]);
  }
}

// Same as in Demo 3
void prompt(){
  print_msg("Dmc > ");
}


// ---------------
// -- Reception --
// ---------------

// @todo Modificar con registros UART1
ISR(USART1_RX_vect) {
  return;
}

void limpia_linea() {
  int i;
	for(i=0;i<RBUFSIZE;i++)
		rbuf[i]=s[i]=cmd[i]=pars[i]=0x00;
	r_in=0;
	linea=0x00;
}

/***************************************************************************//**
 * A R D U I N O   F U N C T I O N S
 ******************************************************************************/

// UART 1 is initialized by our own function
void setup() {
  led_setup();
  UART_first_init();				// First init UART 1

  led_on();
  print_msg("Disenno con microcontroladores\r\n\0");
  print_msg("Leds corriendo.....\r\n\0");
  prompt();
}

// Same as in Demo 1, now printing with our own functions
void loop() {
  static int inc_led = 1;
  static int i = 1;

  if(linea) { // Queda a la espera de una línea disponible en rbuf.
    n=0;
    sscanf(rbuf, "%s %n", cmd, &n);  // Get text

    if (!strcmp(cmd, "led")) {
      if (!strcmp(rbuf+n, "start")) {           // Argumento start
          inc_led = 1;
          strcpy (so," leds corriendo... \r\n");
          print_msg(so);
      } else if (!strcmp(rbuf+n, "stop")) {     // Argumento stop
          inc_led = 0;
          strcpy (so, " leds parados... \r\n");
          print_msg(so);
      } else if (strlen(rbuf+n)==0) {           // Sin argumentos
        sprintf(so, "leds: %d \r\n", inc_led);
        print_msg(so);
      } else if ((i=atoi(rbuf+n))>=1 && i<=9) { // Detecta caracter entre 1 y 9
        inc_led=i;
        sprintf(so, "atenuación de leds: %d \r\n", i);
        print_msg(so);
      }	else {                                  // Argumento erroneo
              strcpy (so, "*** ERROR en parámetros\r\n");
              print_msg(so);
              strcpy (so, "uso: led [start | stop | 1..9] \r\n");
              print_msg(so);
      }
    } else if (strlen(cmd)!=0) {			          // Comando erroneo
          strcpy (so, "*** ERROR en comando\r\n");
          print_msg(so);
    }

    prompt();
    limpia_linea();
  }
  
  if (cont++==1000){
    cont=0;
    leds(inc_led);
  }
}