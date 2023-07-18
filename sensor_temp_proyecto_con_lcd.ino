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
void setup() {
  //Serial.begin(9600);
  delay(1000);
  sensors.begin();   //Se inicia el sensor
  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();
}

void loop() {

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

  lcd.setCursor(0, 3);
  lcd.print("Q1:");

  lcd.print("   ");

  lcd.setCursor(11, 3);
  lcd.print("Q2:");

  lcd.print("   ");


}
