#include "Arduino.h"
#include "motors.h"

MotorControl::MotorControl(int fl_for, int fl_back,
                           int fr_for, int fr_back,
                           int bl_for, int bl_back,
                           int br_for, int br_back) 
{
  this->fl_for = fl_for;
  this->fl_back = fl_back;

  this->fr_for = fr_for;
  this->fr_back = fr_back;

  this->bl_for = bl_for;
  this->bl_back = bl_back;

  this->br_for = br_for;
  this->br_back = br_back;
}

void MotorControl::initMotors() {
  // Declare motor control pins to be in output
  pinMode(fl_for, OUTPUT);
  pinMode(fl_back, OUTPUT);

  pinMode(fr_for, OUTPUT);
  pinMode(fr_back, OUTPUT);

  pinMode(bl_for, OUTPUT);
  pinMode(bl_back, OUTPUT);

  pinMode(br_for, OUTPUT);
  pinMode(br_back, OUTPUT);
}
/*  Move function
    Dir (Boolean) { true: Forward,
          false: Backward }
    Spd (Int) { 0 <-> maxSpd }
    bias (Int) { Move more to left or right: -ve is left, +ve is right [Range: -turnFactor <-> turnFactor ] }
*/

void MotorControl::moveBot(float spd, float bias) {
  float sL = spd;
  float sR = spd;
  bool dir = (spd > 0) ? 1 : 0;

  if(bias != 0)
  {
    rotateBot((bias > 0) ? 1 : 0, bias);
    return;
  }

  sL = constrain(sL, -moveFactor * maxSpd, moveFactor * maxSpd);
  sR = constrain(sR, -moveFactor * maxSpd, moveFactor * maxSpd);
  if (sL < 0) {
    sL *= -1;
  }
  if (sR < 0) {
    sR *= -1;
  }

  if(dir)
  {
    analogWrite(fl_for, (int) sL);
    analogWrite(fl_back, 0);
    analogWrite(fr_for, (int) sR);
    analogWrite(fr_back, 0);
  }
  else
  {
    analogWrite(fl_for, 0);
    analogWrite(fl_back, (int) sL);
    analogWrite(fr_for, 0);
    analogWrite(fr_back, (int) sR);
  }

  delay(1);
}

void MotorControl::rotateBot(bool dir, float spd) {
  int s = spd * maxSpd;
  if (dir < 0) {
    s *= -1;
  }
  if(dir)
  {
    // Clockwise
    analogWrite(fl_for, s);
    analogWrite(fl_back, 0);
    analogWrite(fr_for, 0);
    analogWrite(fr_back, s);
  }
  else
  {
    // Counter Clockwise
    analogWrite(fl_for, 0);
    analogWrite(fl_back, s);
    analogWrite(fr_for, s);
    analogWrite(fr_back, 0);
  }
  delay(1);
}

//Turn off both motors
void MotorControl::stopMotors() {

  digitalWrite(fl_for, LOW);
  digitalWrite(fl_back, LOW);

  digitalWrite(fr_for, LOW);
  digitalWrite(fr_back, LOW);

  digitalWrite(bl_for, LOW);
  digitalWrite(bl_back, LOW);

  digitalWrite(br_for, LOW);
  digitalWrite(br_back, LOW);
}
