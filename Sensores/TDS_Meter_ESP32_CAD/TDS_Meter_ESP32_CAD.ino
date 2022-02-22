/*
 * 
 * 
 * **********
 * Adaptado por Raúl Miranda-Tello 20220221
 * **********
*/


//Variables del sensor TDS Meter
int sensortds_pin = 14;
int tds_valor;
float tds_voltaje;

void setup() 
{
// Comunicación serial en 115200 bits por segundo:
Serial.begin(115200);

//Configuración del pin analógico como entrada
  pinMode (sensortds_pin, INPUT);

//Espera (Opcional)
  delay (1000);
}


// bucle infinito para mostrar el voltaje en la entrada 14
void loop() 
{
// captura entrda análoga en el GPIO 14:
  tds_valor = analogRead(sensortds_pin);

// Convierte la entrada análoga, la cual va de 0 - 1023 to a un voltaje (0 - 5V):
  tds_voltaje = tds_valor * (5.0 / 1023.0);

// Envìa por puerto serie el valor de voltaje leido:
Serial.println(tds_voltaje);

delay(5000);    //espera de 5 segundos para enviar siguiente dato
}
