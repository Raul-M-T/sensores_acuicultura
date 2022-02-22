/*
 * 
 * 
 * **********
 * Adaptado por Raúl Miranda-Tello 20220222
 * **********
*/


//Variables del sensor PH-4502C
int sensorph_pin = 15;
int ph_valor;
float ph_voltaje;

void setup() 
{
// Comunicación serial en 115200 bits por segundo:
Serial.begin(115200);

//Configuración del pin analógico como entrada
  pinMode (sensorph_pin, INPUT);

//Espera (Opcional)
  delay (1000);
}


// bucle infinito para mostrar el voltaje en la entrada 15:
void loop() 
{
// captura entrda análoga en el GPIO 15:
  ph_valor = analogRead(sensorph_pin);

// Convierte la entrada análoga, la cual va de 0 - 1023 to a un voltaje (0 - 5V):
  ph_voltaje = ph_valor * (5.0 / 1023.0);

// Envìa por puerto serie el valor de voltaje leido:
Serial.println(ph_voltaje);

delay(5000);  //espera de 5 segundos para enviar siguiente dato
}
