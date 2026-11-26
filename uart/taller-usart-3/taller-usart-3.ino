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

volatile unsigned char t_in;            // TX buffer in index
volatile unsigned char t_out;           // TX buffer out index

volatile unsigned char r_in;            // RX buffer in index
volatile unsigned char r_out;           // RX buffer out index
volatile unsigned char putting=0x00;
volatile unsigned char echo=0x00;
volatile unsigned char echo_char=0x00;

volatile unsigned char linea=0x00;

unsigned char s[RBUFSIZE];
unsigned char so[RBUFSIZE];
unsigned char cmd[RBUFSIZE];
unsigned char pars[RBUFSIZE];
int n;
int cont=0;
unsigned char led=0;


// --------------------
// -- Initialization --
// --------------------

// Same as in Demo 2
void UART_first_init(void) {
  return;
}


// ------------------
// -- Transmission --
// ------------------

// @todo: change to match UART1 registers from Arduino Leonardo
ISR(USART1_UDRE_vect){
  return;
}

char tbuflen(void) {
//****************
// Retrieve pending chars in TX buffer
//
	return(t_in - t_out);
}

// @todo: change to match UART1 registers from Arduino Leonardo
int USART_putchar(char c) {

}

void print_msg(unsigned char *msg){
	int i=0;
	while(msg[i]) {
	  USART_putchar(msg[i++]);
  }
}

void prompt(){
  print_msg("Dmc > ");
}


// ---------------
// -- Reception --
// ---------------

/***************************************************************************//**
 * A R D U I N O   F U N C T I O N S
 ******************************************************************************/

// UART 1 is initialized by our own function
void setup() {
  led_setup();
  UART_first_init();				// First init UART 1
  Serial.begin(57600);      // Then, init USB CDC

  while(!Serial) {
    // Do nothing, wait for Serial to be ready
  }

  led_on();

  print_msg("Disenno con microcontroladores\r\n\0");
  print_msg("Leds corriendo.....\r\n\0");
  prompt();
}

// Same as in Demo 1, now printing with our own functions
void loop() {
  static int counter = 0;

  Serial.print("Hello World S0: ");
  Serial.println(counter);

  char so[TBUFSIZE];
  sprintf(so, "Hello Workd S1: %d \r\n", counter);
  print_msg(so);

  counter+=1;
  led_toggle();
  delay(2000);
}