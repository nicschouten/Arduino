
int DATA               = 3;
int DATA_OUTPUT_ENABLE = 4;
int LATCH              = 5;
int CLOCK              = 6;
int RESET              = 7;

byte Screen[8][8] = {{0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0},
                     {0,0,0,0,0,0,0,0}};

byte HappyFace[8][8] = {{0,0,3,3,3,3,0,0},
                        {0,3,3,3,3,3,3,0},
                        {3,3,4,3,3,4,3,3},
                        {3,3,3,3,3,3,3,3},
                        {3,3,3,3,3,3,3,3},
                        {3,3,2,3,3,2,3,3},
                        {0,3,3,2,2,3,3,0},
                        {0,0,3,3,3,3,0,0}}; 

byte BlueBall[8][8] = {{0,0,0,4,4,0,0,0},
                       {0,0,4,5,5,4,0,0},
                       {0,4,5,7,7,5,4,0},
                       {4,5,7,7,7,7,5,4},
                       {4,5,7,7,7,7,5,4},
                       {0,4,5,7,7,5,4,0},
                       {0,0,4,5,5,4,0,0},
                       {0,0,0,4,4,0,0,0}};

byte Picture[8][8] = {{4,4,4,4,4,4,4,4},
                      {4,4,1,4,4,3,3,4},
                      {4,1,1,1,4,3,3,4},
                      {4,1,1,1,4,4,4,4},
                      {4,4,2,4,4,4,4,4},
                      {4,4,2,4,4,4,4,4},
                      {1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1}};

unsigned long LastStateChangeTime;
unsigned long StateWaitTime;
int State;

void sendBit(uint8_t aData)
{
  digitalWrite(DATA,  aData);  
  digitalWrite(CLOCK, HIGH);
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA,  LOW);  
}

void sendDataFromArray()
{
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    //Set Anode Line
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if (lineIndex == rowIndex)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Set Green Row
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if ((Screen[lineIndex][rowIndex] & 1) == 0)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Set Red Row
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if ((Screen[lineIndex][rowIndex] & 2) == 0)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Set Blue Row
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      if ((Screen[lineIndex][rowIndex] & 4) == 0)
      {
        sendBit(HIGH);
      }
      else
      {
        sendBit(LOW);
      }
    }

    //Send data to output
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
  }
}

void Clear()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = 0;
    }
  }
}

void ShowHappyFace()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = HappyFace[lineIndex][rowIndex];
    }
  }
}

void ShowPicture()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = Picture[lineIndex][rowIndex];
    }
  }
}

void ShowRainBow()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    Screen[lineIndex][0] = 0;
    Screen[lineIndex][1] = 1;
    Screen[lineIndex][2] = 2;
    Screen[lineIndex][3] = 3;
    Screen[lineIndex][4] = 4;
    Screen[lineIndex][5] = 5;
    Screen[lineIndex][6] = 6;
    Screen[lineIndex][7] = 7;
  }
}

void ShowFartyFace()
{  
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = HappyFace[lineIndex][rowIndex];
    }
  }
}

void ScrollUp(byte NewLine[])
{
  byte lineIndex;
  byte rowIndex;

  for(lineIndex = 0; lineIndex < 7; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {
      Screen[lineIndex][rowIndex] = Screen[lineIndex+1][rowIndex];
    }
  }

  for(rowIndex = 0; rowIndex < 8; rowIndex++)
  {
    Screen[7][rowIndex] = NewLine[rowIndex];
  }
}

void UpdateState()
{
  State++;
  if (State == 19)
  {
    State = 0;
  }

  LastStateChangeTime = millis();
  switch (State)
  {
    case 0:
      ShowRainBow();
      StateWaitTime = 2000;
      break;
    case 1:
      Clear();
      StateWaitTime = 250;
      break;
    case 2:
      ScrollUp(HappyFace[0]);
      StateWaitTime = 250;
      break;
    case 3:
      ScrollUp(HappyFace[1]);
      StateWaitTime = 250;
      break;
    case 4:
      ScrollUp(HappyFace[2]);
      StateWaitTime = 250;
      break;
    case 5:
      ScrollUp(HappyFace[3]);
      StateWaitTime = 250;
      break;   
    case 6:
      ScrollUp(HappyFace[4]);
      StateWaitTime = 250;
      break;
    case 7:
      ScrollUp(HappyFace[5]);
      StateWaitTime = 250;
      break;
    case 8:
      ScrollUp(HappyFace[6]);
      StateWaitTime = 250;
      break;
    case 9:
      ScrollUp(HappyFace[7]);
      StateWaitTime = 2000;
      break; 

    case 10:
      ScrollUp(BlueBall[7]);
      StateWaitTime = 250;
      break;
    case 11:
      ScrollUp(BlueBall[6]);
      StateWaitTime = 250;
      break;
    case 12:
      ScrollUp(BlueBall[5]);
      StateWaitTime = 250;
      break;
    case 13:
      ScrollUp(BlueBall[4]);
      StateWaitTime = 250;
      break;   
    case 14:
      ScrollUp(BlueBall[3]);
      StateWaitTime = 250;
      break;
    case 15:
      ScrollUp(BlueBall[2]);
      StateWaitTime = 250;
      break;
    case 16:
      ScrollUp(BlueBall[1]);
      StateWaitTime = 250;
      break;
    case 17:
      ScrollUp(BlueBall[0]);
      StateWaitTime = 2000;
      break; 
    
    case 18:
      ShowPicture();
      StateWaitTime = 4000;
      break; 
  }
}

void setup() 
{
  pinMode(DATA, OUTPUT);
  pinMode(DATA_OUTPUT_ENABLE, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(RESET, OUTPUT);

  digitalWrite(DATA_OUTPUT_ENABLE, LOW);
  digitalWrite(RESET, HIGH); 
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  digitalWrite(DATA, LOW);
  
  ShowRainBow();
  State = 0;
  StateWaitTime = 2000;
  LastStateChangeTime = millis();
}

void loop() 
{
  if ((StateWaitTime > 0) &&
      (LastStateChangeTime + StateWaitTime < millis()))
  {
    UpdateState();
  }  
  
  sendDataFromArray();
}
