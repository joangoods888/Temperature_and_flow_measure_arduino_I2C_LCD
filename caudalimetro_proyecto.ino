volatile int NumPulsos1; //variable para la cantidad de pulsos recibidos
int PinSensor1 = 3;    //Sensor conectado en el pin 3
float factor_conversion1=7.5; //para convertir de frecuencia a caudal

//---Función que se ejecuta en interrupción---------------
void ContarPulsos1 ()
{ 
  NumPulsos1++;  //incrementamos la variable de pulsos
} 

//---Función para obtener frecuencia de los pulsos--------
int ObtenerFrecuencia1() 
{
  int frecuencia1;
  NumPulsos1 = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Desabilitamos las interrupciones
  frecuencia1=NumPulsos1; //Hz(pulsos por segundo)
  return frecuencia1;
}

volatile int NumPulsos2; //variable para la cantidad de pulsos recibidos
int PinSensor2 = 4;    //Sensor conectado en el pin 4
float factor_conversion2=7.5; //para convertir de frecuencia a caudal

//---Función que se ejecuta en interrupción---------------
void ContarPulsos2 ()
{ 
  NumPulsos2++;  //incrementamos la variable de pulsos
} 

//---Función para obtener frecuencia de los pulsos--------
int ObtenerFrecuencia2() 
{
  int frecuencia2;
  NumPulsos2 = 0;   //Ponemos a 0 el número de pulsos
  interrupts();    //Habilitamos las interrupciones
  delay(1000);   //muestra de 1 segundo
  noInterrupts(); //Desabilitamos las interrupciones
  frecuencia2=NumPulsos2; //Hz(pulsos por segundo)
  return frecuencia2;
}


#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);


OneWire ourWire(2);   //Se establece el pin 2  como bus OneWire

DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

DeviceAddress address1 = {0x28, 0xEF, 0x5F, 0xFA, 0x5, 0x0, 0x0, 0xB6};//dirección del sensor 1
DeviceAddress address2 = {0x28, 0xC6, 0x6, 0xFB, 0x5, 0x0, 0x0, 0x7F};//dirección del sensor 2
DeviceAddress address3 = {0x28, 0xE8, 0x27, 0xFB, 0x5, 0x0, 0x0, 0xEF};//dirección del sensor 3
DeviceAddress address4 = {0x28, 0x38, 0x47, 0xFB, 0x5, 0x0, 0x0, 0x3A};//dirección del sensor 3

void setup()
{ 
  //Serial.begin(9600); 
  pinMode(PinSensor1, INPUT); 
  attachInterrupt(0,ContarPulsos1,RISING); //(Interrupcion 0(Pin2),funcion,Flanco de subida)
  pinMode(PinSensor2, INPUT); 
  attachInterrupt(0,ContarPulsos2,RISING); //(Interrupcion 0(Pin2),funcion,Flanco de subida)
    //Serial.begin(9600);
  delay(1000);
  sensors.begin();   //Se inicia el sensor
  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();

} 

void loop ()    
{
  float frecuencia1=ObtenerFrecuencia1(); //obtenemos la Frecuencia de los pulsos en Hz
  float caudal_L_m1=frecuencia1/factor_conversion1; //calculamos el caudal en L/m
  float caudal_L_h1=caudal_L_m1*60; //calculamos el caudal en L/h

   float frecuencia2=ObtenerFrecuencia2(); //obtenemos la Frecuencia de los pulsos en Hz
  float caudal_L_m2=frecuencia2/factor_conversion2; //calculamos el caudal en L/m
  float caudal_L_h2=caudal_L_m2*60; //calculamos el caudal en L/h

  //-----Enviamos por el puerto serie---------------
 /* Serial.print ("FrecuenciaPulsos: "); 
  Serial.print (frecuencia1,0); 
  Serial.print ("Hz\tCaudal: "); 
  Serial.print (caudal_L_m1,3); 
  Serial.print (" L/m\t"); 
   Serial.print (caudal_L_h1,3); 
  Serial.println ("L/h");  */

  sensors.requestTemperatures();   //envía el comando para obtener las temperaturas
  float temp1 = sensors.getTempC(address1); //Se obtiene la temperatura en °C del sensor 1
  float temp2 = sensors.getTempC(address2); //Se obtiene la temperatura en °C del sensor 2
  float temp3 = sensors.getTempC(address3); //Se obtiene la temperatura en °C del sensor 3
  float temp4 = sensors.getTempC(address4); //Se obtiene la temperatura en °C del sensor 4




  lcd.setCursor(0, 0);
  lcd.print("T1:");
  lcd.print(temp1, 1);
  lcd.print("   ");

  lcd.setCursor(11, 0);
  lcd.print("T2:");
  lcd.print(temp2, 1);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("T3:");
  lcd.print(temp3, 1);
  lcd.print("   ");

  lcd.setCursor(11, 1);
  lcd.print("T4:");
  lcd.print(temp4, 1);
  lcd.print("   ");

  lcd.setCursor(0, 2);
  lcd.print("Q1:");
  lcd.print (caudal_L_m1,1); 
  lcd.print("   ");

  lcd.setCursor(11, 2);
  lcd.print("Q2:");
  lcd.print (caudal_L_m2,1);
  lcd.print("   ");
  lcd.setCursor(0, 3);
  lcd.print("Q:(L/m) *****  T:(C)");
  

}

//En nues
