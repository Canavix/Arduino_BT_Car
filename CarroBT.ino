/*
Control para Carro Bluetooth con Arduino y Driver L298.

Desarrollado por: Cristian Camilo Cañaveral Avilés
Fecha de creación: 1 de agosto de 2025
Contacto: camilo.canaveral@itspereira.edu.co
*/

// ****************************************** Variables *********************************************************************************

// Esta variable le permite controlar la velocidad de los motores
// Con un 0, los motores estarían apagados
// Con un 255, irían a la máxima velocidad
// Valores intermedios, escalarán la velocidad
int velocidad = 255;

// ****************************************** Void Setup *********************************************************************************

void setup() {

  // Aqui estan definidos los pines de los motores
  pinMode(2, OUTPUT); // In1 --> Motor Izquierda (Define el pin 2 como salida para el motor izquierdo)
  pinMode(3, OUTPUT); // In2 --> Motor Izquierda (Define el pin 3 como salida para el motor izquierdo)
  pinMode(4, OUTPUT); // In3 --> Motor Derecha (Define el pin 4 como salida para el motor derecho)
  pinMode(5, OUTPUT); // In4 --> Motor Derecha (Define el pin 5 como salida para el motor derecho)

  // con los pines 10 y 11, podemos variar la velocidad de los motores
  pinMode(10, OUTPUT); // EnA (Define el pin 10 como salida para el control de velocidad del motor izquierdo)
  pinMode(11, OUTPUT); // EnB (Define el pin 11 como salida para el control de velocidad del motor derecho)

  // Configuracion del bluetooth
  Serial.begin(9600); // 9600 es la velocidad de transimisión con el celular (Inicia la comunicación serial a 9600 baudios)
}

// ****************************************** Void Loop *********************************************************************************


void loop() {
  if(Serial.available() == true){ // Es porque el Arduino está recibiendo por el BT (Verifica si hay datos disponibles en el buffer serial)
    char datoRecibido = Serial.read(); // Lee el dato del puerto serial y lo guarda en la variable 'datoRecibido'
    if(datoRecibido == 'A'){ // Si el dato recibido es una letra A (Verifica si el dato es 'A')
      detener(); // Llama a la función para detener el robot
    }
    else if(datoRecibido == 'B'){ // Si el dato recibido es una letra B (Verifica si el dato es 'B')
      adelante(velocidad); // Llama a la función para mover el robot hacia adelante
    }
    else if(datoRecibido == 'C'){ // Si el dato recibido es una letra C (Verifica si el dato es 'C')
      atras(velocidad); // Llama a la función para mover el robot hacia atrás
    }
    else if(datoRecibido == 'D'){ // Si el dato recibido es una letra D (Verifica si el dato es 'D')
      derecha(velocidad); // Llama a la función para girar el robot a la derecha
    }
    else if(datoRecibido == 'E'){ // Si el dato recibido es una letra E (Verifica si el dato es 'E')
      izquierda(velocidad); // Llama a la función para girar el robot a la izquierda
    }
  }
}

// ****************************************** Funciones de movimiento *********************************************************************************


void adelante(int velocidad) {
  // Adelante (Función para mover el robot hacia adelante)
  analogWrite(10, velocidad); // Variar velocidad (Controla la velocidad del motor izquierdo)
  analogWrite(11, velocidad); // Variar velocidad (Controla la velocidad del motor derecho)
  digitalWrite(2, HIGH); // Activa el motor izquierdo en una dirección
  digitalWrite(3, LOW); // Desactiva la otra dirección del motor izquierdo
  digitalWrite(4, HIGH); // Activa el motor derecho en una dirección
  digitalWrite(5, LOW); // Desactiva la otra dirección del motor derecho
}

void atras(int velocidad) {
  // Atras (Función para mover el robot hacia atrás)
  analogWrite(10, velocidad); // Variar velocidad (Controla la velocidad del motor izquierdo)
  analogWrite(11, velocidad); // Variar velocidad (Controla la velocidad del motor derecho)
  digitalWrite(2, LOW); // Activa el motor izquierdo en una dirección
  digitalWrite(3, HIGH); // Desactiva la otra dirección del motor izquierdo
  digitalWrite(4, LOW); // Activa el motor derecho en una dirección
  digitalWrite(5, HIGH); // Desactiva la otra dirección del motor derecho
}

void derecha(int velocidad) {
  // Derecha (Función para girar el robot a la derecha)
  analogWrite(10, velocidad); // Variar velocidad (Controla la velocidad del motor izquierdo)
  analogWrite(11, velocidad); // Variar velocidad (Controla la velocidad del motor derecho)
  digitalWrite(2, HIGH); // Mueve el motor izquierdo hacia adelante
  digitalWrite(3, LOW); // Desactiva la otra dirección
  digitalWrite(4, LOW); // Mueve el motor derecho hacia atrás
  digitalWrite(5, HIGH); // Desactiva la otra dirección
}

void izquierda(int velocidad) {
  // Izquierda (Función para girar el robot a la izquierda)
  analogWrite(10, velocidad); // Variar velocidad (Controla la velocidad del motor izquierdo)
  analogWrite(11, velocidad); // Variar velocidad (Controla la velocidad del motor derecho)
  digitalWrite(2, LOW); // Mueve el motor izquierdo hacia atrás
  digitalWrite(3, HIGH); // Desactiva la otra dirección
  digitalWrite(4, HIGH); // Mueve el motor derecho hacia adelante
  digitalWrite(5, LOW); // Desactiva la otra dirección
}

void detener() {
  // Detener (Función para detener el robot)
  analogWrite(10, 0); // Variar velocidad (Establece la velocidad del motor izquierdo a cero)
  analogWrite(11, 0); // Variar velocidad (Establece la velocidad del motor derecho a cero)
  digitalWrite(2, LOW); // Detiene el motor izquierdo
  digitalWrite(3, LOW); // Detiene el motor izquierdo
  digitalWrite(4, LOW); // Detiene el motor derecho
  digitalWrite(5, LOW); // Detiene el motor derecho
}