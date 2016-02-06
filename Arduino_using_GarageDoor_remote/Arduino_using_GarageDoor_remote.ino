#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const int VT = 2;    
const int D0 = 6;  
const int D1 = 5;  
const int D2 = 4;  
const int D3 = 3;  

int transmitState = 0;
int button0State = 0;
int button1State = 0;
int button2State = 0;
int button3State = 0;

void setup()
{
  // Setup size of LCD 20 characters and 2 lines
  lcd.begin(20,2); 
  // Back light on
  lcd.backlight();

  pinMode(VT, INPUT);
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);

  lcd.setCursor(0,0);
  lcd.clear();
}  
  
void loop() 
{
  transmitState = digitalRead(VT);
  
  if (transmitState == HIGH)
  {
    button0State = digitalRead(D0);
    button1State = digitalRead(D1);
    button2State = digitalRead(D2);
    button3State = digitalRead(D3);
  }
  else
  {
    button0State = LOW;
    button1State = LOW;
    button2State = LOW;
    button3State = LOW;
  }
  
  lcd.setCursor(0,0);
  if (button0State == HIGH)
  {
    lcd.print("B0=On ");
  }
  else
  {
    lcd.print("B0=Off");
  }
  
  lcd.setCursor(7,0);
  if (button1State == HIGH)
  {
    lcd.print("B1=On ");
  }
  else
  {
    lcd.print("B1=Off");
  }
  
  lcd.setCursor(0,1);
  if (button2State == HIGH)
  {
    lcd.print("B2=On ");
  }
  else
  {
    lcd.print("B2=Off");
  }
  
  lcd.setCursor(7,1);
  if (button3State == HIGH)
  {
    lcd.print("B3=On ");
  }
  else
  {
    lcd.print("B3=Off");
  }
  
  delay(10);
}


