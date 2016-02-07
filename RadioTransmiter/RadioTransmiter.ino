#include <VirtualWire.h>

const int BitPerSec = 2000;
const int DataPin = 2;
const int led = 13;

uint8_t Send_Counter = 0;
uint8_t* Data;

void setup()
{
  pinMode(led, OUTPUT); 
  
  vw_setup(BitPerSec); 
  vw_set_tx_pin(DataPin);
}

void loop()
{
  digitalWrite(led, HIGH);
  Send_Counter ++;
  if (Send_Counter >= 65000)
  {
    Send_Counter = 0; 
  }
  
  Data[0] = Send_Counter;
  
  vw_send(Data, 1);
  vw_wait_tx();
  
  digitalWrite(led, LOW);
  delay(10);
}

