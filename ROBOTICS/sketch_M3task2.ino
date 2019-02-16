#include <Servo.h>

//define inputs
#define GRIP 8
#define PAN 9
#define TILT 10
#define PRESSURE 11
#define LEDS 12

Servo servoGrip, servoPan, servoTilt;

void setup()
{
  pinMode(LEDS, OUTPUT);
  pinMode(PRESSURE, INPUT);
  pinMode(GRIP, OUTPUT);
  pinMode(PAN, OUTPUT);
  pinMode(TILT, OUTPUT);
  servoGrip.attach(GRIP);
  servoPan.attach(PAN);
  servoTilt.attach(TILT);
}

void loop()
{
  int pos;
  servoPan.write(90);
  servoTilt.write(70);
  servoGrip.write(180);
  delay(500);
  for (pos = 180; digitalRead(PRESSURE)==LOW; pos -= 1) { // goes from 180 degrees to 0 degrees
    servoGrip.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  digitalWrite(LEDS, HIGH);
}
