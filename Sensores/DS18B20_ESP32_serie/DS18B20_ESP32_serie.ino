
/*OneWire DS18S20, DS18B20, DS1822 Temperatur Ejemplo
//información en:
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// DallasTemperature library
// https://github.com/milesburton/Arduino-Temperature-Control-Libra
*********** 
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
*********
*Adaptado por Raúl Miranda-Tello 20220220
*
*DS_18B20         ESP32CAM
*   G              GND
*   R              5 V
*   Y              GPIO NN (entrada digital D2)
*/


//Bibliotecas
#include <OneWire.h>
#include <DallasTemperature.h>

//variables
#define ONE_WIRE_BUS 2  //El cable de datos está conectado al pin digital 2

//Objetos
OneWire oneWire(ONE_WIRE_BUS);  //Configura una instancia de oneWire para comunicarse con cualquier dispositivo OneWire
//OneWire  ds(10);  // otra forma de definir en pin 10 ( 4.7K pull up)

DallasTemperature sensors(&oneWire); //Pasar nuestra referencia de oneWire al sensor de temperatura de Dallas
void setup(void) {
  Serial.begin(115200);  //Inicia comunicación serial
  sensors.begin();        // Pone en marcha la biblioteca
}

void loop(void) {

  // Llama a sensores.requestTemperatures() para emitir una temperatura global y solicitudes a todos los dispositivos en el bus
  sensors.requestTemperatures(); 
  Serial.print("Celsius temperature: ");
 // ¿Por qué "byIndex"?Puede tener más de un IC en el mismo bus. 0 se refiere al primer IC en el cable
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  delay(5000);
  
}
