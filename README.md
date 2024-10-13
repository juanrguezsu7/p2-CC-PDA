# Práctica 2 Complejidad Computacional: Implementación del Autómata de Pila (PDA)
## Autor
* Nombre: Juan Rodríguez Suárez
* Correo: [alu0101477596@ull.edu.es](alu0101477596@ull.edu.es)
## Requerimientos
* **g++:** Para compilar código C++17.
* **make:** Para ejecutar el archivo *Makefile*.
## Ejecución
**1.** Para compilar el programa, ejecute el siguiente comando:
```bash
make
```
**2.** Para ejecutar el programa, ejecute el siguiente comando:
```bash
./main <PDAFileName>
```
* Donde *\<PDAFileName\>* es el nombre del archivo que contiene la definición del autómata de pila.

**3.** El programa le pedirá que introduzca cadenas de entrada para el autómata de pila hasta que introduzca una cadena vacía (presionar *Enter* sin escribir nada).

**4.** El programa le mostrará si la cadena de entrada es aceptada o rechazada por el autómata de pila.

**5.** Para limpiar los archivos generados por el programa, ejecute el siguiente comando:
```bash
make clean
```
## Descripción
En esta práctica se ha implementado un programa en C++ que calcula la potencia de un número entero no negativo usando funciones primitivas recursivas. Para ello, se han implementado las siguientes funciones primitivas recursivas:
* **Cero:** Función que devuelve 0.
* **Sucesor:** Función que devuelve el sucesor de un número.
* **Proyección:** Función que devuelve uno de los argumentos que recibe.
* **Suma:** Función que devuelve la suma de dos números.
* **Producto:** Función que devuelve el producto de dos números.
* **Potencia:** Función que devuelve la potencia de un número.

Y operadores primitivos:
* **Composición:** Operador que permite componer funciones primitivas recursivas.
* **Combinación:** Operador que permite combinar el resultado de funciones primitivas recursivas.