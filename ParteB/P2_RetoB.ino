#include <Controllino.h>

// Estructura que agrupa los pines de cada color de un semáforo
struct Semaforo {
  int verde;
  int amarillo;
  int rojo;
};

// Dos semáforos independientes: semA y semB
Semaforo semA = {CONTROLLINO_D0, CONTROLLINO_D1, CONTROLLINO_D2}; // LEDs para semáforo A
Semaforo semB = {CONTROLLINO_D6, CONTROLLINO_D7, CONTROLLINO_D8}; // LEDs para semáforo B

// Definición de los estados posibles de la máquina de estados
enum EstadoFSM {
  A_VERDE,     // A en verde, B en rojo
  A_AMARILLO,  // A en amarillo, B en rojo
  B_VERDE,     // B en verde, A en rojo
  B_AMARILLO   // B en amarillo, A en rojo
};

EstadoFSM estado = A_VERDE; // Estado inicial

unsigned long t_prev = 0;     // Marca de tiempo del último cambio de estado
unsigned long duracion = 0;   // Duración del estado actual

void setup() {
  // Configurar todos los pines de los LEDs como salidas
  pinMode(semA.verde, OUTPUT);
  pinMode(semA.amarillo, OUTPUT);
  pinMode(semA.rojo, OUTPUT);

  pinMode(semB.verde, OUTPUT);
  pinMode(semB.amarillo, OUTPUT);
  pinMode(semB.rojo, OUTPUT);

  setEstado(A_VERDE); // Estado inicial: semáforo A en verde
}

void loop() {
  unsigned long t_actual = millis();

  // Si ha pasado el tiempo asignado al estado, cambiar al siguiente
  if (t_actual - t_prev >= duracion) {
    switch (estado) {
      case A_VERDE:
        setEstado(A_AMARILLO); break;
      case A_AMARILLO:
        setEstado(B_VERDE); break;
      case B_VERDE:
        setEstado(B_AMARILLO); break;
      case B_AMARILLO:
        setEstado(A_VERDE); break;
    }
  }
}

// Función que configura los LEDs para un nuevo estado
void setEstado(EstadoFSM nuevoEstado) {
  apagarSemaforo(semA);  // Apaga todos los LEDs del semáforo A
  apagarSemaforo(semB);  // Apaga todos los LEDs del semáforo B

  estado = nuevoEstado;
  t_prev = millis(); // Reinicia el temporizador del estado

  // Configura los LEDs según el nuevo estado y asigna la duración correspondiente
  switch (estado) {
    case A_VERDE:
      digitalWrite(semA.verde, HIGH);
      digitalWrite(semB.rojo, HIGH);
      duracion = 5000;
      break;
    case A_AMARILLO:
      digitalWrite(semA.amarillo, HIGH);
      digitalWrite(semB.rojo, HIGH);
      duracion = 2000;
      break;
    case B_VERDE:
      digitalWrite(semA.rojo, HIGH);
      digitalWrite(semB.verde, HIGH);
      duracion = 5000;
      break;
    case B_AMARILLO:
      digitalWrite(semA.rojo, HIGH);
      digitalWrite(semB.amarillo, HIGH);
      duracion = 2000;
      break;
  }
}

// Apaga todos los LEDs de un semáforo
void apagarSemaforo(Semaforo s) {
  digitalWrite(s.verde, LOW);
  digitalWrite(s.amarillo, LOW);
  digitalWrite(s.rojo, LOW);
}
