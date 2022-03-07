/*
 * https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244
 * TDS (Total Dissolved Solids) indica cuántos miligramos de sólidos solubles se disuelven en un litro de agua. 
 * En general, cuanto mayor sea el valor de TDS, más sólidos solubles se disuelven en el agua y menos limpia es el agua. 
 * Por lo tanto, el El valor TDS se puede utilizar como un punto de referencia para reflejar la limpieza del agua.
 *
 * https://hydro-gardens.com/ec-to-tds-conversion/   ppm500= EC*500
 * **********
 * Adaptado para ESP32 (CAD DE 12 Bits) por Raúl Miranda-Tello 20220221
 * **********
*/

//Variables del sensor TDS Meter
#define sensortds_pin 12
#define muestra 20      // numero de muestras
int tdsVal, tds_PPM, n=4, fTP=20; //ejemplo de temperatura a 20 Grados
float tdsVoltaje;

// Variables para promedio y odenar muestras
float avgVal, temp;
int buf[muestra];

void setup() 
{
// Comunicación serial en 115200 bits por segundo:
Serial.begin(115200);

//Configuración del pin analógico como entrada
  pinMode (sensortds_pin, INPUT);

//Espera (Opcional)
  delay (250);
}

// bucle infinito para mostrar el voltaje en la entrada GPIO
void loop() 
{
// captura entrada análoga en el GPIO seleccionado:

/* // Envía valor PPM {ppm500 = CE x 500} de acuerdo con:
//https://hydro-gardens.com/ec-to-tds-conversion/      
tdsVal = analogRead(sensortds_pin);     //prueba para un solo valor
// Convierte la entrada análoga, la cual va de 0 - 4096 to a un voltaje (0 - 5V):
tdsVoltaje = tdsVal * (5.0 / 4096.0);

Serial.print("  ppm500:  ");     //EC "conductividad eléctrica" ​​
Serial.println(tdsVoltaje*500);
  */
  //**********************
  for(int i=0;i<muestra;i++)       //bucle de datos para promedio
  { 
    buf[i]=analogRead(sensortds_pin);
    delay(100);
  }
  for(int i=0;i<(muestra-1);i++)        //ordenar en forma ascendente los datos
  {
    for(int j=i+1;j<muestra;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
avgVal = 0;                               // Inicializar buffer
for(int i=n;i<(muestra-n);i++)  //Suma de muestras centrales, se deacartan 2 inferiores y 2 supeiores
avgVal = avgVal+buf[i];         
  
// Convierte la entrada análoga, la cual va de 0 - 4096 para un voltaje (0 - 5V):
tdsVoltaje=(avgVal /(muestra-(2*n))) * (5.0/4096); //convierte a milivolt la CAD de 12 bits ESP32

// Envìa por puerto serie valores:
Serial.print("   EC:  ");
Serial.println(tdsVoltaje);
float coeficiente=1.0+0.02*(fTP-25.0);    //formula de compensación por temperatura: fResultadoFinal(25^C) = fResultadoFinal(current)/(1.0+0.02*(fTP-25.0));
float ajusteVoltaje=tdsVoltaje/coeficiente;  //temperature compensation
tds_PPM=(133.42*ajusteVoltaje*ajusteVoltaje*ajusteVoltaje - 255.86*ajusteVoltaje*ajusteVoltaje + 857.39*ajusteVoltaje)*0.5; //convertir voltage a un valor tds
Serial.print("   PPM:  ");
Serial.println(tds_PPM);
//******************************
delay(500);    //espera para enviar siguiente dato
}
