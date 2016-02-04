int CLOCK = 5;
int LATCH = 6;
int DATA  = 7;

void setup() 
{
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);
}

void loop() 
{
  // write a 1
  digitalWrite(DATA, HIGH);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(LATCH, LOW);
  // Latch it
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, HIGH);
  // Set all Clear
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  // write a 0
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(LATCH, LOW);
  // Latch it
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, HIGH);
  // Set all Clear
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
    // write a 0
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(LATCH, LOW);
  // Latch it
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, HIGH);
  // Set all Clear
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
    // write a 0
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(LATCH, LOW);
  // Latch it
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, HIGH);
  // Set all Clear
  digitalWrite(DATA, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(LATCH, LOW);
  delay(250);
}
