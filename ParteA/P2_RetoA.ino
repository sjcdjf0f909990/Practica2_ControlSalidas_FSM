// Práctica 2: Encendido y apagado de un LED del tablero mediante dos botones
#include <Controllino.h> // Librería específica para control del hardware Controllino

unsigned long t_prev = 0; // Tiempo anterior para controlar los intervalos de actualización

// Secuencia de pines para los LEDs en sentido horario
int ledPins[] = {
  CONTROLLINO_D7, CONTROLLINO_D0, CONTROLLINO_D6, CONTROLLINO_D12, CONTROLLINO_D13,
  CONTROLLINO_D14, CONTROLLINO_D8, CONTROLLINO_D2, CONTROLLINO_D1, CONTROLLINO_D7
};

// Secuencia de pines en sentido antihorario
int ledPins2[] = {
  CONTROLLINO_D0, CONTROLLINO_D7, CONTROLLINO_D1, CONTROLLINO_D2, CONTROLLINO_D8,
  CONTROLLINO_D14, CONTROLLINO_D13, CONTROLLINO_D12, CONTROLLINO_D6, CONTROLLINO_D0
};

// Punteros para recorrer cada secuencia
int* ptr1 = ledPins;
int* ptr2 = ledPins2;

int i = 0; // Índice para avanzar en ledPins
int j = 0; // Índice para avanzar en ledPins2

// Entradas de botones físicas
const int boton_16 = CONTROLLINO_I16;   // Activa modo1 (apagado)
const int boton_17 = CONTROLLINO_I17;   // Activa modo2 (secuencia 1)
const int boton_18 = CONTROLLINO_I18;   // Activa modo3 (secuencia 2)

// Definición de modos
const int modo1 = 1;
const int modo2 = 2;
const int modo3 = 3;
int modo_n = 0; // Estado actual del sistema

void setup() {
  // Configuración de pines como salidas
  pinMode(CONTROLLINO_D0, OUTPUT);
  pinMode(CONTROLLINO_D1, OUTPUT);
  pinMode(CONTROLLINO_D2, OUTPUT);
  pinMode(CONTROLLINO_D6, OUTPUT);
  pinMode(CONTROLLINO_D7, OUTPUT);
  pinMode(CONTROLLINO_D8, OUTPUT);
  pinMode(CONTROLLINO_D12, OUTPUT);
  pinMode(CONTROLLINO_D13, OUTPUT);
  pinMode(CONTROLLINO_D14, OUTPUT);

  // Configuración de botones como entradas
  pinMode(boton_16, INPUT);
  pinMode(boton_17, INPUT);
  pinMode(boton_18, INPUT);
}

void loop() {
  unsigned long t_actual = millis(); // Tiempo actual

  switch (modo_n) {
    case modo2: // Modo secuencia 1 (ptr1)
      if (t_actual - t_prev >= 500) {
        t_prev = t_actual;
        digitalWrite(*(ptr1 + i + 1), HIGH); // Enciende el siguiente LED
        digitalWrite(*(ptr1 + i), LOW);      // Apaga el anterior
        i++;
        if (i == 9) i = 0;
      }
      if (digitalRead(boton_18) == HIGH) {
        digitalWrite(ledPins[i], LOW); // Apaga LED si se cambia de modo
      }
    break;

    case modo3: // Modo secuencia 2 (ptr2)
      if (t_actual - t_prev >= 500) {
        t_prev = t_actual;
        digitalWrite(*(ptr2 + j + 1), HIGH);
        digitalWrite(*(ptr2 + j), LOW);
        j++;
        if (j == 9) j = 0;
      }
      if (digitalRead(boton_17) == HIGH) {
        digitalWrite(ledPins2[j], LOW);
      }
    break;

    case modo1: // Apagar LEDs
      digitalWrite(ledPins[i], LOW);
      digitalWrite(ledPins2[j], LOW);
      i = 0;
      j = 0;
    break;
  }

  // Cambios de estado según combinaciones de botones
  if (digitalRead(boton_16) == HIGH && digitalRead(boton_17) == LOW && digitalRead(boton_18) == LOW) {
    modo_n = modo1;
  }
  if (digitalRead(boton_16) == LOW && digitalRead(boton_17) == HIGH && digitalRead(boton_18) == LOW) {
    modo_n = modo2;
    j = 0;
  }
  if (digitalRead(boton_16) == LOW && digitalRead(boton_17) == LOW && digitalRead(boton_18) == HIGH) {
    modo_n = modo3;
    i = 0;
  }

  delay(10); // Antirebote
}

