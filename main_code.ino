#include <ezButton.h>
#include <Arduino.h>
#include <Servo.h>


int count =1;
// STEPPER MOTORS
// Gantry motor
int PUL1=7; //Pulse pin
int DIR1=6; //Direction pin
int ENA1=5; //Enable Pin

int PUL2=12; //Pulse pin
int DIR2=11; //Direction pin
int ENA2=10; //Enable Pin

// ENCODERS
// Duplicate this for each encoder
int ENC1PINA=18;
int ENC1PINB=19;
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
long lastencoderValue = 0;
int lastMSB = 0;
int lastLSB = 0;

// LIMIT SWITCHES
ezButton limitSwitch1(40); // x bottom
ezButton limitSwitch2(48); // x top
ezButton limitSwitch3(44); // y right
ezButton limitSwitch4(52); // y left

// SERVO MOTOR
Servo penServo;
int SERVOPOS=0;

void setup() {
  Serial.begin (9600);
  
  // Stepper Motors
  pinMode (PUL1, OUTPUT);
  pinMode (DIR1, OUTPUT);
  pinMode (ENA1, OUTPUT);
  pinMode (PUL2, OUTPUT);
  pinMode (DIR2, OUTPUT);
  pinMode (ENA2, OUTPUT);

  // Encoders
  pinMode(ENC1PINA, INPUT_PULLUP); 
  pinMode(ENC1PINB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(18), updateEncoder, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(19), updateEncoder, CHANGE);

  // Limit Switches
  limitSwitch1.setDebounceTime(50); 
  limitSwitch2.setDebounceTime(50); 
  limitSwitch3.setDebounceTime(50); 
  limitSwitch4.setDebounceTime(50); 

  // Servo
  penServo.attach(36);

}

void loop() {
  
  homingSequence();

}

// ===================== MOTION ROUTINES =================================
void homingSequence(){
  limitSwitch2.loop();
  limitSwitch3.loop();
  limitSwitch4.loop();

  while (!(limitSwitch1.isPressed() || limitSwitch2.isPressed())){
    limitSwitch1.loop();

    Serial.println("made it to loop");
    
    if(limitSwitch1.isPressed()){
      Serial.println("pressed");
    }

    motor2Forward();
  }



  // count =0;
  // while (!(limitSwitch2.isPressed())){
  //   motor1Backwards();
  // }
  // while (!(limitSwitch3.isPressed())){
  //   motor2Forward();
  // }
  // while (!(limitSwitch4.isPressed())){
  //   motor2Backwards();
  // }
  
}


// ===================== COMPONENTS CONTROLS ==============================

void updateEncoder()
{
  int MSB = digitalRead(ENC1PINA); //MSB = most significant bit
  int LSB = digitalRead(ENC1PINB); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

void motor1Forward(){
  for (int i=0; i<6400; i++)    //Forward 5000 steps
  {
    digitalWrite(DIR1,LOW);
    digitalWrite(ENA1,HIGH);
    digitalWrite(PUL1,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL1,LOW);
    delayMicroseconds(100);
  }
  Serial.println("Motow Spinning");
}

void motor2Forward(){
  for (int i=0; i<200; i++)    //Forward 5000 steps
  {
    digitalWrite(DIR2,LOW);
    digitalWrite(ENA2,HIGH);
    digitalWrite(PUL2,HIGH);
    delayMicroseconds(250);
    digitalWrite(PUL2,LOW);
    delayMicroseconds(250);
  }
}

void motor1Backwards(){
  for (int i=0; i<6400; i++)   //Backward 5000 steps
  {
    digitalWrite(DIR1,HIGH);
    digitalWrite(ENA1,HIGH);
    digitalWrite(PUL1,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL1,LOW);
    delayMicroseconds(100);
  }
}

void motor2Backwards(){
  {
    digitalWrite(DIR2,HIGH);
    digitalWrite(ENA2,HIGH);
    digitalWrite(PUL2,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL2,LOW);
    delayMicroseconds(100);
  }
}







