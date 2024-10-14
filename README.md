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

**4.** El programa le mostrará si la cadena de entrada es aceptada o rechazada por el autómata de pila y el número de transiciones realizadas. Si se tiene el modo traza activado, se mostrará la traza en cada transición.

**5.** Para limpiar los archivos generados por el programa, ejecute el siguiente comando:
```bash
make clean
```

## Modo traza
Para activar el modo traza, descomente la siguiente línea en el archivo *main.cpp* y compile el programa nuevamente:
```cpp
pda.EnableTrace();
```
## Descripción
En esta práctica se ha implementado un programa en C++ que implementa un autómata de pila (PDA) por vaciado. El programa recibe como entrada un archivo que contiene la definición del autómata de pila y le solicita al usuario que introduzca cadenas de entrada para el autómata de pila. El programa mostrará si la cadena de entrada es aceptada o rechazada por el autómata de pila y el número de transiciones realizadas. Si se tiene el modo traza activado, se mostrará la traza en cada transición.

El autómata de pila es una 7-tupla (Q, Σ, Γ, δ, q0, Z0, F) donde:
* Q: Conjunto finito de estados.
* Σ: Alfabeto de entrada.
* Γ: Alfabeto de la pila.
* δ: Función de transición.
* q0: Estado inicial.
* Z0: Símbolo inicial de la pila.
* F: Conjunto de estados finales (en este caso, como es por vaciado, no se utiliza).

El autómata de pila se representa mediante una clase **PDA** que contiene los siguientes métodos:
```cpp
// Constructor de la clase.
PDA::PDA(...);
// Método que verifica si una cadena de entrada es aceptada por el autómata de pila.
PDA::Accepts(std::string input);
// Método que activa el modo traza.
PDA::EnableTrace();
// Método que devuelve el número de transiciones realizadas.
PDA::TransitionCounter();
```

Se han implementado otras clases auxiliares para representar los elementos del autómata de pila:
* **PDAStack:** Clase que representa la pila del autómata de pila.
* **State:** Clase que representa un estado del autómata de pila.
* **Symbol:** Clase que representa un símbolo del autómata de pila.
* **TransitionSet:** Clase que representa un conjunto de transiciones de un estado del autómata de pila.
* Y otros tipos para representar simplificar el resultado de la función de transición.

Para la entrada del autómata de pila, se ha implementado una clase **PDAInput** que lee un archivo que contiene la definición del autómata de pila y devuelve un objeto de la clase **PDA**.
