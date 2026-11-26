// =============================================================================
//  ui.h  -  Interfaz de usuario (display + teclado)
// -----------------------------------------------------------------------------
//  Desde fuera (practica.ino) solo se llama a:  uiInit()  y  uiActualizar().
//  El resto de funciones son internas de ui.cpp; se declaran aquí para tener
//  la lista completa a la vista.
//
//  Reglas: ui.cpp NO toca pines ni registros ni calcula el PID.
//          Solo usa lcd.h, teclado.h y control.h.
// =============================================================================
#ifndef UI_H
#define UI_H

#include "config.h"

// -----------------------------------------------------------------------------
//  Tipos
// -----------------------------------------------------------------------------

// Pantallas posibles (estados de la máquina de estados)
enum Pantalla {
  P_PRINCIPAL,      // objetivo, real, Kp/Ki/Kd, marcha/parado, teclado/pot
  P_MENU,           // lista de comandos
  P_EDITAR,         // editar un valor numérico
  P_MENSAJE         // aviso temporal ("Motor arrancado", "Reset hecho"...)
};

// Opciones del menú (comandos del enunciado)
enum OpcionMenu {
  OP_VELOCIDAD,
  OP_ACELERACION,
  OP_ARRANQUE,
  OP_PARADA,
  OP_PARAMETROS,    // Kp -> Ki -> Kd
  OP_POTENCIOMETRO, // alterna teclado / potenciómetro
  OP_RESET,
  OP_NUM_OPCIONES   // número de opciones (no es una opción)
};

// Valor que se está editando en P_EDITAR
enum Parametro {
  PARAM_VELOCIDAD,
  PARAM_ACELERACION,
  PARAM_KP,
  PARAM_KI,
  PARAM_KD
};

// -----------------------------------------------------------------------------
//  Funciones públicas (las que llama practica.ino)
// -----------------------------------------------------------------------------
void uiInit();                  // inicializa el LCD y muestra la pantalla principal
void uiActualizar();            // llamar en cada vuelta del loop(); NUNCA bloquea
void uiForzarRepintado();       // marca que hay que redibujar la pantalla actual

// -----------------------------------------------------------------------------
//  Navegación
// -----------------------------------------------------------------------------
void uiIrA(Pantalla nueva);     // cambia de pantalla y fuerza repintado

// -----------------------------------------------------------------------------
//  Gestión de teclas (una por pantalla)
// -----------------------------------------------------------------------------
void uiTeclasPrincipal(int tecla);  // OK -> menú
void uiTeclasMenu(int tecla);       // arriba/abajo mueven, OK ejecuta, izq vuelve
void uiTeclasEditar(int tecla);     // arriba/abajo cambian, der cambia paso,
                                    // OK guarda, izq cancela
void uiTeclasMensaje(int tecla);    // cualquier tecla cierra el mensaje

// -----------------------------------------------------------------------------
//  Dibujo (una por pantalla)
// -----------------------------------------------------------------------------
void uiDibujarPrincipal();
void uiDibujarMenu();
void uiDibujarEditar();
void uiDibujarMensaje();

void uiRefrescarMedidas();      // repinta solo los datos que cambian solos
                                // (rpm real, potenciómetro) sin borrar la pantalla

// -----------------------------------------------------------------------------
//  Acciones del menú
// -----------------------------------------------------------------------------
void uiEjecutarOpcion(OpcionMenu op);   // decide qué hace cada opción del menú

// -----------------------------------------------------------------------------
//  Edición genérica de valores
// -----------------------------------------------------------------------------
void uiEmpezarEdicion(Parametro p);     // copia el valor actual y fija min/max/paso
void uiCambiarValor(int sentido);       // +1 sube, -1 baja (respeta min/max)
void uiCambiarPaso();                   // rota el paso: 1 -> 10 -> 100 (o 0.01 -> 0.1 -> 1)
void uiGuardarEdicion();                // escribe el valor en el estado de control
void uiCancelarEdicion();               // descarta y vuelve al menú

// -----------------------------------------------------------------------------
//  Mensajes temporales (sin delay)
// -----------------------------------------------------------------------------
void uiMostrarMensaje(const char* texto, unsigned long duracionMs);
bool uiMensajeCaducado();               // true cuando ya pasó la duración

// -----------------------------------------------------------------------------
//  Utilidades de dibujo
// -----------------------------------------------------------------------------
void uiImprimirLinea(byte fila, const char* texto);  // escribe y rellena con
                                                     // espacios hasta LCD_COLUMNAS
void uiFormatearFloat(float valor, byte decimales, char* buffer, byte ancho);
                                                     // envoltorio de dtostrf()
const char* uiNombreOpcion(OpcionMenu op);           // "Velocidad", "Aceleracion"...
const char* uiNombreParametro(Parametro p);          // "Velocidad", "Kp"...

#endif // UI_H
