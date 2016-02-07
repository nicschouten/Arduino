#include <VirtualWire.h>

const int BitPerSec = 2000;
const int DataPin   = 2;
const int InputPin  = A0;

uint8_t* Data;
int InputValue;

void setup()
{
  vw_set_ptt_inverted(true);
  vw_setup(BitPerSec); 
  vw_set_tx_pin(DataPin);
}

void loop()
{
  InputValue = analogRead(InputPin);
    
  Data[0] = 25;
  
  vw_send(Data, 1);
  vw_wait_tx();

  delay(10);
}

