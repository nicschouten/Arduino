const int coil01 = 2;
const int coil02 = 3;
const int coil03 = 4;
const int coil04 = 5;

//----------------------------------------------------------------------------
void setup()
{
  pinMode(coil01, OUTPUT);
  pinMode(coil02, OUTPUT);
  pinMode(coil03, OUTPUT);
  pinMode(coil04, OUTPUT);
}

//----------------------------------------------------------------------------
void loop()
{
  Step_ClockWise(4200, 1, true);
  void Coiloff();
  delay(1000);
  
  Step_CounterClockWise(4200, 1, true);
  void Coiloff();
  delay(1000);
  
  Step_ClockWise(2100, 2, false);
  void Coiloff();
  delay(1000);
  
  Step_CounterClockWise(2100, 2, false);
  void Coiloff();
  delay(1000);
  
}

//----------------------------------------------------------------------------
void Step_ClockWise(int steps, int off_time, boolean dohalfsteps)
{
  int StepIndex;
  int StepInc;
  int StepPos;
  
  if (dohalfsteps == true)
  {
    StepInc = 1;
  }
  else
  {
    StepInc = 2;
  }
  
  StepPos = 1;
 
  for(StepIndex = 0; StepIndex < steps; StepIndex++)
  {
    Step_Coil(StepPos);
    
    StepPos = StepPos + StepInc;
    if (StepPos > 8)
    {
      StepPos = 1;  
    }
    
    delay(off_time);
  }
}

//----------------------------------------------------------------------------
void Step_CounterClockWise(int steps, int off_time, boolean dohalfsteps)
{
  int StepIndex;
  int StepInc;
  int StepPos;
  
  if (dohalfsteps == true)
  {
    StepInc = 1;
  }
  else
  {
    StepInc = 2;
  }
  
  StepPos = 1;
 
  for(StepIndex = 0; StepIndex < steps; StepIndex++)
  {
    Step_Coil(StepPos);
    
    StepPos = StepPos - StepInc;
    if (StepPos < 1)
    {
      if (StepInc == 2)
      {
        StepPos = 7;
      }
      else
      {
        StepPos = 8;
      }
    }
    
    delay(off_time);
  }
}

//----------------------------------------------------------------------------
void Step_Coil(int coilsteppos)
{
  if (coilsteppos == 1)
  {
     CoilPos(coil02, coil03, coil04, coil01, false); 
  }
  
  if (coilsteppos == 2)
  {
     CoilPos(coil03, coil04, coil01, coil02, true); 
  }
  
  if (coilsteppos == 3)
  {
     CoilPos(coil03, coil04, coil01, coil02, false); 
  }
  
  if (coilsteppos == 4)
  {
     CoilPos(coil04, coil01, coil02, coil03, true); 
  }

  if (coilsteppos == 5)
  {
     CoilPos(coil04, coil01, coil02, coil03, false); 
  }
  
  if (coilsteppos == 6)
  {
     CoilPos(coil01, coil02, coil03, coil04, true); 
  }
  
  if (coilsteppos == 7)
  {
     CoilPos(coil01, coil02, coil03, coil04, false); 
  }
  
  if (coilsteppos == 8)
  {
     CoilPos(coil02, coil03, coil04, coil01, true); 
  }
}

//----------------------------------------------------------------------------
void CoilPos(int c1, int c2,int c3,int c4, boolean twocoils)
{
  digitalWrite(c1, LOW);
  digitalWrite(c2, LOW);
  
  if (twocoils == true)
  {
    digitalWrite(c3, HIGH);
  }
  else
  {
    digitalWrite(c3, LOW);
  }
  
  digitalWrite(c4, HIGH);
}

//----------------------------------------------------------------------------
void Coiloff()
{
  digitalWrite(coil01, LOW);
  digitalWrite(coil02, LOW);
  digitalWrite(coil03, LOW);
  digitalWrite(coil04, LOW);
}
