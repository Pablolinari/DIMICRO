- activar pullup en las entradas del motor, para no tener que poner las 
resistencias nosotros 

- los dos pines al lado del condensador son la fuente de alimentacion 
no invertir la polaridad que se lia 

-la tira de la izq controla la de abajo y la de  la derecha la de arriba 

- pwm senial cuadrada , el ancho del pulso determina la cantidad de corriente que se da al motor, 

usar para generar la frecuencia la funcion analogWrite , tiene un parametro de 0 a 511 , 

- estos motores usan frecuencias del orden de 20000 hercios 

para ver que funciona el encoder , meterse en un bucle y en el momento de que una senial cambia incremento el contador , al cabo de un segundo pinto el valor de los dos contadores , 

se puede incluir medida de velocidad , primero se toma el tiempo , nos metemos en un bucle y mientras milis - antes < 1 segundo entonces monitorizar las dos seniales incrementando los contadores , en funcion de las caracteristicas del motor vemos cuantos pulsos hay por vuelta y dividimos entre el tiempo que ha pasado , asi calculamos la veloidadd 




