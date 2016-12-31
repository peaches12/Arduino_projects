//this program moves the robot from the living room to Alexandra's room
 
#include "MeMegaPi.h"
MeMegaPiDCMotor motor1(PORT1A);

MeMegaPiDCMotor motor2(PORT1B); //FRONT MOTOR--the one with the MegaPi

MeMegaPiDCMotor motor3(PORT2A);

MeMegaPiDCMotor motor4(PORT2B); //BACK MOTOR--the one with the batteries

void setup()
{
    delay(5000);
}

void loop()
{
  motor2.run(-255);
  motor4.run(255);
  delay(3190); //table to hall
  motor4.stop();
  motor2.run(255);
  delay(2000); // turn right
  motor2.run(-255);
  motor4.run(255);
  delay(10000); //hall to bedroom
  motor4.stop();
  motor2.run(255);
  delay(2000); // turn right
  motor2.run(-255);
  motor4.run(255);
  delay(3190); //into the bedroom
  motor2.stop();
  motor4.run(255);
  delay(2000);
  motor2.run(-255);
  motor4.run(255);
  delay(3000);
  motor4.stop();
  motor2.stop();
  
}

