// =============================================================================
//  config.h  -  Configuración central de la práctica
// -----------------------------------------------------------------------------
//  Rellena / revisa los valores marcados con  TODO.
//  Los que ya tienen valor están sacados de tu código actual (lcd.cpp,
//  teclado.cpp, motor.cpp); comprueba que siguen siendo correctos.
//  Placa: ATmega32U4 (Arduino Leonardo / Micro), por los registros que usas.
// =============================================================================
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// -----------------------------------------------------------------------------
//  Macros de manejo de bits (úsalas desde aquí y bórralas de los .cpp)
// -----------------------------------------------------------------------------
#define sbi(port, bit) ((port) |= (1 << (bit)))   // set bit
#define cbi(port, bit) ((port) &= ~(1 << (bit)))  // clear bit


#define SERIAL_BAUDRATE      57600       // TODO: motor.cpp usa 9600, el resto 57600

// =============================================================================
//  LCD (HD44780, modo 8 bits, acceso directo a registros)
// =============================================================================
#define LCD_COLUMNAS         20
#define LCD_FILAS            4

// Líneas de control  (puerto B)
#define LCD_RS_DDR   DDRB
#define LCD_RS_PORT  PORTB
#define LCD_RS_BIT   PORTB6              // pin 10
#define LCD_RW_DDR   DDRB
#define LCD_RW_PORT  PORTB
#define LCD_RW_BIT   PORTB5              // pin 9
#define LCD_E_DDR    DDRB
#define LCD_E_PORT   PORTB
#define LCD_E_BIT    PORTB4              // pin 8

// Bus de datos D7..D0 (puerto / bit / pin Arduino)
//   D7 -> PD2 (pin 0)   D6 -> PD3 (pin 1)   D5 -> PD1 (pin 2)   D4 -> PD0 (pin 3)
//   D3 -> PD4 (pin 4)   D2 -> PC6 (pin 5)   D1 -> PD7 (pin 6)   D0 -> PE6 (pin 7)
// Busy flag (D7) se lee en:
#define LCD_BUSY_PIN_REG     PIND
#define LCD_BUSY_BIT         PIND2

// =============================================================================
//  TECLADO ANALÓGICO (5 botones en divisor resistivo)
// =============================================================================
#define TECLADO_PIN          A0

// Umbrales del ADC (límite superior de cada tecla)
#define TECLA1_MAX           73
#define TECLA2_MAX           226
#define TECLA3_MAX           401
#define TECLA4_MAX           546
#define TECLA5_MAX           890
#define TECLADO_LIBRE_MIN    1000        // >= esto = ninguna tecla pulsada

// Antirrebote / autorepetición
#define TECLADO_FILTRO_LIBRE     20      // lecturas seguidas "libre" para soltar
#define TECLADO_FILTRO_PULSADA   100     // lecturas seguidas iguales para aceptar
#define TECLADO_REPE_PRIMERA     800     // ms hasta la 1ª repetición
#define TECLADO_REPE_SIGUIENTES  200     // ms entre repeticiones

// Función de cada tecla   TODO: asigna según tu placa
#define TECLA_NINGUNA        0
#define TECLA_ARRIBA         1           // TODO
#define TECLA_ABAJO          2           // TODO
#define TECLA_IZQUIERDA      3           // TODO
#define TECLA_DERECHA        4           // TODO
#define TECLA_OK             5           // TODO

// =============================================================================
//  MOTOR DC (puente H)
// =============================================================================
// ¡OJO! Los pines que usa motor.cpp (1,2,3,5,6) coinciden con el bus de datos
// del LCD (pines 0-7). Si usas los dos a la vez tienes que mover el motor/encoder.
#define MOTOR_PIN_IN1        3           // TODO: cambiar (conflicto con LCD)
#define MOTOR_PIN_IN2        5           // TODO: cambiar (conflicto con LCD)
#define MOTOR_PIN_EN         6           // TODO: cambiar (conflicto con LCD) - debe ser PWM

#define MOTOR_PWM_MIN        0           // TODO: PWM por debajo del cual no arranca
#define MOTOR_PWM_MAX        255
#define MOTOR_SENTIDO_INICIAL 1          // 1 = derecha, 0 = izquierda

// =============================================================================
//  ENCODER
// =============================================================================
#define ENCODER_PIN_A        2           // TODO: cambiar (conflicto con LCD) - mejor pin con interrupción
#define ENCODER_PIN_B        1           // TODO: cambiar (conflicto con LCD)

// Pulsos por vuelta del eje de salida (float: en motor.cpp está como int y se trunca a 823)
#define ENCODER_PPR          823.1f
#define ENCODER_FLANCOS      1           // 1 = cuentas solo cambios de A, 2 = A y B, 4 = cuadratura completa

// Periodo de medida de velocidad
#define VELOCIDAD_PERIODO_MS 100         // ventana de conteo de pulsos

// =============================================================================
//  CONTROL PID  (librería PID_v1)
// =============================================================================
#define PID_KP               0.0         // TODO
#define PID_KI               0.0         // TODO
#define PID_KD               0.0         // TODO

#define PID_SAMPLE_TIME_MS   100         // TODO: igual o múltiplo de VELOCIDAD_PERIODO_MS
#define PID_OUT_MIN          MOTOR_PWM_MIN
#define PID_OUT_MAX          MOTOR_PWM_MAX
#define PID_DIRECCION        DIRECT      // DIRECT o REVERSE

// Consigna (setpoint) en RPM
#define RPM_SETPOINT_INICIAL 0           // TODO
#define RPM_MIN              0           // TODO
#define RPM_MAX              0           // TODO: RPM máximas reales del motor
#define RPM_PASO             10          // TODO: incremento por pulsación de tecla

// Paso al modificar Kp/Ki/Kd desde el menú
#define PID_PASO_KP          0.1         // TODO
#define PID_PASO_KI          0.1         // TODO
#define PID_PASO_KD          0.01        // TODO

// =============================================================================
//  INTERFAZ DE USUARIO
// =============================================================================
#define UI_REFRESCO_MS       250         // TODO: cada cuánto se repinta el LCD

#endif // CONFIG_H
