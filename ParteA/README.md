# Parte A

## Objetivo

Implementar una lógica de control de salidas digitales utilizando una Máquina de Estados Finitos (FSM) programada en el Controllino. El sistema permite encender una secuencia de LEDs en dos direcciones diferentes, activadas mediante botones físicos. Además, un tercer botón permite detener o apagar la secuencia.

## Funcionamiento del Programa

El programa define tres modos de operación controlados por los botones conectados a las entradas I16, I17 e I18 del Controllino:

- **Modo 1 (botón I16):** Apaga todos los LEDs y reinicia los contadores de secuencia.
- **Modo 2 (botón I17):** Enciende una secuencia de LEDs hacia la derecha (sentido horario), avanzando cada 500 ms.
- **Modo 3 (botón I18):** Enciende una secuencia de LEDs hacia la izquierda (sentido antihorario), también con un retardo de 500 ms.

Cada secuencia está implementada con punteros a arreglos que definen el orden de los pines digitales usados. Se utilizan funciones de temporización con `millis()` para evitar bloqueos y permitir un control más preciso.

El código se encuentra bien comentado en el archivo `P2_RetoA.ino`, donde se explican los punteros, estados, entradas y lógica de cambio de modos.

---

Este directorio contiene:

- `P2_RetoA.ino`: Código fuente completo y comentado de la Parte A.
- `README.md`: Documento explicativo.
