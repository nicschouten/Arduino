#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const int analogInPin = A0; 

const int SensorValueLow = 463; 
const int SensorValueDiff = 36; // differance between high and low sensor value
const int TempValueDiff = 42; // differance between high and low Temp value
const int TempValueLow = 9;

int sensorValue = 0;
double Temp = 0;

void setup() 
{
  lcd.begin(20,2); 
  lcd.backlight();
}

void loop() 
{
  sensorValue = analogRead(analogInPin);
  Temp = sensorValue-SensorValueLow;
  Temp = Temp/SensorValueDiff;
  Temp = Temp*TempValueDiff;
  Temp = Temp+TempValueLow;

  lcd.setCursor(0,0);
  lcd.print("Value = ");
  lcd.setCursor(7,0);
  lcd.print(sensorValue);

  lcd.setCursor(0,1);
  lcd.print("Temp = ");
  lcd.setCursor(7,1);
  lcd.print(Temp);

  delay(200);
}
