
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print('#');
  Serial.print('H');
  delay(1000);
  Serial.print('#');
  Serial.print('L');
  delay(1000);
}
