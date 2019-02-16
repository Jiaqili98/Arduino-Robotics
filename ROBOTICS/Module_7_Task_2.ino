#include <EEPROM.h>
byte left_speed=EEPROM.read(0);
byte right_speed=EEPROM.read(1);
int pushButton = 12;
int rBumper = 11;
int lBumper = 10;
int rWheel = 6;
int rDir = 7; //direction
int lWheel = 5;
int lDir = 4; //direction
volatile int LCounter = 0;
int alpha = 1;

void setup() {
  // put your setup code here, to run once:
  
   EEPROM.write(0, 100);
  EEPROM.write(1, 100);
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
  //Serial.println("hello");
  Forward();
  AdjustSpeeds();
}

void AdjustSpeeds()
{
  //Serial.print(digitalRead(rBumper));
  //Serial.println(digitalRead(lBumper));
  if (!digitalRead(rBumper) || !digitalRead(lBumper))
  {
   delay(500);
  }
  //left bumper only
  if (digitalRead(rBumper) && !digitalRead(lBumper))
  {
    Serial.println("--------------------");
    Serial.println("left");
    Serial.print("Left Speed: ");
    Serial.println(left_speed);
    Serial.print("Right Speed: ");
    Serial.println(right_speed);
    if(left_speed != 0)
    {
    left_speed = left_speed - alpha;
    }
    if(right_speed != 255)
    {
    right_speed = right_speed + alpha;
    }
  }
  //right bumper only
  else if (!digitalRead(rBumper) && digitalRead(lBumper))
  {
    Serial.println("--------------------");
    Serial.println("right");
    Serial.print("Left Speed: ");
    Serial.println(left_speed);
    Serial.print("Right Speed: ");
    Serial.println(right_speed);
    if(left_speed != 255)
    {
    left_speed = left_speed + alpha;
    }
    if(right_speed != 0)
    {
    right_speed = right_speed - alpha;
    }
  }
  else if (!digitalRead(rBumper) && !digitalRead(lBumper))
  {
    Serial.println("--------------------");
    Serial.println("both");
    Serial.print("Left Speed: ");
    Serial.println(left_speed);
    Serial.print("Right Speed: ");
    Serial.println(right_speed);
    EEPROM.write(0, left_speed);
    EEPROM.write(1, right_speed);
    right_speed = left_speed = 0;
    delay(500);
  }
  
}

void Forward()
{
  digitalWrite(rDir, HIGH);
  digitalWrite(lDir, HIGH);
  analogWrite(rWheel, right_speed);
  analogWrite(lWheel, left_speed);
}

void WaitButton()
{
  while (digitalRead(pushButton) == HIGH) {}
  while (digitalRead(pushButton) == LOW) {}
}

void Backward()
{
  digitalWrite(rDir, LOW);
  digitalWrite(lDir, LOW);
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

void leftCounter()
{
  LCounter++;
}
