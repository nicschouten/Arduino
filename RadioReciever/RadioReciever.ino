#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RH_ASK.h>
#include <SPI.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

RH_ASK driver;

int data;

void setup()
{
  lcd.begin(20,2);
  lcd.setCursor(0,0);
  lcd.print("begin");
  
  driver.init();
}

void loop()
{
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) // Non-blocking
  {
    lcd.setCursor(0,0); 
    lcd.print(buf[0]);
    lcd.print("   ");
  }
}
