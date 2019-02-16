#include <EEPROM.h>
byte left_speed = EEPROM.read(0);
byte right_speed = EEPROM.read(1);
int pushButton = 12;
int rBumper = 11;
int lBumper = 10;
int rWheel = 6;
int rDir = 7; //direction
int lWheel = 5;
int lDir = 4; //direction
volatile int LCounter = 0;
int IRSensor = A5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  WaitButton();
  pinMode(IRSensor, INPUT);
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
  if (analogRead(IRSensor) > 600)
  {
    Backward();
    TurnAround();
  }
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
  analogWrite(rWheel, right_speed);
  analogWrite(lWheel, left_speed);
  LCounter = 0;
  while (LCounter <= 32)
  {
    Serial.println(LCounter);
  }
  analogWrite(rWheel, 0);
  analogWrite(lWheel, 0);
}


void leftCounter()
{
  LCounter++;
}
void WaitButton()
{
  while (digitalRead(pushButton) == HIGH) {}
  while (digitalRead(pushButton) == LOW) {}
}
