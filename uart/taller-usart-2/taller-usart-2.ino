// Demo 2: test the initialization procedure based on
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

// @todo: change to match UART1 registers from Arduino Leonardo
//        Only transmission shall be activated.
//        Baud rate: 115200bps.
void UART_first_init(void) {
  return;
}

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
}

// Same as in Demo 1
void loop() {
  static int counter = 0;

  Serial.print("Hello World S0: ");
  Serial.println(counter);

  Serial1.print("Hello World S1: ");
  Serial1.println(counter);

  counter+=1;
  led_toggle();
  delay(2000);
}
