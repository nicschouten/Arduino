String inputString = "";        
boolean stringComplete = false; 

byte RedClr = 255;
byte GreenClr = 0;
byte BlueClr = 0;

int RedPin   = 9;
int GreenPin = 10;
int BluePin  = 11;

void setup()
{
  Serial.begin(57600);
  
  while (!Serial) 
  {
    ; 
  }

  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  
  analogWrite(RedPin,   RedClr);
  analogWrite(GreenPin, GreenClr);
  analogWrite(BluePin,  BlueClr);

  inputString.reserve(200);
}

void loop()
{
  if (stringComplete)
  {
    if (inputString[0] == 'P')
    {
      Serial.println("D");
    }
    else if (inputString[0] == 'S')
    {
      RedClr   = (byte)inputString[1];
      GreenClr = (byte)inputString[2];
      BlueClr  = (byte)inputString[3];

      analogWrite(RedPin,   RedClr);
      analogWrite(GreenPin, GreenClr);
      analogWrite(BluePin,  BlueClr);
    }
    else
    {
      Serial.println("E");
    }

    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() 
{
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    if (inChar == '\n') 
    {
      stringComplete = true;
    }
  }
}
