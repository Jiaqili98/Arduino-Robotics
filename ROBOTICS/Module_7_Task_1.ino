int left_speed = 120;
int right_speed = 120;
int pushButton = 12;
int rBumper = 11;
int lBumper = 10;
int rWheel = 6; //power
int rDir = 7; //direction
int lWheel = 5; //power
int lDir = 4; //direction
volatile int LCounter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  WaitButton();
  pinMode(lBumper, INPUT);
  pinMode(rBumper, INPUT);
  pinMode(rDir, OUTPUT);
  pinMode(lDir, OUTPUT);
  interrupts();
  attachInterrupt(0, leftCounter, CHANGE);
}

void loop()
{
  Forward();
  ReactBumpers();
}

void ReactBumpers()
{
  //give time for other bumper to hit
  if (!digitalRead(rBumper) || !digitalRead(lBumper))
  {
    delay(200);
    //both bumpers hit
    if (!digitalRead(rBumper) && !digitalRead(lBumper))
    {
      Backward();
      TurnAround();
    }
    //right bumper hit
    else if (!digitalRead(rBumper) && digitalRead(lBumper))
    {
      Backward();
      TurnLeft();
    }
    //left bumper hit
    else if (digitalRead(rBumper) && !digitalRead(lBumper))
    {
      Backward();
      TurnRight();
    }
  }
}

void TurnLeft()
{
  digitalWrite(rDir, HIGH);
  digitalWrite(lDir, LOW);
  LCounter = 0;
  analogWrite(rWheel, right_speed);
  analogWrite(lWheel, left_speed);
  while (LCounter <= 12)
  {
    Serial.println(LCounter);
  }
  analogWrite(rWheel, 0);
  analogWrite(lWheel, 0);
}

void TurnRight()
{
  digitalWrite(rDir, LOW);
  digitalWrite(lDir, HIGH);
  LCounter = 0;
  analogWrite(rWheel, right_speed);
  analogWrite(lWheel, left_speed);
  while (LCounter <= 12)
  {
    Serial.println(LCounter);
  }
  analogWrite(rWheel, 0);
  analogWrite(lWheel, 0);
}

void TurnAround()
{
  digitalWrite(rDir, LOW);
  digitalWrite(lDir, HIGH);
  LCounter = 0;
  analogWrite(rWheel, right_speed);
  analogWrite(lWheel, left_speed);
  while (LCounter <= 32)
  {
    Serial.println(LCounter);
  }
  analogWrite(rWheel, 0);
  analogWrite(lWheel, 0);
}

void Forward()
{
  digitalWrite(rDir, HIGH);
  digitalWrite(lDir, HIGH);
  analogWrite(rWheel, right_speed);
  analogWrite(lWheel, left_speed);
}

void Backward()
{
  digitalWrite(rDir, LOW);
  digitalWrite(lDir, LOW);
  LCounter = 0;
  analogWrite(rWheel, right_speed);
  analogWrite(lWheel, left_speed);
  while (LCounter <= 16)
  {
    Serial.println(LCounter);
  }
  analogWrite(rWheel, 0);
  analogWrite(lWheel, 0);
}

void WaitButton()
{
  while (digitalRead(pushButton) == HIGH) {}
  while (digitalRead(pushButton) == LOW) {}
}

void leftCounter()
{
  LCounter++;
}
