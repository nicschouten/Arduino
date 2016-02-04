int Sensor_Read = 2;
int LED_Write = 13;

int SensorOutput = 0;

void setup()
{
  pinMode(Sensor_Read, INPUT);
  pinMode(LED_Write, OUTPUT);
}

void loop()
{
  SensorOutput = digitalRead(2);
  
  digitalWrite(13, SensorOutput);
}
