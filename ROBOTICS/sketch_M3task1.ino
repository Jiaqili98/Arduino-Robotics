#include <Servo.h>

//define inputs
#define GRIP 8
#define PAN 9
#define TILT 10

Servo servoGrip, servoPan, servoTilt;

void setup()
{
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
  servoTilt.write(160);
  for (pos = servoGrip.read(); pos <= 180; pos += 1) { // goes from current pos to 180 degrees
    // in steps of 1 degree
    servoGrip.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
  delay(500);
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servoGrip.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
}
