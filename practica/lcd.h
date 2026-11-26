#include "config.h"

void setIO(bool salida);
void cargarDatos(byte valor);
void write(byte valor);
void printDisp(char* frase);
void comando(byte valor, int timeout);
void comando(byte valor);
void home();
void setCursor(byte columna, byte fila);
void scrollDisplayLeft();
void scrollDisplayRight();
void cursor();
void noCursor();
void blink();
void noBlink();
void display();
void noDisplay();
void autoscroll();
void noAutoscroll();
void setmode();
void reset();
void isBusy();
