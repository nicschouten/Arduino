// SDA to A4, 
// SCL to A5 on Arduino
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup()
{
  // Setup size of LCD 20 characters and 2 lines
  lcd.begin(20,2); 
  // Back light on
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Hello world");
}  
  
void loop() 
{
}


