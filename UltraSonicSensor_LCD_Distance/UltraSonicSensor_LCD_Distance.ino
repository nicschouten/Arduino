#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

#define ultra_trig 2
#define ultra_echo 3

void setup()
{
  pinMode(ultra_trig, OUTPUT);
  pinMode(ultra_echo, INPUT);
  lcd.begin(20,4); 
}


void loop()  
{
  //lcd.backlight();
  //lcd.noBacklight(); 
  
  int duration;
  int distance;
  
  digitalWrite(ultra_trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(ultra_trig, LOW);
  duration = pulseIn(ultra_echo, HIGH);
  distance = (duration/2) / 29.1; 
  
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Distance");
  lcd.setCursor(0,1); //Start at character 0 on line 1
  lcd.print(distance);
  lcd.print(" cm ");
  delay(500);
}


