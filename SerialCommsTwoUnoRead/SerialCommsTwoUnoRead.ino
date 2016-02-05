
const int ledPin =  13;  

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(ledPin, LOW);
}

void loop()
{
  if(Serial.read() == '#'
  {  
    if(Serial.read() == 'H' 
    {
      digitalWrite(ledPin, HIGH); 
    }
    else
    {
      digitalWrite(ledPin, LOW);
    }  
  } 
}
