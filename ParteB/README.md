# Parte B

## Diagrama de Estados

El sistema implementa una Máquina de Estados Finitos (FSM) para controlar dos semáforos utilizando LEDs. La FSM incluye los siguientes estados:

1. **A_VERDE:** El semáforo A enciende su LED verde. El semáforo B permanece en rojo.
2. **A_AMARILLO:** El semáforo A cambia a LED amarillo. El semáforo B sigue en rojo.
3. **B_VERDE:** El semáforo B enciende su LED verde. El semáforo A cambia a rojo.
4. **B_AMARILLO:** El semáforo B cambia a LED amarillo. El semáforo A permanece en rojo.

### Transiciones

El sistema inicia en el estado `A_VERDE` y cambia de estado de acuerdo al siguiente ciclo:


Los tiempos de duración por estado son:

- **Verde:** 5000 ms (5 segundos)
- **Amarillo:** 2000 ms (2 segundos)

Se utiliza la función `millis()` para medir el tiempo transcurrido y evitar bloqueos con `delay()`.

## Comportamiento del Sistema

- Cada estado activa los LEDs correspondientes usando la función `digitalWrite`.
- Antes de cambiar de estado, todos los LEDs son apagados con la función `apagarSemaforo()`.
- Se emplea una estructura `Semaforo` para representar cada grupo de LEDs y una enumeración `EstadoFSM` para definir los estados posibles.
- La función `setEstado()` centraliza la lógica de transición de estados y configuración del sistema.

Este diseño garantiza un control claro, escalable y sin interferencias entre los semáforos, simulando adecuadamente un sistema vial básico.

---
 Este directorio contiene:

- `P2_RetoB.ino`: Código fuente del sistema de control por FSM para semáforos.
- `diagrama_fsm.png`: Diagrama de estados representando visualmente la FSM implementada.
- `README.md`: Documento explicativo del funcionamiento y lógica del sistema.
