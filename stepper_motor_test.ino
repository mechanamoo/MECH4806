/*!
 * @file  DRI0043.ino
 * @brief TB6600 arduino Stepper Motor Driver is an easy-to-use professional stepper motor driver, which could control a two-phase stepping motor.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  DFRobot
 * @version  V1.0
 * @date  2023-08-03
 */

int PUL1=7; //define Pulse pin
int DIR1=6; //define Direction pin
int ENA1=5; //define Enable Pin
int PUL2=12; //define Pulse pin
int DIR2=11; //define Direction pin
int ENA2=10; //define Enable Pin
void setup() {
  pinMode (PUL1, OUTPUT);
  pinMode (DIR1, OUTPUT);
  pinMode (ENA1, OUTPUT);
  pinMode (PUL2, OUTPUT);
  pinMode (DIR2, OUTPUT);
  pinMode (ENA2, OUTPUT);
}

void loop() {
  for (int i=0; i<6400; i++)    //Forward 5000 steps
  {
    digitalWrite(DIR2,LOW);
    digitalWrite(ENA2,HIGH);
    digitalWrite(PUL2,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL2,LOW);
    delayMicroseconds(100);
  }
  for (int i=0; i<6400; i++)    //Forward 5000 steps
  {
    digitalWrite(DIR1,LOW);
    digitalWrite(ENA1,HIGH);
    digitalWrite(PUL1,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL1,LOW);
    delayMicroseconds(100);
  }
  for (int i=0; i<6400; i++)   //Backward 5000 steps
  {
    digitalWrite(DIR1,HIGH);
    digitalWrite(ENA1,HIGH);
    digitalWrite(PUL1,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL1,LOW);
    delayMicroseconds(100);
  }
  for (int i=0; i<6400; i++)   //Backward 5000 steps
  {
    digitalWrite(DIR2,HIGH);
    digitalWrite(ENA2,HIGH);
    digitalWrite(PUL2,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL2,LOW);
    delayMicroseconds(100);
  }
}