// Definimos los pines de los LEDs
#define ledA 13  // LED amarillo
#define ledR 12  // LED rojo
#define ledV 11  // LED verde

// Banderas para el estado de las luces
bool estadoLuzAmarilla = false;
bool estadoLuzRoja = false;
bool estadoLuzVerde = false;

void setup() {
  // Configuramos los pines de los LEDs como salidas
  pinMode(ledA, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);

  // Iniciamos la comunicación serie a 9600 baudios
  Serial.begin(9600);
  
  // Mensaje inicial para el Monitor Serial
  Serial.println("Control de luces desde el Monitor Serial:");
  Serial.println("1: Prender/Apagar todas las luces.");
  Serial.println("2: Encender/Apagar la luz verde.");
  Serial.println("3: Encender/Apagar la luz roja.");
  Serial.println("4: Encender/Apagar la luz amarilla.");
  Serial.println("5: Activar/Desactivar la intermitencia en todas las luces.");
}

void loop() {
  // Verificamos si hay datos disponibles en el Monitor Serial
  if (Serial.available() > 0) {
    // Leemos el comando ingresado como un carácter
    char comando = Serial.read();

    // Verificamos qué opción se seleccionó
    switch (comando) {
      case '1':
        // Prender/Apagar todas las luces
        if (estadoLuzAmarilla || estadoLuzRoja || estadoLuzVerde) {
          // Si alguna luz está encendida, las apagamos todas
          digitalWrite(ledA, LOW);
          digitalWrite(ledR, LOW);
          digitalWrite(ledV, LOW);
          estadoLuzAmarilla = false;
          estadoLuzRoja = false;
          estadoLuzVerde = false;
          Serial.println("Todas las luces apagadas.");
        } else {
          // Si todas las luces están apagadas, las encendemos
          digitalWrite(ledA, HIGH);
          digitalWrite(ledR, HIGH);
          digitalWrite(ledV, HIGH);
          estadoLuzAmarilla = true;
          estadoLuzRoja = true;
          estadoLuzVerde = true;
          Serial.println("Todas las luces encendidas.");
        }
        break;

      case '2':
        // Encender/Apagar la luz verde
        estadoLuzVerde = !estadoLuzVerde;  // Cambiamos el estado de la luz verde
        digitalWrite(ledV, estadoLuzVerde ? HIGH : LOW);
        Serial.println(estadoLuzVerde ? "Luz verde encendida." : "Luz verde apagada.");
        break;

      case '3':
        // Encender/Apagar la luz roja
        estadoLuzRoja = !estadoLuzRoja;  // Cambiamos el estado de la luz roja
        digitalWrite(ledR, estadoLuzRoja ? HIGH : LOW);
        Serial.println(estadoLuzRoja ? "Luz roja encendida." : "Luz roja apagada.");
        break;

      case '4':
        // Encender/Apagar la luz amarilla
        estadoLuzAmarilla = !estadoLuzAmarilla;  // Cambiamos el estado de la luz amarilla
        digitalWrite(ledA, estadoLuzAmarilla ? HIGH : LOW);
        Serial.println(estadoLuzAmarilla ? "Luz amarilla encendida." : "Luz amarilla apagada.");
        break;

      case '5':
        // Activar/Desactivar la intermitencia en todas las luces
        Serial.println("Intermitencia activada.");
        for (int i = 0; i < 10; i++) {  // Parpadeo 10 veces
          digitalWrite(ledA, HIGH);
          digitalWrite(ledR, HIGH);
          digitalWrite(ledV, HIGH);
          delay(500);
          digitalWrite(ledA, LOW);
          digitalWrite(ledR, LOW);
          digitalWrite(ledV, LOW);
          delay(500);
        }
        Serial.println("Intermitencia terminada.");
        break;

      default:
        // Comando no reconocido
        Serial.println("Comando no reconocido. Por favor, usa 1, 2, 3, 4 o 5.");
        break;
    }
  }
}



