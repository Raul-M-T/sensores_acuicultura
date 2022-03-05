/*
 * ENLACE DE PROYECTO 
 * https://www.electroniclinic.com/ph-sensor-arduino-how-do-ph-sensors-work-application-of-ph-meter-ph-sensor-calibration/
 * **********
 * Adaptado por Raúl Miranda-Tello 20220222
 *
 *    PH-4502C      ESP32                        
 *       VCC         5 V             
 *       GND         GND             
 *        P0         GPIO 15                       
 * 
 *
 *
 ********
*/


//Variables del sensor PH-4502C
#define sensorph_pin 15
int phValor;
float phVoltaje;
// Variables para promedio y odenar 10 muestras
float avgValue;
int buf[10],temp;
void setup() 
{
// Comunicación serial en 115200 bits por segundo:
Serial.begin(115200);

//Configuración del pin analógico como entrada
  pinMode (sensorph_pin, INPUT);

//Espera (Opcional)
  delay (1000);
}
//***************************************************
// bucle infinito para mostrar el voltaje en la entrada GPIO 15:
void loop() 
{
// captura entrada análoga en el GPIO 15:
for(int i=0;i<10;i++)       //10 datos para un promedio
  { 
    buf[i]=analogRead(sensorph_pin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //ordenar en forma ascendente los datos
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue = 0;                   // Inicializar buffer
  for(int i=3;i<8;i++)            //Suma de 6 muestras centrales
  avgValue = avgValue+buf[i]; 
  
  // Convierte la CAD, que va de 0 - 1024 a un voltaje (0 - 5V):
  float phVoltaje=(avgValue*5.0)/(1024*6); //convierte a milivolt la CAD
  phValor = phVoltaje-3.5;                 //convierte los milivolt en un valor pH 
 // Envìa por puerto serie los valores obtenidos:
  Serial.print("    pH:");  
  Serial.println(phValor);        
  Serial.print("   Voltaje:");
  Serial.println(phVoltaje);

delay(1000);  //espera segundos para enviar siguiente dato
}
