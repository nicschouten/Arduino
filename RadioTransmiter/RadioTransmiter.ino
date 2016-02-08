#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

const int PotInputPin = A0;
uint8_t *data;
uint8_t InputValue;

void setup()
{
  driver.init();
}

void loop()
{
  InputValue = analogRead(PotInputPin)/4;

  data = &InputValue;
    
  driver.send(data, sizeof(InputValue));
  driver.waitPacketSent();
  delay(200);
}
