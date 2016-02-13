
const int EnginePin =  2;
int EngineState = LOW;

void setup() 
{
  pinMode(EnginePin, OUTPUT);      
}

void loop()
{

  if (EngineState == HIGH)
  {
    EngineState = LOW;  
  }
  else
  {
    EngineState = HIGH;
  }
  
  digitalWrite(EnginePin, EngineState);
  
  delay(500);

}

