const int analogInPin = A0; 

int sensorValue = 0;
double Temp = 0;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  sensorValue = analogRead(analogInPin);
  Temp = sensorValue-486;
  Temp = Temp/49;
  Temp = Temp*60.5;
  Temp = Temp+11.5;

  Serial.print("Sensor = ");
  Serial.print(sensorValue);

  Serial.print(" ,Temp = ");
  Serial.println(Temp);

  delay(200);
}
